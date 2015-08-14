/*
 * Key_Long_Short
 * Ӳ��������Launchpad G2553��������P1.3����һ��������P1.0��P1.6������1��LED��������ñ���ӣ�
 * ����������ʹ��״̬���б𳤶̰������̰����л�LED1״̬���������л�LED2״̬
 *  Created on: 2013-4-8
 *  Author: Administrator
 */
#include "MSP430G2553.h"

//-----��״̬���к궨��-----
#define IDLE						0
#define SHORT					1
#define LONG					2
#define COUNTER_THRESHOLD   30		/*�����б�����*/
//-----ȫ�ֱ���-----
unsigned char WDT_Counter=0;				/*���ڶ԰�������ʱ����м���*/

//-----��main����ǰ��ǰ��������-----
void GPIO_init();
void WDT_init();
void Key_SM();
unsigned char LongClick_Dect();
void P13_OnShortRelease();
void P13_OnLongClick();

/******Ϊ�����Ķ�ϰ�ߣ���main��������ǰ�棬�����������ͱ�����ǰ����***/
void main(void) {
	WDTCTL = WDTPW + WDTHOLD;	//�ع�
	GPIO_init();
	WDT_init();
	_enable_interrupts();							//�����ж�
	_bis_SR_register(LPM3_bits);				//LPM3����
}

/******************************************************************************************************
 * ��       �ƣ�GPIO_Init()
 * ��       �ܣ��趨������LED����IO�ķ������ð���IO����������
 * ��ڲ�������
 * ���ڲ�������
 * ˵       ������
 * ��       ������
 ******************************************************************************************************/
void GPIO_init()
{
	//-----�趨P1.0��P1.6�������ʼֵ-----
	P1DIR |= BIT0+BIT6;				//�趨P1.0��P1.6Ϊ���
	P1OUT |= BIT0;						//�趨P1.0��ֵ
	P1OUT &= ~BIT6;					//�趨P1.6��ֵ
	//-----��ϻ�е�����������ڲ���������-----
	P1REN |= BIT3;				        //����P1.3�ڲ�����������
	P1OUT |= BIT3;			            //����������Ϊ����
}
/******************************************************************************************************
 * ��       �ƣ�WDT_init()
 * ��       �ܣ��趨WDT��ʱ�ж�Ϊ16ms������WDT��ʱ�ж�ʹ��
 * ��ڲ�������
 * ���ڲ�������
 * ˵       ����WDT��ʱ�жϵ�ʱ��Դѡ��ACLK��������LPM3���ߡ�
 * ��       ������
 ******************************************************************************************************/
void WDT_init()
{
	//-----�趨WDTΪ-----
	WDTCTL=WDT_ADLY_16;
	//-----WDT�ж�ʹ��-----
    IE1|=WDTIE;
}
/******************************************************************************************************
 * ��       �ƣ�WDT_ISR()
 * ��       �ܣ���ӦWDT��ʱ�жϷ���
 * ��ڲ�������
 * ���ڲ�������
 * ˵       ��������ֱ���ж��¼���������״̬��
 * ��       ������
 ******************************************************************************************************/
#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR(void)
{
	//-----���ð���״̬��-----
	Key_SM();
}

/******************************************************************************************************
 * ��       �ƣ�Key_SM()
 * ��       �ܣ����̼�״̬��
 * ��ڲ�������
 * ���ڲ�������
 * ˵       ������״̬��ΪMoore��״̬������Switch(State)�������ж��¼�
 * ��       ������
 ******************************************************************************************************/
 void Key_SM()
{
	static unsigned char State;				//״̬����״̬����
	static unsigned char Key_Now=0;	//��¼�����ĵ�ǰ��ƽ
	unsigned char Key_Past=0;				//��¼������ǰһ�ε�ƽ

	Key_Past=Key_Now;
	//-----��ѯIO������Ĵ���-----
	if(P1IN&BIT3) 	Key_Now=1;
	else 					    Key_Now=0;
	//-----��ƽǰ�ߺ�ͣ��������������¼�-----
	if((Key_Past==1)&&(Key_Now==0))
	{
		switch(State)
		{
		case IDLE:WDT_Counter=0;State=SHORT;break;//·��1
		default:break;
		}
	}
	//-----��ƽǰ�ͺ�ߣ����������ɿ�-----
	if((Key_Past==0)&&(Key_Now==1))
	{
		switch(State)
		{
		case SHORT:State=IDLE;P13_OnShortRelease();break;//·��2
		case LONG:	WDT_Counter=0;State=IDLE;break;			//·��4
		default:break;
		}
	}
	//-----�������¼�-----
	if(LongClick_Dect())
	{
		switch(State)
		{
		case SHORT:State=LONG;P13_OnLongClick();break;	//·��3
		default:break;
		}
	}
}
 /******************************************************************************************************
  * ��       �ƣ�LongClick_Dect()
  * ��       �ܣ���WDT�жϼ�ʱ���������㲢���ء���������Ϣ
  * ��ڲ�������
  * ���ڲ�������
  * ˵       ����
  * ��       ������
  ******************************************************************************************************/
unsigned char LongClick_Dect()
{
	WDT_Counter++;
	if (WDT_Counter ==COUNTER_THRESHOLD)
	{
		WDT_Counter=0;
		return(1);
	}
	else return(0);
}
/******************************************************************************************************
 * ��       �ƣ�P13_OnShortRelease()
 * ��       �ܣ�P1.3�Ķ̰��¼���������������P1.3�������̰�������һ����ʲô
 * ��ڲ�������
 * ���ڲ�������
 * ˵       ����ʹ���¼�������������ʽ��������ǿ�������ֲ�ԺͿɶ���
 * ��       ������
 ******************************************************************************************************/
void P13_OnShortRelease()					//P1.3���¼���������
{
	//----��תP1.3IO��ƽ-----
	P1OUT ^= BIT0;
}
/******************************************************************************************************
 * ��       �ƣ�P13_OnLongClick()
 * ��       �ܣ�P1.3�ĳ����¼���������������P1.3����������������һ����ʲô
 * ��ڲ�������
 * ���ڲ�������
 * ˵       ����ʹ���¼�������������ʽ��������ǿ�������ֲ�ԺͿɶ���
 * ��       ������
 ******************************************************************************************************/
void P13_OnLongClick()					//P1.3���¼���������
{
	//----��תP1.6IO��ƽ-----
	P1OUT ^= BIT6;
}
/*
 * TCA6416A.c
 *
 *  Created on: 2013-4-6
 *      Author: Administrator
 */
#include "USCI_I2C.h"

//-----���ƼĴ�������-----
#define		In_CMD0			0x00	//��ȡ�ܽ�����״̬�Ĵ�����ֻ��
#define		In_CMD1			0x01
#define		Out_CMD0		0x02	//���ƹܽ����״̬�Ĵ�����R/W
#define		Out_CMD1		0x03
#define		PIVS_CMD0		0x04	//������ƹܽ����״̬�Ĵ�����R/W
#define		PIVS_CMD1		0x05
#define		CFG_CMD0		0x06	//�ܽŷ�����ƣ�1��In��0:��Out��
#define		CFG_CMD1		0x07
volatile unsigned int TCA6416A_InputBuffer=0;

/******************************************************************************************************
 * ��       �ƣ�TCA6416_Tx_Frame()
 * ��       �ܣ���TCA6416����һ֡����
 * ��ڲ�����*p_Tx�����������ݵ�ͷָ��
 * 					 num�������ֽ���
 * ���ڲ�������
 * ˵       �������õײ�����ʵ�֡����ɹ�Ϊֹ��
 * ��       ������
 ******************************************************************************************************/
void TCA6416_Tx_Frame(unsigned char *p_Tx,unsigned char num)
{
	unsigned char temp=0;
	do{
			temp=PreSet_Tx_Frame(p_Tx, num);
		}while(temp==0);
}
/******************************************************************************************************
 * ��       �ƣ�TCA6416_Rx_Frame()
 * ��       �ܣ���TCA6416A����һ֡����
 * ��ڲ����� *p_Rx����������ݵ�ͷָ��
 * 					 num���������ֽ���
 * ���ڲ�������
 * ˵       �������õײ���������ʵ�֡��ճɹ�Ϊֹ��
 * ��       ������
 ******************************************************************************************************/
void TCA6416_Rx_Frame(unsigned char *p_Rx,unsigned char num)
{
	unsigned char temp=0;
	do {
		temp=PreSet_Rx_Frame(p_Rx, num);
	}while(temp==0);
}
/******************************************************************************************************
 * ��       �ƣ�TCA6416A_Init()
 * ��       �ܣ�TCA6416A
 * ��ڲ�������
 * ���ڲ�������
 * ˵       �������ƶ�FIFO��������ָ������ѭ��
 * ��       ������
 ******************************************************************************************************/
void TCA6416A_Init(void)
{
	unsigned char conf[3]={0};
	 __delay_cycles(100000);			//TCA6416�ĸ�λʱ��ȵ�Ƭ�������ӳ�ȷ���ɿ���λ
	 USCI_I2C_Init();
	 USCI_I2C_Tx_Init();				//��ԶĬ�Ϸ�ģʽ
	//----������չ�������ʹ�ã����������ڹܽų�ʼ��Ϊ���룬����ܽų�ʼ��Ϊ���
	conf[0] = CFG_CMD0;					//TCA6416���ƼĴ���
	conf[1] = 0x00;						//  0 0 0 0_0 0 0 0  ��LED0~LED7��
	TCA6416_Tx_Frame(conf,2);			//  д��������

	conf[0] = CFG_CMD1;
	conf[1] = 0x0f;						//  0 0 0 0_1 1 1 1 (����)
	TCA6416_Tx_Frame(conf,2);			//  д��������

	//----�ϵ��Ƚ��ܽ����Ϊ�ߣ��˲���������ܽ���Ч��
	conf[0] = Out_CMD0;
	conf[1] = 0xff;						// ĳλ��1�����Ϊ�ߣ�0Ϊ��
	TCA6416_Tx_Frame(conf,2);			//  д��������

	conf[0] = Out_CMD1;
	conf[1] = 0xff;
	TCA6416_Tx_Frame(conf,2);			//  д��������
}

/******************************************************************************************************
 * ��       �ƣ�PinOUT()
 * ��       �ܣ�I2C��Rx�¼�������������ȡUCB0RXBUFд��ָ������������
 * ��ڲ�������
 * ���ڲ�������
 * ˵       �������ƶ�FIFO��������ָ������ѭ��
 * ��       ������
 ******************************************************************************************************/
void PinOUT(unsigned char pin,unsigned char status)
{
	static unsigned char pinW0 = 0xff;		//���ڻ�����д����Ӧ�ܽŵ�״̬��Ϣ���˲����������TCA6416A�е�ǰ�Ĵ�����ֵ
	static unsigned char pinW1 = 0xff;		//���ڻ�����д����Ӧ�ܽŵ�״̬��Ϣ���˲����������TCA6416A�е�ǰ�Ĵ�����ֵ

	unsigned char out0_7[2]={0};				//�ܽ� pin0~pin7���״̬����
	unsigned char out10_17[2] = {0};			//�ܽ� pin10~pin17���״̬����
	if(pin<=7)												//��ѡ�ܽ�Ϊpin0~pin7 ��ˢ����Ҫ�������������pinW0 ״̬
	{
		if(status == 0)
			pinW0 &= ~(1<<pin);
		else
			pinW0 |= 1<<pin;
		out0_7[0] = Out_CMD0;
		out0_7[1] = pinW0;
		 TCA6416_Tx_Frame(out0_7,2);					// �����º�����ݰ���д��оƬ�Ĵ���

	}
	else if(pin>=10 && pin<=17)				//��ѡ�ܽ�Ϊpin10~pin17 ��ˢ����Ҫ�������������pinW1 ״̬
	{
		if(status == 0)
			pinW1 &= ~(1<<(pin%10));
		else
			pinW1 |= 1<<(pin%10);
		out10_17[0] = Out_CMD1;
		out10_17[1] = pinW1 ;
		 TCA6416_Tx_Frame(out10_17,2);				// �����º�����ݰ���д��оƬ�Ĵ���
	}
	else
	{
	    __no_operation();                       					// Set breakpoint >>here<<
	}

}
/******************************************************************************************************
 * ��       �ƣ�PinIN()
 * ��       �ܣ�I2C��Rx�¼�������������ȡUCB0RXBUFд��ָ������������
 * ��ڲ�������
 * ���ڲ�������
 * ˵       �������ƶ�FIFO��������ָ������ѭ��
 * ��       ������
 ******************************************************************************************************/
void PinIN()
{
	unsigned char temp[1]={0};
	unsigned char conf[1]={0};
	conf[0]=In_CMD1;
	TCA6416_Tx_Frame(conf,1);										//	д��Ҫ��ȡ�ļĴ�����ַ����
	USCI_I2C_Rx_Init();                 		 								// ��I2C�л���Rxģʽ ��ʼ��
	TCA6416_Rx_Frame(temp,1);										// ��ȡ�������ڹܽ���Ϣ

	//----�����¼�ֵ�����µ����뻺��----
    TCA6416A_InputBuffer = TCA6416A_InputBuffer&0x00ff;
	TCA6416A_InputBuffer |=(((unsigned int)temp[0])<<8 )&0xff00;
	USCI_I2C_Tx_Init(); // ��I2C�л���Txģʽ ��ʼ��
}
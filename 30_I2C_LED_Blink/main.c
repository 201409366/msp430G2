/*警告：由于G2 LaunchPad上的LED2使用了P1.6（I2C引脚），所以所有涉及到I2C的实验都必须把P1.6跳线拔除,包含本例程！
 * main.c
 */
#include"MSP430G2553.h"
#include"TCA6416A.h"

void WDT_init();
void I2C_IODect()	;		                 //检测事件确实发生了

void main(void)
{
	WDTCTL = WDTPW + WDTHOLD;	//关狗
    BCSCTL1 = CALBC1_16MHZ;      /* Set DCO to 8MHz */
    DCOCTL = CALDCO_16MHZ;
    TCA6416A_Init();			// 初始化IO扩展口
//----提示初始化成功----
	PinOUT(0,1);           // 指定0号管脚输出为0
	PinOUT(1,0);           // 指定1号管脚输出为0
	PinOUT(2,0);           // 指定2号管脚输出为0
	PinOUT(3,0);           // 指定3号管脚输出为0
	PinOUT(4,0);           // 指定4号管脚输出为0
	PinOUT(5,0);           // 指定5号管脚输出为0
	PinOUT(6,0);           // 指定6号管脚输出为0
	PinOUT(7,0);           // 指定7号管脚输出为0
	WDT_init();
	while(1)
	{
		 _bis_SR_register(LPM0_bits);
		 PinOUT(0,0);
		 PinOUT(1,1);
		 _bis_SR_register(LPM0_bits);
		 PinOUT(1,0);
		 PinOUT(2,1);
		 _bis_SR_register(LPM0_bits);
		 PinOUT(2,0);
		 PinOUT(3,1);
		 _bis_SR_register(LPM0_bits);
		 PinOUT(3,0);
		 PinOUT(4,1);
		 _bis_SR_register(LPM0_bits);
		 PinOUT(4,0);
		 PinOUT(5,1);
		 _bis_SR_register(LPM0_bits);
		 PinOUT(5,0);
		 PinOUT(6,1);
		 _bis_SR_register(LPM0_bits);
		 PinOUT(6,0);
		 PinOUT(7,1);
		 _bis_SR_register(LPM0_bits);
		 PinOUT(7,0);
		 PinOUT(0,1);
	}


}

/********WDT初始化函数**********/
void WDT_init()
{
	//-----设定WDT为-----------
	WDTCTL=WDT_ADLY_250;
	//-----WDT中断使能----------------------
    IE1 |= WDTIE;
    _enable_interrupts();
}


/***********WDT定时中断函数*************/
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
__bic_SR_register_on_exit(LPM0_bits );
}



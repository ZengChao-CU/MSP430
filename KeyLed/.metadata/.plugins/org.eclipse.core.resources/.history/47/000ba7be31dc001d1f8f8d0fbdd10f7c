#include <msp430.h> 
//函数库
#include <HARDWARE/delay.h>//延时函数
#include <HARDWARE/led.h>  //初始化函数

/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// 关闭看门狗

	LED_Init();//led初始化函数

    while (1)
    {
     P1OUT |= BIT0;            //亮灯
     P4OUT &= ~BIT7;            //低电平熄灯
     delay_ms(1000);
     P1OUT &= ~BIT0;             //低电平熄灯
     P4OUT |= BIT7;           //亮灯
     delay_ms(1000);
    }
	//return 0;
}

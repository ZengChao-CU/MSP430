#include <msp430.h>
#include <HARDWARE/delay.h>
int s=0;//记录按键次数
int num=0;//LED值
/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1SEL &= ~0x3C;
    P1DIR |= (BIT2|BIT3|BIT4|BIT5);
    P1OUT &= ~(BIT2|BIT3|BIT4|BIT5);
    P2SEL &= ~BIT1;
    P2DIR &= ~BIT1;
    P2IFG = 0x00;
    P2IE = BIT1;
    P2IES = BIT1;
    P2IN = BIT1;
    P2OUT = BIT1;
    P2REN = BIT1;
   // _enable_interrupts();
    _EINT();
    while(1)
    {
     num=s%4;
     switch(num){
     case 0:P1OUT=BIT2;break;
     case 1:P1OUT=BIT3;break;
     case 2:P1OUT=BIT4;break;
     case 3:P1OUT=BIT5;break;
     }
    }
    //return 0;
}
#pragma vector=PORT2_VECTOR
__interrupt void Port2_ISR(void){
    unsigned int temp;
    delay_ms(100);
    if(!(P2IN&BIT1)){
        temp=P2IFG;
        P2IFG=0x00;
        s++;
    }

}

#include <msp430f5529.h>
#include <HARDWARE/delay.h>
// *************************************************************
// 主程序
// *************************************************************
//在P1.3产生pwm波

void main(void)
{
//  unsigned int PWMPeriod = 1000; //设置PWM周期
  unsigned int i=0;
  WDTCTL = WDTPW + WDTHOLD;   // 关闭看门狗
//
//  P2SEL |= BIT4;
//  P2DIR |= BIT4;
//
//
//  TA2CCR0 = PWMPeriod;
//  TA2CTL = TASSEL_2 + MC_1;
//  TA2CCTL1 = OUTMOD_7;
//
//  while(1){
//      for(i=0;i<PWMPeriod;i+=10)
//      {
//          TA2CCR1=i;
//          delay_ms(20);
//      }
//      for(i=PWMPeriod;i>0;i-=10)
//      {
//          TA2CCR1=i;
//          delay_ms(20);
//      }
//  }
////闪烁
  P3SEL &= ~BIT7;
  P3DIR |= BIT7;
  P3OUT &= ~BIT7;

  TA0CTL = TASSEL_2+TAIE+TACLR+ MC_1;
  TA0CCR0 = 10000;
    while(1){
        if(TA0CTL&TAIFG){
          i++;
          TA0CTL &= ~TAIFG;
          if(i==15){
              P3OUT ^= BIT7;
              i=0;
          }
      }
}





}





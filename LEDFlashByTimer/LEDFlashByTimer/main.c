#include <msp430f5529.h>
#include <HARDWARE/delay.h>
// *************************************************************
// 主程序
// *************************************************************
//在P1.3产生pwm波

void main(void)
{

  WDTCTL = WDTPW + WDTHOLD;   // 关闭看门狗
  unsigned int count=0;
  P2DIR |= BIT3;

  TA1CTL = TASSEL_2 + MC_2;//信号源选择SMCLK。计数模式选择加计数模式，循环0x0000~0xffff

  while(1){
      if(TA1CTL & TAIFG){//检测是否有中断事件
          count++;
          TA1CTL &= ~TAIFG;//标志位清零
          if(count==15){//默认情况下DCO为1MHz, 65.536ms中断发生一次。1s大约需要15次
              P2OUT ^= BIT3;//翻转
              count=0;
          }
      }
  }


}


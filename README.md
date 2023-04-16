# MSP430
- [MSP430](#msp430)
  - [一、（LED交替闪烁）The LEDs flash alternately](#一led交替闪烁the-leds-flash-alternately)
    - [(一)、实验内容](#一实验内容)
    - [(二)、开发板介绍](#二开发板介绍)
      - [**1、 I/O** **的简介**](#1-io-的简介)
      - [**2、I/O 的简单配置**](#2io-的简单配置)
    - [(三)、原理图(只涉及本实验的)](#三原理图只涉及本实验的)
    - [(四)、代码部分](#四代码部分)
    - [(五)、实验现象](#五实验现象)
  - [二、（按键控制LED）Press the key to control the LED](#二按键控制ledpress-the-key-to-control-the-led)
    - [（一）、实验内容](#一实验内容-1)
    - [（二）、原理图及涉及到的寄存器](#二原理图及涉及到的寄存器)
    - [（三）、代码部分](#三代码部分)
    - [（四）、实验现象](#四实验现象)


msp430f5529 study 

## 一、（LED交替闪烁）The LEDs flash alternately


### (一)、实验内容

**使用开发板：msp430f5529**

**使用的LED灯：为开发板上自带的User LEDs(LED1、LED2)**

**环境：CCS     (Version: 12.2.0.00009)** 

**通过ccs编写代码，控制LED1和LED2交替闪烁**

### (二)、开发板介绍

**开发板正面 与背面图**    
<img src="https://github.com/ZengChao-CU/MSP430/blob/master/msp430LEDImag/%E5%BC%80%E5%8F%91%E6%9D%BF%E6%AD%A3%E9%9D%A2.jpg" width=200dp />                          <img src="https://github.com/ZengChao-CU/MSP430/blob/master/msp430LEDImag/%E5%BC%80%E5%8F%91%E6%9D%BF%E8%83%8C%E9%9D%A2.jpg" width=200dp /> 


#### **1、 I/O** **的简介**

**一般情况下，P1和 P2都是具有中断能力的。从 P1和 P2接口的各个I/O 管脚引入的中断可以独立的被使能并且设置为上升沿或者下降沿触发。对应的中断向量表分别为 P1IV 和 P2IV，它们只能进行字操作，并且 PAIV 这个寄存器根本不存在。 P1、P2可合为 PA，P3、P4可合为 PB，…PC、PD。所以 P1为8位BCD 0x00，PA 为16位 BCD 0x0000。当进行字操作写入 PA 口时，所有的16位都被写入这个端口；当利用字节操作写入 PA 口的低字节时，高字节保持不变。**

#### **2、I/O 的简单配置** 

**(1)、功能选择寄存器 PXSEL**

**用来声明该端口是要应用于外围电路的特殊功能（不决定输入输出方向），默认为低电平。**

**低电平表示通用 I/O（默认），高电平表示该引脚将有连接外围电路的特殊用途即作为外设。**

 **如：设置P1.0和P1.1为通用 I/O的操作:**

```c
P1SEL &= ~(BIT0+BIT1); 
```

**(2)、I/O 方向设定寄存器 PXDIR**

**如设定 P1.1和 P1.2为输出状态 操作为：**

```c
P1DIR |=(BIT1+BIT2); //等价于 PADIR |=（BIT1+BIT2）或  PADIR_L |=（BIT1+BIT2）
```

**注意：在msp430f5529.h的头文件中BITS有如下定义：**

<img src="https://github.com/ZengChao-CU/MSP430/blob/master/msp430LEDImag/BITx%E6%89%80%E5%9C%A8%E5%A4%B4%E6%96%87%E4%BB%B6.png" width=400dp />

**(3)、I/O 输入设定寄存器 PXIN**

**如设定 P1.1和 P1.2的输入为低电平 操作为：**

```c
P1IN &= ~(BIT1+BIT2);
```

**(4)、I/O 输出设定寄存器 PXOUT**

**只用为简单的输出时：** 

**设定 P1.1和 P1.2输出高电平 操作为：**

```c
 P1OUT |= (BIT1+BIT2);
```

 **如果该引脚为正常 I/O 功能，且当前已设定为输入方向，且上拉/下拉电阻寄存器是有效地。那么 PXOUT 可以用来配置上拉和下拉电阻： 低电平为下拉电阻； 高电平为上拉电阻；**

 **(5)、上拉/下拉电阻使能寄存器 PXREN**

**低电平表示该寄存器为无效状态； 高电平表示该寄存器为有效状态；**

### (三)、原理图(只涉及本实验的)

<img src="https://github.com/ZengChao-CU/MSP430/blob/master/msp430LEDImag/LED%E5%8E%9F%E7%90%86%E5%9B%BE.png" width=400dp />

**由原理图可知，本实验应该设置P1.0和P4.7引脚为通用I/O,并且方向为输出方向，当P1.0和P4.7引脚为高电平时LED1和LED2点亮，为低电平时LED1和LED2熄灭。**

### (四)、代码部分

**main.c**

```c
#include <msp430.h> 

#include <delay.h>//延时函数
#include <led.h>  //初始化函数

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// 关闭看门狗
    
	LED_Init();   //led初始化函数

    while (1)
    {
     P1OUT |= BIT0;           //亮灯
     P4OUT &= ~BIT7;          //熄灯
     delay_ms(1000);
     P1OUT &= ~BIT0;          //熄灯
     P4OUT |= BIT7;           //亮灯
     delay_ms(1000);
    }
//	return 0;
}

```

**led.h**

```c
#ifndef GO_LED_H_
#define GO_LED_H_

#include <msp430.h>

void LED_Init(void);//初始化函数

#endif 

```

**led.c**

```c
#include "led.h"

void LED_Init(void)//led初始化函数
{
    
    P1SEL &= ~BIT0; //设置P1.0口为通用I/O
    P4SEL &= ~BIT7; //设置p4.7口为通用I/O
   
    P1DIR |= BIT0;   //设置P1.0口为输出模式
    P4DIR |= BIT7;   //设置p4.7口为输出模式

    //初始化为熄灭
    P1OUT &=~ BIT0;   //低电平熄灯
    P4OUT &=~ BIT7;   //低电平熄灯
}

```

**delay.h**

```c
#ifndef GO_DELAY_H_
#define GO_DELAY_H_

#include <msp430.h>

#define CPU_F ((double)1000000)
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))//重新定义延时函数
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))

#endif 

```

###  (五)、实验现象

[**点击跳转**](https://live.csdn.net/v/290512 )


## 二、（按键控制LED）Press the key to control the LED

### （一）、实验内容

**使用的开发板：msp430f5529。**

**使用的LED灯：为开发板上自带的User LEDs(LED1:P1.0)。**

**使用的按键：开发板自带的按键2（s2:P1.1）。**

**环境：CCS     (Version: 12.2.0.00009)。** 

**通过ccs编写代码，利用按键控制LED1亮灭。**

### （二）、原理图及涉及到的寄存器

**原理图：**


**涉及到的寄存器：P1SEL、P1DIR、P1OUT、P1IN、P1REN。**

**具体不做说明，在LED闪烁实验中有所介绍。**

### （三）、代码部分

**main.c**

```c
#include <msp430.h> 

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// 关闭看门狗

    P1SEL &= ~(BIT0+BIT1); //将P1.0 P1.1设置为通用I/O
	P1DIR |= BIT0;       //将P1.0设为输出模式
	P1OUT &= ~BIT0;     //初始化为灭
	P1DIR &= ~BIT1;      //将P1.1设为输入模式

	P1REN |= BIT1;       //使能上拉
	P1OUT |= BIT1;

    while (1)
    {
        if(P1IN & BIT1){  //高电平表示未被按下
            P1OUT &= ~BIT0; //熄灭
        }
        else{
            P1OUT |= BIT0;//点亮
        }

    }
	//return 0;
}
```

***关键部分***

```c
    P1REN |= BIT1;       //使能上拉
	P1OUT |= BIT1;
```

**将P1.1设置为上拉模式，P1.1默认状态为高电平。**

**当检测到P1.1为高电平时，表示按键未按下，P1.0熄灭；**
**当检测到P1.1为低电平时，表示按键按下，P1.0点亮。**

```c
if(P1IN & BIT1){...}
else{...}
```

**P1IN&BIT1:对按键按下情况进行检测.**

### （四）、实验现象

[**点击跳转**]( )
/*
 * Black_DELAY.h
 *
 *  Created on: 2020年10月8日
 *      Author: PC
 */

#ifndef GO_DELAY_H_
#define GO_DELAY_H_

#include <msp430.h>

#define CPU_F ((double)1000000)
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))//重新定义延时函数
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))



#endif /* GO_BLACK_DELAY_H_ */

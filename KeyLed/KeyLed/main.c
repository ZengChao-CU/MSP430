#include <msp430.h> 

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// �رտ��Ź�

	P1SEL &= ~(BIT0+BIT1);
	P1DIR |= BIT0;       //��P1.0��Ϊ���ģʽ
	P1OUT &= ~BIT0;     //��ʼ��Ϊ��
	P1DIR &= ~BIT1;      //��P1.1��Ϊ����ģʽ

	P1REN |= BIT1;       //ʹ������
	P1OUT |= BIT1;

    while (1)
    {
        if(P1IN & BIT1){  //�ߵ�ƽ��ʾδ������
            P1OUT &= ~BIT0; //Ϩ��
        }
        else{
            P1OUT |= BIT0;//����
        }

    }
	//return 0;
}
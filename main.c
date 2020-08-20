#include <stm32f10x.h>
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "TLC2543.h"
/*
��Ȩ����:https://github.com/MisakaMikoto128/TLC2543_STM32
���ߣ���Ը��
*/
int main()
{
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 //���ڳ�ʼ��Ϊ9600
	TLC2543_Init();

	while(1)
	{
			delay_ms(1000);   
			printf("%f:V\r\n",TLC2543_Calvot(TLC2543_Read(AIN0),OUT12BIT_MAX));
			//printf("%d\r\n",TLC2543_Read(AIN0|BIP));˫����
			//printf("%d\r\n",TLC2543_Read(AIN0|BIP|LSBF));˫���ԣ�LSB frist
	}
}

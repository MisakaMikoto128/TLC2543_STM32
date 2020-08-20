#include <stm32f10x.h>
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "TLC2543.h"
/*
版权所有:https://github.com/MisakaMikoto128/TLC2543_STM32
作者：林愿留
*/
int main()
{
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 //串口初始化为9600
	TLC2543_Init();

	while(1)
	{
			delay_ms(1000);   
			printf("%f:V\r\n",TLC2543_Calvot(TLC2543_Read(AIN0),OUT12BIT_MAX));
			//printf("%d\r\n",TLC2543_Read(AIN0|BIP));双极性
			//printf("%d\r\n",TLC2543_Read(AIN0|BIP|LSBF));双极性，LSB frist
	}
}

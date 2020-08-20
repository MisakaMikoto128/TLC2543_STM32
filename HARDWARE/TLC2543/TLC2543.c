#include "TLC2543.h"

/*
版权所有:https://github.com/MisakaMikoto128/TLC2543_STM32
作者：林愿留
*/
void TLC2543_Init()
{
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );//PORTB时钟使能 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;  // PB12 推挽 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOB,GPIO_Pin_12);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);

	SPI2_Init();		   	//初始化SPI
	SPI2_SetSpeed(SPI_BaudRatePrescaler_256);//设置为18M时钟,高速模式
}	

unsigned int TLC2543_ReadWirte(unsigned int ctrlcode)
{
	unsigned int rev = 0;
	ctrlcode |= OUT16BIT;
	ctrlcode <<=8;//控制码在高字节
	CS=0;                            //使能器件 
		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE)==RESET); 
	SPI_I2S_SendData(SPI2,ctrlcode);  //写入一个数据，包括采样通道和数据格式  
		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE)==RESET); 
	rev = SPI_I2S_ReceiveData(SPI2);         //发送读取命令 
	CS=1;
	return rev;  
}

unsigned int TLC2543_Read(unsigned int channel)   
{
	unsigned int adcvalue = 0;
	adcvalue = TLC2543_ReadWirte(channel)>>4;
		while(!EOC);  
	return adcvalue;  
}

unsigned int TLC2543_Set(unsigned int ctrlcode)
{
	return TLC2543_ReadWirte(ctrlcode);
}

float TLC2543_Calvot(unsigned int ADCValue,int maxout)
{
	return ADCValue*RF_VOT/maxout;
}


int TLC2543_readAll(unsigned char *pdata,int len)
{
	for(int i = 0; i < len; i++)
	{
		pdata[i] = TLC2543_Read(((AIN0 >> 4) + (unsigned char)i) << 4);
	}
	return len;
}

#include "TLC2543.h"

/*
��Ȩ����:https://github.com/MisakaMikoto128/TLC2543_STM32
���ߣ���Ը��
*/
void TLC2543_Init()
{
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );//PORTBʱ��ʹ�� 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;  // PB12 ���� 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOB,GPIO_Pin_12);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
 	GPIO_Init(GPIOB, &GPIO_InitStructure);

	SPI2_Init();		   	//��ʼ��SPI
	SPI2_SetSpeed(SPI_BaudRatePrescaler_256);//����Ϊ18Mʱ��,����ģʽ
}	

unsigned int TLC2543_ReadWirte(unsigned int ctrlcode)
{
	unsigned int rev = 0;
	ctrlcode |= OUT16BIT;
	ctrlcode <<=8;//�������ڸ��ֽ�
	CS=0;                            //ʹ������ 
		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE)==RESET); 
	SPI_I2S_SendData(SPI2,ctrlcode);  //д��һ�����ݣ���������ͨ�������ݸ�ʽ  
		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE)==RESET); 
	rev = SPI_I2S_ReceiveData(SPI2);         //���Ͷ�ȡ���� 
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

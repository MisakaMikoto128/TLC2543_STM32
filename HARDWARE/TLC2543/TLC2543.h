#ifndef _TLC2543_H_
#define _TLC2543_H_
#include "sys.h"
#include "spi.h"

//CPOL = 0
//CPHA = 0

#define RF_VOT 4.98




//每一个长等号为一块，每一块之间或运算来形成运算符,Output data length默认为OUT16BIT，所
//以操作时就是(data input|[Output data format]|[polar]),[]表示可以省略。
/*=============data input===============*/
//Select input channel
#define AIN0  	0x00             
#define AIN1		0x10
#define AIN2   	0x20
#define AIN3   	0x30
#define AIN4   	0x40
#define AIN5   	0x50
#define AIN6   	0x60
#define AIN7   	0x70
#define AIN8   	0x80
#define AIN9   	0x90
#define AIN10  	0xA0
//Select test voltage
#define RF0			0xB0
#define RFN			0xC0
#define RFP			0xD0
//Software power down
#define TLC2543POWER_ON		0xE000
#define TLC2543POWER_OFF	0xF000

/*=============data output://default===============*/
//Output data length
#define OUT8BIT 	0x04
#define OUT12BIT 	0x00	//default
#define OUT16BIT 	0x0C

#define OUT8BIT_MAX 0x0F
#define OUT12BIT_MAX 	4095
#define OUT16BIT_MAX 	0xFF
/*=================//default======================*/
//Output data format
#define MSBF	0x00	//default
#define LSBF	0x02

/*===================//default====================*/
#define UIP		0x00	//Unipolar (binary)		//default
#define BIP		0x01	//Bipolar (BIP) 2s complement



//TLC2543控制引脚宏定义
#define EOC	PBin(11)
#define CS	PBout(12)                        //模拟片选口

//初始化SPI TLC2543的IO口
void TLC2543_Init(void);
unsigned int TLC2543_ReadWirte(unsigned int ctrlcode);
unsigned int TLC2543_Read(unsigned int channel);
unsigned int TLC2543_Set(unsigned int ctrlcode);
float TLC2543_Calvot(unsigned int ADCValue,int maxout);
int TLC2543_readAll(unsigned char *pdata,int len);

#endif

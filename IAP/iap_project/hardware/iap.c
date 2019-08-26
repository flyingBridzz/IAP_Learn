#include "iap.h"
#include "stmflash.h"
#include "usart.h"
#include "tim.h"

uint32_t iapBuf[512];
iapFun jump2APP;

__asm void MSR_MSP(uint32_t addr) 
{
	MSR MSP, r0 			//set Main Stack value
	BX r14
}

/********************************************
*函数名：	IAP_Write_APPbin
*参数：		appxaddr：flash写入地址
					appBuf：存放代码的数组首地址
					appSize：APP的大小(单位：Byte)
*返回值：	空
*功能：		将接收到的APP代码写入到flash中去
********************************************/
void IAP_Write_APPbin(uint32_t appxaddr, uint8_t *appBuf, uint32_t appSize)
{
	uint32_t t;
	uint16_t i=0;
	uint32_t temp;
	uint32_t fwaddr=appxaddr;//当前写入的地址
	uint8_t *dfu=appBuf;
	for(t=0;t<appSize;t+=4)
	{
		temp = ((uint32_t)dfu[3])<<24;
		temp |= ((uint32_t)dfu[2])<<16;
		temp |= ((uint32_t)dfu[1])<<8;
		temp |= (uint32_t)dfu[0];
		dfu+=4;
		iapBuf[i++] = temp;
		if(i == 512){
			i = 0;
			STMFLASH_Write(fwaddr, iapBuf, 512);
			fwaddr += 4*512;
		}
	}
	if(i)STMFLASH_Write(fwaddr, iapBuf, i);
}

/********************************************
*函数名：	IAP_Load_APP
*参数：		appxaddr：程序跳转地址
*返回值：	空
*功能：		加载APP应用程序
********************************************/
void IAP_Load_APP(uint32_t appxaddr)
{ 
	if(((*(volatile uint32_t*)appxaddr)&0x2FFE0000)==0x20000000)	//检查栈顶地址是否合法.
	{ 
		HAL_UART_DeInit(&huart1);
		HAL_TIM_Base_DeInit(&htim6);
		jump2APP=(iapFun)*(volatile uint32_t*)(appxaddr+4);		//用户代码区第二个字为程序开始地址(复位地址)		
		MSR_MSP(*(volatile uint32_t*)appxaddr);					//初始化APP堆栈指针(用户代码区的第一个字用于存放栈顶地址)
		jump2APP();									//跳转到APP.
	}
}		



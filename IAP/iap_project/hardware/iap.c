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
*��������	IAP_Write_APPbin
*������		appxaddr��flashд���ַ
					appBuf����Ŵ���������׵�ַ
					appSize��APP�Ĵ�С(��λ��Byte)
*����ֵ��	��
*���ܣ�		�����յ���APP����д�뵽flash��ȥ
********************************************/
void IAP_Write_APPbin(uint32_t appxaddr, uint8_t *appBuf, uint32_t appSize)
{
	uint32_t t;
	uint16_t i=0;
	uint32_t temp;
	uint32_t fwaddr=appxaddr;//��ǰд��ĵ�ַ
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
*��������	IAP_Load_APP
*������		appxaddr��������ת��ַ
*����ֵ��	��
*���ܣ�		����APPӦ�ó���
********************************************/
void IAP_Load_APP(uint32_t appxaddr)
{ 
	if(((*(volatile uint32_t*)appxaddr)&0x2FFE0000)==0x20000000)	//���ջ����ַ�Ƿ�Ϸ�.
	{ 
		HAL_UART_DeInit(&huart1);
		HAL_TIM_Base_DeInit(&htim6);
		jump2APP=(iapFun)*(volatile uint32_t*)(appxaddr+4);		//�û��������ڶ�����Ϊ����ʼ��ַ(��λ��ַ)		
		MSR_MSP(*(volatile uint32_t*)appxaddr);					//��ʼ��APP��ջָ��(�û��������ĵ�һ�������ڴ��ջ����ַ)
		jump2APP();									//��ת��APP.
	}
}		



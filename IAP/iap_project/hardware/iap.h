#ifndef _IAP_H_
#define _IAP_H_

#include "main.h"

#define FLASH_APP_ADDR		0x08010000  	//第一个应用程序起始地址(存放在FLASH)

typedef void(*iapFun)(void);

void IAP_Write_APPbin(uint32_t appxaddr, uint8_t *appBuf, uint32_t appSize);
void IAP_Load_APP(uint32_t appxaddr);


#endif

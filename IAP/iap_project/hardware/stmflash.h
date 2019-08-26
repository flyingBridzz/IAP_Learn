#ifndef _STMFLASH_H_
#define _STMFLASH_H_

#include "main.h"

#define STM32_FLASH_BASE 0x08000000 	//STM32 FLASH����ʼ��ַ
#define FLASH_WAITETIME  50000          //FLASH�ȴ���ʱʱ��

#define	ADDR_FLASH_SECTOR_0		((uint32_t)0x08000000)	//����0����ʼ��ַ��16KB
#define ADDR_FLASH_SECTOR_1		((uint32_t)0x08004000)	//����1����ʼ��ַ��16KB
#define	ADDR_FLASH_SECTOR_2		((uint32_t)0x08008000)	//����2����ʼ��ַ��16KB
#define ADDR_FLASH_SECTOR_3		((uint32_t)0x0800C000)	//����3����ʼ��ַ��16KB
#define ADDR_FLASH_SECTOR_4		((uint32_t)0x08010000)	//����4����ʼ��ַ��64KB
#define ADDR_FLASH_SECTOR_5		((uint32_t)0x08020000)	//����5����ʼ��ַ��128KB
#define ADDR_FLASH_SECTOR_6		((uint32_t)0x08040000)	//����6����ʼ��ַ��128KB
#define ADDR_FLASH_SECTOR_7		((uint32_t)0x08060000)	//����7����ʼ��ַ��128KB
#define ADDR_FLASH_SECTOR_8		((uint32_t)0x08080000)	//����8����ʼ��ַ��128KB
#define ADDR_FLASH_SECTOR_9		((uint32_t)0x080A0000)	//����9����ʼ��ַ��128KB
#define ADDR_FLASH_SECTOR_10	((uint32_t)0x080C0000)	//����10����ʼ��ַ,128KB
#define ADDR_FLASH_SECTOR_11	((uint32_t)0x080E0000)	//����11����ʼ��ַ,128KB

uint32_t STMFLASH_ReadWord(uint32_t faddr);
uint8_t STMFLASH_GetFrashSector(uint32_t addr);
void STMFLASH_Write(uint32_t addrWrite, uint32_t *pBuffer, uint32_t numToWrite);
void STMFLASH_Read(uint32_t addrRead, uint32_t *pBuffer, uint32_t NumToRead);



#endif

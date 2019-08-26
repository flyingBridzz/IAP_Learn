#ifndef _STMFLASH_H_
#define _STMFLASH_H_

#include "main.h"

#define STM32_FLASH_BASE 0x08000000 	//STM32 FLASH的起始地址
#define FLASH_WAITETIME  50000          //FLASH等待超时时间

#define	ADDR_FLASH_SECTOR_0		((uint32_t)0x08000000)	//扇区0的起始地址，16KB
#define ADDR_FLASH_SECTOR_1		((uint32_t)0x08004000)	//扇区1的起始地址，16KB
#define	ADDR_FLASH_SECTOR_2		((uint32_t)0x08008000)	//扇区2的起始地址，16KB
#define ADDR_FLASH_SECTOR_3		((uint32_t)0x0800C000)	//扇区3的起始地址，16KB
#define ADDR_FLASH_SECTOR_4		((uint32_t)0x08010000)	//扇区4的起始地址，64KB
#define ADDR_FLASH_SECTOR_5		((uint32_t)0x08020000)	//扇区5的起始地址，128KB
#define ADDR_FLASH_SECTOR_6		((uint32_t)0x08040000)	//扇区6的起始地址，128KB
#define ADDR_FLASH_SECTOR_7		((uint32_t)0x08060000)	//扇区7的起始地址，128KB
#define ADDR_FLASH_SECTOR_8		((uint32_t)0x08080000)	//扇区8的起始地址，128KB
#define ADDR_FLASH_SECTOR_9		((uint32_t)0x080A0000)	//扇区9的起始地址，128KB
#define ADDR_FLASH_SECTOR_10	((uint32_t)0x080C0000)	//扇区10的起始地址,128KB
#define ADDR_FLASH_SECTOR_11	((uint32_t)0x080E0000)	//扇区11的起始地址,128KB

uint32_t STMFLASH_ReadWord(uint32_t faddr);
uint8_t STMFLASH_GetFrashSector(uint32_t addr);
void STMFLASH_Write(uint32_t addrWrite, uint32_t *pBuffer, uint32_t numToWrite);
void STMFLASH_Read(uint32_t addrRead, uint32_t *pBuffer, uint32_t NumToRead);



#endif

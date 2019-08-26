#include "stmflash.h"

/*****************************************
*函数名：	STMFRASH_ReadWord
*参数：		faddr:frash中的32位地址
*返回值：	返回地址中存储的值
*功能：		从frash的指定地址中读取一个字(32位)
*****************************************/
uint32_t STMFLASH_ReadWord(uint32_t faddr)
{
	return *(volatile uint32_t*)faddr;
}

/*****************************************
*函数名：	STMFRASH_GetFrashSector
*参数：		addr:frash中的32位地址
*返回值：	返回地址所在的frash扇区
*功能：		获取地址所在的扇区号
*****************************************/
uint8_t STMFLASH_GetFrashSector(uint32_t addr)
{
	if(addr < ADDR_FLASH_SECTOR_1)return FLASH_SECTOR_0;
	else if(addr < ADDR_FLASH_SECTOR_2)return FLASH_SECTOR_1;
	else if(addr < ADDR_FLASH_SECTOR_3)return FLASH_SECTOR_2;
	else if(addr < ADDR_FLASH_SECTOR_4)return FLASH_SECTOR_3;
	else if(addr < ADDR_FLASH_SECTOR_5)return FLASH_SECTOR_4;
	else if(addr < ADDR_FLASH_SECTOR_6)return FLASH_SECTOR_5;
	else if(addr < ADDR_FLASH_SECTOR_7)return FLASH_SECTOR_6;
	else if(addr < ADDR_FLASH_SECTOR_8)return FLASH_SECTOR_7;
	else if(addr < ADDR_FLASH_SECTOR_9)return FLASH_SECTOR_8;
	else if(addr < ADDR_FLASH_SECTOR_10)return FLASH_SECTOR_9;
	else if(addr < ADDR_FLASH_SECTOR_11)return FLASH_SECTOR_10;
	return FLASH_SECTOR_11;
}

/*****************************************
*函数名：	STMFLASH_Write
*参数：		addrWrite:flash写入地址
					pBuffer:数据指针
					numToWrite:字(32位)数
*返回值：	空
*功能：		向flash指定地址中以字(32位)为单位写入指定长度的数据
*****************************************/
void STMFLASH_Write(uint32_t addrWrite, uint32_t *pBuffer, uint32_t numToWrite)
{
	FLASH_EraseInitTypeDef FLASH_EraseInit;
	HAL_StatusTypeDef FlashStatus = HAL_OK;
	uint32_t SectorError=0;
	uint32_t addrx = addrWrite;
	uint32_t endaddr = addrWrite + numToWrite*4;
	
	if((addrWrite%4) || (addrx < STM32_FLASH_BASE || endaddr > 0x1FFF0000))return ;//不支持向OTP区域写数据
	
	HAL_FLASH_Unlock();
	
	while(addrx < endaddr){
		if(STMFLASH_ReadWord(addrx) != 0xFFFFFFFF){
			FLASH_EraseInit.NbSectors = 1;
			FLASH_EraseInit.Sector = STMFLASH_GetFrashSector(addrx);
			FLASH_EraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;
			FLASH_EraseInit.VoltageRange = FLASH_VOLTAGE_RANGE_3;
			if(HAL_FLASHEx_Erase(&FLASH_EraseInit, &SectorError) != HAL_OK){
				break;
			}
		}else{
			addrx+=4;
		}
		FLASH_WaitForLastOperation(FLASH_WAITETIME);
	}
	FlashStatus = FLASH_WaitForLastOperation(FLASH_WAITETIME);
	if(FlashStatus == HAL_OK){
		while(addrWrite < endaddr){
			if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addrWrite, *pBuffer) != HAL_OK){
				break;
			}
			addrWrite+=4;
			pBuffer++;
		}
	}
	HAL_FLASH_Lock();
}

/*****************************************
*函数名：	STMFLASH_Read
*参数：		addrRead:flash读取地址
					pBuffer:数据指针
					numToWrite:字(32位)数
*返回值：	空
*功能：		从flash指定地址中以字(32位)为单位读取指定长度的数据
*****************************************/
void STMFLASH_Read(uint32_t addrRead, uint32_t *pBuffer, uint32_t NumToRead)
{
	uint32_t i;
	for(i=0;i<NumToRead;i++){
		pBuffer[i] = STMFLASH_ReadWord(addrRead);
		addrRead+=4;
	}
}	


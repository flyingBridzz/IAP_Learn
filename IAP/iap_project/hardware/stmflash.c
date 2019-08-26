#include "stmflash.h"

/*****************************************
*��������	STMFRASH_ReadWord
*������		faddr:frash�е�32λ��ַ
*����ֵ��	���ص�ַ�д洢��ֵ
*���ܣ�		��frash��ָ����ַ�ж�ȡһ����(32λ)
*****************************************/
uint32_t STMFLASH_ReadWord(uint32_t faddr)
{
	return *(volatile uint32_t*)faddr;
}

/*****************************************
*��������	STMFRASH_GetFrashSector
*������		addr:frash�е�32λ��ַ
*����ֵ��	���ص�ַ���ڵ�frash����
*���ܣ�		��ȡ��ַ���ڵ�������
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
*��������	STMFLASH_Write
*������		addrWrite:flashд���ַ
					pBuffer:����ָ��
					numToWrite:��(32λ)��
*����ֵ��	��
*���ܣ�		��flashָ����ַ������(32λ)Ϊ��λд��ָ�����ȵ�����
*****************************************/
void STMFLASH_Write(uint32_t addrWrite, uint32_t *pBuffer, uint32_t numToWrite)
{
	FLASH_EraseInitTypeDef FLASH_EraseInit;
	HAL_StatusTypeDef FlashStatus = HAL_OK;
	uint32_t SectorError=0;
	uint32_t addrx = addrWrite;
	uint32_t endaddr = addrWrite + numToWrite*4;
	
	if((addrWrite%4) || (addrx < STM32_FLASH_BASE || endaddr > 0x1FFF0000))return ;//��֧����OTP����д����
	
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
*��������	STMFLASH_Read
*������		addrRead:flash��ȡ��ַ
					pBuffer:����ָ��
					numToWrite:��(32λ)��
*����ֵ��	��
*���ܣ�		��flashָ����ַ������(32λ)Ϊ��λ��ȡָ�����ȵ�����
*****************************************/
void STMFLASH_Read(uint32_t addrRead, uint32_t *pBuffer, uint32_t NumToRead)
{
	uint32_t i;
	for(i=0;i<NumToRead;i++){
		pBuffer[i] = STMFLASH_ReadWord(addrRead);
		addrRead+=4;
	}
}	


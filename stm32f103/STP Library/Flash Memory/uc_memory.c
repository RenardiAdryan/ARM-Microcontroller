#include <stdio.h>
#include <string.h>
#include "stm32f10x_usart.h"
#include "stm32f10x_flash.h"
#include "uc_memory.h"
/*****************************************************************************
 * Allows to use the internal flash to store non volatile data. To initialize
 * the functionality use the FEE_Init() function. Be sure that by reprogramming
 * of the controller just affected pages will be deleted. In other case the non
 * volatile data will be lost.
******************************************************************************/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Functions -----------------------------------------------------------------*/

uint8_t DataBuf[FEE_PAGE_SIZE];
/*****************************************************************************
*  Delete Flash Space used for user Data, deletes the whole space between
*  RW_PAGE_BASE_ADDRESS and the last uC Flash Page
******************************************************************************/
uint16_t
FEE_Init(void) {
	// unlock flash
	FLASH_Unlock();

	// Clear Flags
	FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);

	return FEE_DENSITY_BYTES;
}
/*****************************************************************************
*  Erase the whole reserved Flash Space used for user Data
******************************************************************************/
void
FEE_Erase (void) {

	int page_num = 0;

	// delete all pages from specified start page to the last page
	do {
		FLASH_ErasePage(FEE_PAGE_BASE_ADDRESS + (page_num * FEE_PAGE_SIZE));
		page_num++;
	} while (page_num < FEE_DENSITY_PAGES);
}
/*****************************************************************************
*  Writes once data byte to flash on specified address. If a byte is already
*  written, the whole page must be copied to a buffer, the byte changed and
*  the manipulated buffer written after PageErase.
*******************************************************************************/
uint16_t
FEE_WriteDataByte (uint16_t Address, uint8_t DataByte) {

	FLASH_Status FlashStatus = FLASH_COMPLETE;

	uint32_t page;
	int i;

	// exit if desired address is above the limit (e.G. under 2048 Bytes for 4 pages)
	if (Address > FEE_DENSITY_BYTES) {
		return 0;
	}

	// calculate which page is affected (Pagenum1/Pagenum2...PagenumN)
	page = (FEE_PAGE_BASE_ADDRESS + FEE_ADDR_OFFSET(Address)) & 0x00000FFF;

	if (page % FEE_PAGE_SIZE) page = page + FEE_PAGE_SIZE;
	page = (page / FEE_PAGE_SIZE) - 1;

	// if current data is 0xFF, the byte is empty, just overwrite with the new one
	if ((*(uint16_t*)(FEE_PAGE_BASE_ADDRESS + FEE_ADDR_OFFSET(Address))) == FEE_EMPTY_WORD) {

		FlashStatus = FLASH_ProgramHalfWord(FEE_PAGE_BASE_ADDRESS + FEE_ADDR_OFFSET(Address), (uint16_t)(0x00FF & DataByte));
	}
	else {

		// Copy Page to a buffer
		memcpy(DataBuf, (uint8_t*)FEE_PAGE_BASE_ADDRESS + (page * FEE_PAGE_SIZE), FEE_PAGE_SIZE); // !!! Calculate base address for the desired page

		// check if new data is differ to current data, return if not, proceed if yes
		if (DataByte == *(uint8_t*)(FEE_PAGE_BASE_ADDRESS + FEE_ADDR_OFFSET(Address))) {
			return 0;
		}

		// manipulate desired data byte in temp data array if new byte is differ to the current
		DataBuf[FEE_ADDR_OFFSET(Address)] = DataByte;

		//Erase Page
		FlashStatus = FLASH_ErasePage(FEE_PAGE_BASE_ADDRESS + page);

		// Write new data (whole page) to flash if data has beed changed
		for(i = 0; i < (FEE_PAGE_SIZE / 2); i++) {
			if ((uint16_t)(0xFF00 | DataBuf[FEE_ADDR_OFFSET(i)]) != 0xFFFF) {
				FlashStatus = FLASH_ProgramHalfWord((FEE_PAGE_BASE_ADDRESS + (page * FEE_PAGE_SIZE)) + (i * 2), (uint16_t)(0xFF00 | DataBuf[FEE_ADDR_OFFSET(i)]));
			}
		}

	}
	return FlashStatus;
}
/*****************************************************************************
*  Read once data byte from a specified address.
*******************************************************************************/
uint8_t
FEE_ReadDataByte (uint16_t Address) {

	uint8_t DataByte = 0xFF;

	// Get Byte from specified address
	DataByte = (*(uint8_t*)(FEE_PAGE_BASE_ADDRESS + FEE_ADDR_OFFSET(Address)));

	return DataByte;
}
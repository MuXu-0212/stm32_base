#include "sys.h"


void Flash_Init(void)
{
	FLASH_Unlock();
	
   /* Clear pending flags (if any) */  
   FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                   FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR); 
	
	FLASH_EraseSector(uwSectorCounter, VoltageRange_3) != FLASH_COMPLETE

	

}

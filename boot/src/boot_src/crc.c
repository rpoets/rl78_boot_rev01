/***********************************************************************************************************************
* File Name        : crc.c
* Component Version: 
* Device(s)        : R7F123FLG3xFB
* Description      : This file implements 
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "crc.h"
#include "typedef.h"
#include "config.h"

/*****************************************************************************
* MACRO DEFINITIONS
*****************************************************************************/
/* polyspace:begin<MISRA-C:19.10:Not a defect:Not a defect.> If the debug feature is disabled, DOUT macros are removed. */
/* polyspace:begin<MISRA-C:19.4:Not a defect:Not a defect.> If the debug feature is disabled, DOUT macros are removed. */
#if CFG_DEBUG
#define DOUT(a)		do { r_printf a; } while(0)
#else
#define DOUT(a)
#endif
extern void r_printf(const char * format, ...);

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/


/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
static uint32_t Crc32Ieee8023Table[256];

/***********************************************************************************************************************
* Function Name: 
* Description  : CRC32 IEEE802.3 x^32+x^26+x^23+x^22+x^16+x^12+x^11+x^10+x^8+x^7+x^5+x^4+x^2+x^1+x^0 0x04C11D87
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void Gen_Crc32Ieee8023Table(void)
{
	uint16_t i;
	uint16_t j;
	uint32_t crc_accum;
	
	for (i=0; i < 256; i++)
	{
		crc_accum = ((uint32_t)i << 24);
		for (j=0; j < 8; j++)
		{
			if (crc_accum & 0x80000000uL)
			{
				crc_accum = (crc_accum << 1) ^ CRC32_IEEE8023_POLY;
			}
			else
			{
				crc_accum = (crc_accum << 1);
			}
			Crc32Ieee8023Table[i] = crc_accum;
		}
	}
}

/***********************************************************************************************************************
* Function Name: 
* Description  : CRC32 BZIP2 Algoritm 0xFFFFFFFF, false, false, 0xFFFFFFFF
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

uint32_t Update_CRC32Ieee8023(uint32_t crc_start_value, uint8_t __far *data_addr, uint16_t length)
{
	uint32_t i;
    uint32_t j;
	
    for (j=0; j < length; j++)
    {		
		//DOUT(("data_addr: 0x%x \n\r", *data_addr));
		i = ((uint32_t) (crc_start_value >> 24) ^ *data_addr++) & 0xFF;		
        crc_start_value = (crc_start_value << 8) ^ Crc32Ieee8023Table[i];
    }
    
    return ~crc_start_value;
}

/***********************************************************************************************************************
* Function Name: 
* Description  : CRC32 IEEE802.3 x^32+x^26+x^23+x^22+x^16+x^12+x^11+x^10+x^8+x^7+x^5+x^4+x^2+x^1+x^0 0x04C11DB7
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
bool CheckAppCRC32(void)
{
	bool crc32_check_flag = false;
	uint32_t app_crc32_calcresult = 0;
	
	Gen_Crc32Ieee8023Table();		
	
	//check_codeflash();
	
	app_crc32_calcresult = Update_CRC32Ieee8023(0xFFFFFFFFuL, (uint8_t __far *)APP_CF_START_ADDRESS, APP_CF_SIZE);
	DOUT(("APP CRC32 value: 0x%x \n\r", (app_crc32_calcresult >> 16) & 0xFFFF));
	DOUT(("APP CRC32 value: 0x%x \n\r", app_crc32_calcresult & 0xFFFF));
	
	return crc32_check_flag;	
	
}

/***********************************************************************************************************************
* Function Name: 
* Description  : CRC32 IEEE802.3 x^32+x^26+x^23+x^22+x^16+x^12+x^11+x^10+x^8+x^7+x^5+x^4+x^2+x^1+x^0 0x04C11DB7
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void check_codeflash(void)
{
	uint8_t tmp = 0;	
	
	DOUT(("start~~ \n\r"));		

	for (uint32_t i = (APP_CF_START_ADDRESS + 44u*1024u); i < 0x0000FFFFuL ; i++) 
	{
		tmp = (*(uint8_t __far *)i);
		
		//if(tmp != 0xFF)
		DOUT(("address 0x%x, data 0x%x \n\r", (uint16_t)i, tmp));
#if false		
		/* Not working*/
		DOUT(("address 0x%x, data 0x%x \n\r", i, tmp));
		/* working*/
		DOUT(("address 0x%x, ", i));
		DOUT(("data 0x%x \n\r", tmp));
#endif
	}
	DOUT(("end \n\r"));	
}














/***********************************************************************************************************************
* Function Name: 
* Description  : IAR CRC32 Example
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

bool CheckAppCRC32_woTable(void)
{
	bool crc32_check_flag = false;
	uint32_t app_crc32_calcresult = 0;		
	
#if false
	uint8_t tmp[4] = {0x12, 0x34, 0xab, 0xcd};	
	
	app_crc32_calcresult = crc(0xFFFFFFFFuL, &tmp[0], 4);
	//app_crc32_calcresult = crc(0xFFFFFFFFuL, (uint8_t __far *)APP_CF_START_ADDRESS, APP_CF_SIZE);
		
	uint16_t up = (app_crc32_calcresult >> 16) & 0xFFFF;
	uint16_t down = app_crc32_calcresult & 0xFFFF;
	
	DOUT(("0x1234abcd CRC32 up result: 0x%x \n\r", up));	
	DOUT(("0x1234abcd CRC32 down result: 0x%x \n\r", down));
#endif

	app_crc32_calcresult = crc(0xFFFFFFFFuL, (uint8_t __far *)APP_CF_START_ADDRESS, APP_CF_SIZE);
	
	DOUT(("APP CRC32 value: 0x%x \n\r", (app_crc32_calcresult >> 16) & 0xFFFF));
	DOUT(("APP CRC32 value: 0x%x \n\r", app_crc32_calcresult & 0xFFFF));

	return crc32_check_flag;	
}


/***********************************************************************************************************************
* Function Name: 
* Description  : CRC32 IEEE802.3 x^32+x^26+x^23+x^22+x^16+x^12+x^11+x^10+x^8+x^7+x^5+x^4+x^2+x^1+x^0 0x04C11DB7
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
uint32_t crc_impl(uint32_t sum, uint8_t *p, uint32_t len)
{
	while (len--)
	{
		uint8_t byte = *p++;

		for (int i = 0; i < 8; ++i)
		{
			uint32_t osum = sum;

			sum <<= 1;

			if (byte & 0x80)
			sum |= 1 ;

			if (osum & 0x80000000)
			sum ^= 0x4C11DB7; // the polynominal

			byte <<= 1;
		}
	}
	return ~sum;
}

static const uint8_t zeroes[] = { 0, 0, 0, 0 };

uint32_t crc(uint32_t sum, uint8_t *p, uint32_t len)
{
	return crc_impl(crc_impl(sum, p, len), (uint8_t *)zeroes, 4);
}
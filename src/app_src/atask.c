/***********************************************************************************************************************
* File Name        : task.c
* Component Version: 
* Device(s)        : R7F123FLG3xFB
* Description      : This file implements 
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "atask.h"
#include "config.h"
#include "atypedef.h"
#include <string.h>
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
#pragma section bss bootpara
bootpara_t bootpara;
#pragma section

#pragma section const fidm_version_id
const fidm_version_id_t fidm_version_id = {HW_VERSION, SW_VERSION, TOUCH_ID, DISPLAY_ID};
#pragma section


/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: INTC_intp1_interrupt
* Description  : call test from APP
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
uint16_t read_bl_session_key(void)
{
	//return ((volatile __far bootpara_t*)CFG_ADDR_BOOTPARA) -> bl_session_key;
	return bootpara.bl_session_key;
}

/***********************************************************************************************************************
* Function Name: INTC_intp1_interrupt
* Description  : call test from APP
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
uint8_t read_bl_app_mode(void)
{
	//return ((volatile __far bootpara_t*)CFG_ADDR_BOOTPARA) -> bl_app_mode_notice; 
	return bootpara.bl_app_mode_notice;
}

/***********************************************************************************************************************
* Function Name: 
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void sw_reset(void)
{
	bootpara.reset_request_app = SW_RST_SIGNATURE; 
	/* Illegal instruction execution for RL78! Resets the MCU. */
	static const uint8_t illegal_Instruction = 0xFF;
	void (*dummy)(void) = (void (*)(void))&illegal_Instruction;
	dummy();
}

#if false
#pragma inline_asm sw_reset
void sw_reset(void)
{
	asm("db 0xFF");
}
#endif


/***********************************************************************************************************************
* Function Name: 
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void write_bl_session_key(uint16_t data)
{
	//((volatile __far bootpara_t*)CFG_ADDR_BOOTPARA) -> bl_session_key = data; 
	bootpara.bl_session_key = data;
}

/***********************************************************************************************************************
* Function Name: 
* Description  : 0xBB: Boot mode, 0xAA: App mode
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void bl_app_mode_config(uint8_t code)
{   
	//((volatile __far bootpara_t*)CFG_ADDR_BOOTPARA) -> bl_app_mode_notice = code; 
	bootpara.bl_app_mode_notice = code; 
}

/***********************************************************************************************************************
* Function Name: 
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
uint8_t ClearBootparaValue(void)
{
	memset(&bootpara, 0, sizeof(bootpara_t));	
	return E_OK;	
}


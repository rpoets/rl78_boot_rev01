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
#include "task.h"
#include "typedef.h"
#include "config.h"
#include <string.h>	//for memset()
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
bootpara_t bootpara; //why volatile cause warning?
#pragma section

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
volatile bool SWkey_flag = false;
extern bool CheckAppCRC32(void);

/***********************************************************************************************************************
* Function Name: INTC_intp1_interrupt
* Description  : call test from APP
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#if 1
void __near INTC_intp1_interrupt(void)
{
    /* Start user code for r_Config_INTC_intp1_interrupt. Do not edit comment generated here */
	SWkey_flag = true;
    /* End user code. Do not edit comment generated here */
}
#endif
 
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
uint8_t bl_app_mode_check(void)
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
#if false
void reset_cause(void)
{	
	/* Reset Cause Test 24-03-04 */	
	/* RESET input, reset by power-on-reset(POR) circuit, and reading the RESF register 
	   clear TRAP, WDCLRF, IAWRF, and LVIRF flags. */
	bootpara.reset_cause = RESF;
	DOUT(("POCRES: 0x%x, b4:CLKRF(0), bit0:POCRES0(0)\n\r", POCRES));
	DOUT(("RESF: 0x%x, b7:TRAP(0), b4:WDCLRF(0),b1:IAWRF(0), b0:LVIRF(0)\n\r", reg_resf));		
	
	
	if(0U == POCRES0)
	{
		DOUT(("POR: bootpara init! \n\r"));
		bootpara.bl_app_mode_notice = 0;
		bootpara.bl_session_key = 0;
		bootpara.reset_cause = 0;
		bootpara.reset_count = 0;
	}
	if(_BIT7 == (reg_resf & _BIT7) && SW_RST_SIGNATURE != bootpara.reset_cause)
		DOUT(("Illegal instructiion internal reset! \n\r"));	
	if(_BIT7 == (reg_resf & _BIT7) && SW_RST_SIGNATURE == bootpara.reset_cause)
		{
			DOUT(("SW reset! \n\r"));	
			bootpara.reset_cause = 0x00;
		}
	if(_BIT4 == (reg_resf & _BIT4) && 1U == CLKRF)
		DOUT(("CLK monitor internal reset! \n\r"));
	if(_BIT4 == (reg_resf & _BIT4) && 0U == CLKRF)
		DOUT(("WDT internal reset! \n\r"));		
	if(_BIT1 == (reg_resf & _BIT1))
		DOUT(("Illegal Memory internal reset! \n\r"));	
	if(_BIT0 == (reg_resf & _BIT0))
		DOUT(("Voltage Detector internal reset! \n\r"));	
		
	POCRES0 = _BIT0;
	/* For confirming whether a reset was by the power-on reset (POR) circuit, 
	   the POCRES0 must be set to 1 beforehand. */
}
/***********************************************************************************************************************/
#endif
/***********************************************************************************************************************
* Function Name: 
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
branch_mode_ret_e startup_branch(void)
{	
	branch_mode_ret_e branch_mode_ret = ENUM_RET_STAY_BL;
	bool app_crc_check_flag = false;
	
	/* RESET input, reset by power-on-reset(POR) circuit, and reading the RESF register 
	   clear TRAP, WDCLRF, IAWRF, and LVIRF flags. */
	bootpara.bl_resf = RESF;
	DOUT(("POCRES: 0x%x, b4:CLKRF(0), bit0:POCRES0(0)\n\r", POCRES));
	DOUT(("RESF: 0x%x, b7:TRAP(0), b4:WDCLRF(0),b1:IAWRF(0), b0:LVIRF(0)\n\r", bootpara.bl_resf));		
	
	/* 1. S/W reset && bl_session_key != 0 */
	if (_BIT7 == (bootpara.bl_resf & _BIT7) && SW_RST_SIGNATURE == bootpara.reset_request_app && bootpara.bl_session_key)
	{
		DOUT(("SW reset! \n\r"));	
		bootpara.reset_request_app = 0x00;		
		branch_mode_ret = ENUM_RET_STAY_BL;
	}	
	else
	{	/* 2. APP CRC OK check */
		//app_crc_check_flag = CheckAppCRC32();
		if (false == app_crc_check_flag)
		{
			branch_mode_ret = ENUM_RET_RUN_APP;
		}
		else
		{   /* 3. POR check */
			if (0U == bootpara.bl_pocres)
			{
				/* POR Reset */
				DOUT(("POR: bootpara clear! \n\r"));
				memset(&bootpara, 0, sizeof(bootpara_t));
				branch_mode_ret = ENUM_RET_STAY_BL;	
			}
			else
			{
				branch_mode_ret = ENUM_RET_STAY_BL;	
			}
		}		
	}			
	POCRES0 = _BIT0;
	/* For confirming whether a reset was by the power-on reset (POR) circuit, 
	   the POCRES0 must be set to 1 beforehand. */
	
	return branch_mode_ret;
}

/***********************************************************************************************************************
* Function Name: 
* Description  : 
* Arguments    : SW_VERSION in App Flash 0x4100(const)
* Return Value : None
***********************************************************************************************************************/
uint16_t read_hw_version(void)
{
	 return (*(volatile __near unsigned short *)0x4100); 	
}


/***********************************************************************************************************************
* Function Name: 
* Description  : 
* Arguments    : None
* Return Value : SW_VERSION in App Flash 0x4102(const)
***********************************************************************************************************************/
uint16_t read_sw_version(void)
{
	 return (*(volatile __near unsigned short *)0x4102); 	
}

/***********************************************************************************************************************
* Function Name: 
* Description  : 
* Arguments    : TOUCH ID in App Flash 0x4104(const)
* Return Value : None
***********************************************************************************************************************/
uint8_t read_touch_id(void)
{
	 return (*(volatile __near unsigned char *)0x4104); 
}

/***********************************************************************************************************************
* Function Name: 
* Description  : 
* Arguments    : DISPLAY ID in App Flash 0x4105(const)
* Return Value : None
***********************************************************************************************************************/
uint8_t read_display_id(void)
{
	 return (*(volatile __near unsigned char *)0x4105);
}


#pragma inline_asm ForceReset
/*********************************************************************************************************************/
/**
 *  Reset the CPU.
 *  
 *  @param[in]      -
 *  @return         ---
 */
/*********************************************************************************************************************/
__far void ForceReset(void)
{
	/* Set illegal instruction to request internal reset */
    .DB 255
}


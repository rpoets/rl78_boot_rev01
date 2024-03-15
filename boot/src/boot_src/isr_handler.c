/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "typedef.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma interrupt isr_jump_uart1_handler(vect=INTST1)
//#pragma interrupt r_Config_UART1_interrupt_receive(vect=INTSR1)
#pragma interrupt isr_jump_intp1_handler(vect=INTP1)

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile bootpara_t bootpara;
extern void __near if_r_Config_UART1_interrupt_send(void);
extern void __near if_r_Config_INTC_intp1_interrupt(void);

/***********************************************************************************************************************
* Function Name: 
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near isr_jump_uart1_handler(void)
{
	if(bootpara.bl_app_mode_notice == BL_SIGNATURE)
	{
		if_r_Config_UART1_interrupt_send();
	}
	else
	{		
		//void (*p_func)(void) = (void (*)(void))(VECTOR_UART1_SEND);
		//p_func();
		
		((void (*)(void))VECTOR_UART1_SEND)();
	}
}
/***********************************************************************************************************************
* Function Name: interrupt isr_jump_handler
* Description  : This function is INTP1 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near isr_jump_intp1_handler(void)
{	
	if(bootpara.bl_app_mode_notice == BL_SIGNATURE)
	{
		if_r_Config_INTC_intp1_interrupt();
	}
	else
	{
		//void (*p_func)(void) = (void (*)(void))(VECTOR_INTP1);
		//(*p_func)();
				
		((void (*)(void))VECTOR_INTP1)();
	}
}

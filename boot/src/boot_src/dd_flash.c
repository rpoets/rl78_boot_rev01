/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "typedef.h"
#include "r_rfd.h"
#include "dd_flash.h"
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
Global variables and functions
***********************************************************************************************************************/
extern R_RFD_FAR_FUNC e_rfd_ret_t R_RFD_Init(uint8_t i_u08_cpu_frequency);
extern R_RFD_FAR_FUNC e_rfd_ret_t R_RFD_SetFlashMemoryMode(e_rfd_flash_memory_mode_t i_e_flash_mode);
extern R_RFD_FAR_FUNC void R_RFD_BlankCheckCodeFlashReq(uint16_t i_u16_block_number);
extern R_RFD_FAR_FUNC e_rfd_ret_t R_RFD_CheckCFDFSeqEndStep1(void);
extern R_RFD_FAR_FUNC e_rfd_ret_t R_RFD_CheckCFDFSeqEndStep2(void);
extern R_RFD_FAR_FUNC void R_RFD_GetSeqErrorStatus(uint8_t __near * onp_u08_error_status);
extern R_RFD_FAR_FUNC void R_RFD_ClearSeqRegister(void);
extern R_RFD_FAR_FUNC void R_RFD_EraseCodeFlashReq(uint16_t i_u16_block_number);
extern R_RFD_FAR_FUNC void R_RFD_IVerifyCodeFlashReq(uint16_t i_u16_block_number);
extern R_RFD_FAR_FUNC void R_RFD_WriteCodeFlashReq(uint32_t i_u32_start_addr, uint8_t __near * inp_u08_write_data);

/***********************************************************************************************************************
* Function Name: BL_Code_INITSCT
* Description  : ROM -> RAM Copy
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#define BLFD_PSEC_MAX 3 /* The number of the program sections to copy */
#define BLFD_DSEC_MAX 1 /* The number of the data sections to copy */

const struct blfd_dsec_t {
        char __far *d_rom_sectop; /* Copy source section top address */
        char __far *d_rom_secend; /* Copy source section end address+1 */
        char __near *d_ram_sectop; /* Copy destination section top address */
} blfd_dsec_table[BLFD_DSEC_MAX] = {
        {__sectop("RFD_DATA_n"),
         __secend("RFD_DATA_n"),
         (char __near *)__sectop("RFD_DATA_nR")}};

	 
const struct blfd_psec_t {
        char __far *p_rom_sectop; /* Copy source section top address */
        char __far *p_rom_secend; /* Copy source section end address+1 */
        char __near *p_ram_sectop; /* Copy destination section top address */
} blfd_psec_table[BLFD_PSEC_MAX] = {
        {__sectop("RFD_CMN_f"),
         __secend("RFD_CMN_f"),
         (char __near *)__sectop("RFD_CMN_fR")},
        {__sectop("RFD_CF_f"),
         __secend("RFD_CF_f"),		 
         (char __near *)__sectop("RFD_CF_fR")},       
        {__sectop("BLFD_CF_f"),
         __secend("BLFD_CF_f"),
         (char __near *)__sectop("BLFD_CF_fR")}};

R_RFD_FAR_FUNC void BL_Code_INITSCT(void)
{
        unsigned int i;
        char __far *rom_p;
        char __near *ram_p;

        for (i = 0; i < BLFD_DSEC_MAX; i++) {
                rom_p = blfd_dsec_table[i].d_rom_sectop;
                ram_p = blfd_dsec_table[i].d_ram_sectop;
                for ( ; rom_p != blfd_dsec_table[i].d_rom_secend; rom_p++, ram_p++) {
                        *ram_p = *rom_p;
                }
        }	
        for (i = 0; i < BLFD_PSEC_MAX; i++) {
                rom_p = blfd_psec_table[i].p_rom_sectop;
                ram_p = blfd_psec_table[i].p_ram_sectop;
                for ( ; rom_p != blfd_psec_table[i].p_rom_secend; rom_p++, ram_p++) {
                        *ram_p = *rom_p;
                }
        }
}

/***********************************************************************************************************************
* Function Name: 
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void test_BlFlashDriver(void)
{
	e_sample_ret_t l_e_sam_ret_value = SAMPLE_ENUM_RET_STS_OK; 
	
	uint8_t l_au08_write_data[64];
	 /* Create writing data */
    for (uint16_t i = 0u; i < 64u; i++)
    {
        l_au08_write_data[i] = (uint8_t)(i & SAMPLE_VALUE_U08_MASK1_8BIT);		
    }	
		
	l_e_sam_ret_value = (e_sample_ret_t)InitBlFlashDriver();	
	if (l_e_sam_ret_value)	
	{
		DOUT(("Error: InitBlFlashDriver 0x%x", l_e_sam_ret_value));
	}
	else
	{
		l_e_sam_ret_value = AppFlashEraseBlock(APP_CF_START_ADDRESS, 48);
		if (l_e_sam_ret_value)	
		{
			DOUT(("Error: AppFlashEraseBlock 0x%x", l_e_sam_ret_value));
		}
		else
		{
			l_e_sam_ret_value = AppFlashWrite64B(APP_CF_START_ADDRESS + 64, l_au08_write_data);
			if (l_e_sam_ret_value)	
			{
				DOUT(("Error: AppFlashWrite64B 0x%x", l_e_sam_ret_value));
			}
		}
		
	}		
}



/***********************************************************************************************************************
* Function Name: 
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
uint16_t InitBlFlashDriver(void)
{
	/* Local variable definition */
    e_rfd_ret_t    l_e_rfd_status_flag;
    e_sample_ret_t l_e_sam_ret_value;    
    uint32_t       l_mclk_freq;
		
    BL_Code_INITSCT();

    l_mclk_freq = R_BSP_GetFclkFreqHz();
    l_mclk_freq = (l_mclk_freq + L_MCLK_ROUNDUP_VALUE)/L_MCLK_FREQ_1MHz;    
    
    /* Check whether HOCO is already started */
    if (SAMPLE_VALUE_U01_MASK0_1BIT == HIOSTOP)
    {
         l_e_rfd_status_flag = R_RFD_Init((uint8_t)l_mclk_freq);
        
        if (R_RFD_ENUM_RET_STS_OK == l_e_rfd_status_flag)
        {
			l_e_sam_ret_value = SAMPLE_ENUM_RET_STS_OK;
        }
        else
        {
            /* Failed to initialize RFD */
            l_e_sam_ret_value = SAMPLE_ENUM_RET_ERR_PARAMETER;
        }
	}
	else
    {
        /* HOCO is not started */
        l_e_sam_ret_value = SAMPLE_ENUM_RET_ERR_CONFIGURATION;
    }		
		
	return ((uint16_t)l_e_sam_ret_value);   
}


#pragma section text BLFD_CF

/***********************************************************************************************************************
* Function Name: 
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
R_RFD_FAR_FUNC e_sample_ret_t AppFlashErase(uint32_t i_u32_start_addr)
{
    /* Local variable definition */
	e_rfd_ret_t    l_e_rfd_ret_status;
    e_sample_ret_t l_e_sam_ret_status;
    e_sample_ret_t l_e_sam_ret_value;
    bool           l_e_sam_error_flag;
    uint16_t       l_u16_block_number;
   
    
    /* Set local variables */
    l_e_sam_ret_value           = SAMPLE_ENUM_RET_STS_OK;
    l_e_sam_error_flag          = false;
    
    /* This expression (actual block number) never exceeds the range of casting uint16_t */
    l_u16_block_number          = (uint16_t)(i_u32_start_addr >> SAMPLE_VALUE_U08_SHIFT_ADDR_TO_BLOCK_CF);
   
    
    /******************************************************************************************************************
     * Set the code flash programming mode
     *****************************************************************************************************************/
    l_e_rfd_ret_status = R_RFD_SetFlashMemoryMode(R_RFD_ENUM_FLASH_MODE_CODE_PROGRAMMING);
    
    if (R_RFD_ENUM_RET_STS_OK != l_e_rfd_ret_status)
    {
        l_e_sam_error_flag = true;
        l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_MODE_MISMATCHED;
    }
    else
    {
        /* No operation */
    }
    
    /******************************************************************************************************************
     * BLANKCHECK -> ERASE
     *****************************************************************************************************************/
    if (false == l_e_sam_error_flag)
    {
        /* BLANKCHECK (1 block) */
        R_RFD_BlankCheckCodeFlashReq(l_u16_block_number);
        l_e_sam_ret_status = BL_CheckCFDFSeqEnd();
        
        if (SAMPLE_ENUM_RET_ERR_ACT_BLANKCHECK == l_e_sam_ret_status)
        {
            /* ERASE (1 block) */
            R_RFD_EraseCodeFlashReq(l_u16_block_number);
            l_e_sam_ret_status = BL_CheckCFDFSeqEnd();
            
            if (SAMPLE_ENUM_RET_STS_OK != l_e_sam_ret_status)
            {
                l_e_sam_error_flag = true;
                l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_CMD_ERASE;
            }
            else
            {
                /* No operation */
            }
        }
        else if (SAMPLE_ENUM_RET_STS_OK != l_e_sam_ret_status)
        {
            l_e_sam_error_flag = true;
            l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_CMD_BLANKCHECK;
        }
        else
        {
            /* No operation */
        }
    }
    else /* true == l_e_sam_error_flag */
    {
        /* No operation */
    }
    
     /******************************************************************************************************************
     * Set non-programmable mode
     *****************************************************************************************************************/
    l_e_rfd_ret_status = R_RFD_SetFlashMemoryMode(R_RFD_ENUM_FLASH_MODE_CODE_TO_NONPROGRAMMABLE);
    
    if (R_RFD_ENUM_RET_STS_OK != l_e_rfd_ret_status)
    {
        l_e_sam_error_flag = true;
        l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_MODE_MISMATCHED;
    }
    else
    {
        /* No operation */
    }
    
    return (l_e_sam_ret_value);
}

/***********************************************************************************************************************
* Function Name: 
* Description  : 1Block = 1024Byte
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
R_RFD_FAR_FUNC e_sample_ret_t AppFlashEraseBlock(uint32_t i_u32_start_addr, uint16_t i_u16_block_nums)
{
	/* Local variable definition */
	e_rfd_ret_t    l_e_rfd_ret_status;
    e_sample_ret_t l_e_sam_ret_status;
    e_sample_ret_t l_e_sam_ret_value;	
    bool           l_e_sam_error_flag;
    uint16_t       l_u16_block_number;
   
    
    /* Set local variables */
    l_e_sam_ret_value           = SAMPLE_ENUM_RET_STS_OK;	
    l_e_sam_error_flag          = false;
    
    /* This expression (actual block number) never exceeds the range of casting uint16_t */
    l_u16_block_number          = (uint16_t)(i_u32_start_addr >> SAMPLE_VALUE_U08_SHIFT_ADDR_TO_BLOCK_CF);
   
    
   /******************************************************************************************************************
     * Set the code flash programming mode
     *****************************************************************************************************************/
    l_e_rfd_ret_status = R_RFD_SetFlashMemoryMode(R_RFD_ENUM_FLASH_MODE_CODE_PROGRAMMING);
    
    if (R_RFD_ENUM_RET_STS_OK != l_e_rfd_ret_status)
    {
        l_e_sam_error_flag = true;
        l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_MODE_MISMATCHED;
    }
    else
    {
        /* No operation */
    }
    	
    /******************************************************************************************************************
     * BLANKCHECK -> ERASE
     *****************************************************************************************************************/
    if (false == l_e_sam_error_flag)
    {
		for (uint16_t i = 0; i < i_u16_block_nums; i++)
		{
	        /* BLANKCHECK (1 block) */
	        R_RFD_BlankCheckCodeFlashReq(l_u16_block_number + i);
	        l_e_sam_ret_status = BL_CheckCFDFSeqEnd();
	        
	        if (SAMPLE_ENUM_RET_ERR_ACT_BLANKCHECK == l_e_sam_ret_status)
	        {
	            /* ERASE (1 block) */
	            R_RFD_EraseCodeFlashReq(l_u16_block_number + i);
	            l_e_sam_ret_status = BL_CheckCFDFSeqEnd();
	            
	            if (SAMPLE_ENUM_RET_STS_OK != l_e_sam_ret_status)
	            {
	                l_e_sam_error_flag = true;
	                l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_CMD_ERASE;
	            }
	            else
	            {
	                /* No operation */
	            }
	        }
	        else if (SAMPLE_ENUM_RET_STS_OK != l_e_sam_ret_status)
	        {
	            l_e_sam_error_flag = true;
	            l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_CMD_BLANKCHECK;
				break;
	        }
	        else
	        {
	            /* No operation */
	        }
		}
    }
    else /* true == l_e_sam_error_flag */
    {
        /* No operation */
    }
	
    /******************************************************************************************************************
     * Set non-programmable mode
     *****************************************************************************************************************/
    l_e_rfd_ret_status = R_RFD_SetFlashMemoryMode(R_RFD_ENUM_FLASH_MODE_CODE_TO_NONPROGRAMMABLE);
    
    if (R_RFD_ENUM_RET_STS_OK != l_e_rfd_ret_status)
    {
        l_e_sam_error_flag = true;
        l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_MODE_MISMATCHED;
    }
    else
    {
        /* No operation */
    }
    
    return (l_e_sam_ret_value);	
}


/***********************************************************************************************************************
* Function Name: 
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
R_RFD_FAR_FUNC e_sample_ret_t AppFlashWrite64B(uint32_t i_u32_start_addr, uint8_t __near * inp_u08_write_data)
{
	/* Local variable definition */   
	e_rfd_ret_t    l_e_rfd_ret_status;
    e_sample_ret_t l_e_sam_ret_status;
    e_sample_ret_t l_e_sam_ret_value;
    bool           l_e_sam_error_flag;
    uint16_t       l_u16_count;
    uint16_t       l_u16_block_number;
    uint32_t       l_u32_check_write_data_addr;

	
	    
    /* Set local variables */
    l_e_sam_ret_value           = SAMPLE_ENUM_RET_STS_OK;	
    l_e_sam_error_flag          = false;
	
	    
    /* This expression (actual block number) never exceeds the range of casting uint16_t */
    l_u16_block_number          = (uint16_t)(i_u32_start_addr >> SAMPLE_VALUE_U08_SHIFT_ADDR_TO_BLOCK_CF);
    l_u32_check_write_data_addr = i_u32_start_addr;
    
   /******************************************************************************************************************
     * Set the code flash programming mode
     *****************************************************************************************************************/
    l_e_rfd_ret_status = R_RFD_SetFlashMemoryMode(R_RFD_ENUM_FLASH_MODE_CODE_PROGRAMMING);
    
    if (R_RFD_ENUM_RET_STS_OK != l_e_rfd_ret_status)
    {
        l_e_sam_error_flag = true;
        l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_MODE_MISMATCHED;
    }
    else
    {
        /* No operation */
    }
   
    /******************************************************************************************************************
     * WRITE
     *****************************************************************************************************************/
    if (false == l_e_sam_error_flag)
    {
        for (l_u16_count = 0u; l_u16_count < 64u; l_u16_count += 4u)
        {
            R_RFD_WriteCodeFlashReq(i_u32_start_addr + l_u16_count, &inp_u08_write_data[l_u16_count]);
            l_e_sam_ret_status = BL_CheckCFDFSeqEnd();
            
            if (SAMPLE_ENUM_RET_STS_OK != l_e_sam_ret_status)
            {
                l_e_sam_error_flag = true;
                l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_CMD_WRITE;
                break;
            }
            else
            {
                /* No operation */
            }
        }
    }
    else /* true == l_e_sam_error_flag */
    {
        /* No operation */
    } 
    /******************************************************************************************************************
     * IVERIFY (internal verify)
     *****************************************************************************************************************/
    if (false == l_e_sam_error_flag)
    {
        /* IVERIFY (1 block) */
        R_RFD_IVerifyCodeFlashReq(l_u16_block_number);
        l_e_sam_ret_status = BL_CheckCFDFSeqEnd();
        
        if (SAMPLE_ENUM_RET_STS_OK != l_e_sam_ret_status)
        {
            l_e_sam_error_flag = true;
            l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_CMD_IVERIFY;
        }
        else
        {
            /* No operation */
        }
    }
    else /* true == l_e_sam_error_flag */
    {
        /* No operation */
    }
    
     /******************************************************************************************************************
     * Set non-programmable mode
     *****************************************************************************************************************/
    l_e_rfd_ret_status = R_RFD_SetFlashMemoryMode(R_RFD_ENUM_FLASH_MODE_CODE_TO_NONPROGRAMMABLE);
    
    if (R_RFD_ENUM_RET_STS_OK != l_e_rfd_ret_status)
    {
        l_e_sam_error_flag = true;
        l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_MODE_MISMATCHED;
    }
    else
    {
        /* No operation */
    }
 
    /******************************************************************************************************************
     * Check write data
     *****************************************************************************************************************/
   	if (false == l_e_sam_error_flag)
    {
        for (l_u16_count = 0u; l_u16_count < 64u; l_u16_count++)
        {
            if (inp_u08_write_data[l_u16_count] != (*(uint8_t __far *)l_u32_check_write_data_addr))
            {
                l_e_sam_error_flag = true;
                l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_CHECK_WRITE_DATA;
                break;
            }
            else
            {
                /* No operation */
            }
            l_u32_check_write_data_addr++;
        }
    }
    else /* true == l_e_sam_error_flag */
    {
        /* No operation */
    }	 
	
    return (l_e_sam_ret_value);		
}


/*********************************************************************************************************************/
/**
 *  Check the state of the code/data flash memory sequencer and result.
 *  
 *  @param[in]      -
 *  @return         Execution result status
 *                  - SAMPLE_ENUM_RET_STS_OK             : Successful completion
 *                  - SAMPLE_ENUM_RET_ERR_CFDF_SEQUENCER : CF/DF sequencer error
 *                  - SAMPLE_ENUM_RET_ERR_ACT_ERASE      : Erase action error
 *                  - SAMPLE_ENUM_RET_ERR_ACT_WRITE      : Write action error
 *                  - SAMPLE_ENUM_RET_ERR_ACT_BLANKCHECK : Blankcheck action error
 *                  - SAMPLE_ENUM_RET_ERR_ACT_IVERIFY    : IVerify action error
 */
/*********************************************************************************************************************/
R_RFD_FAR_FUNC e_sample_ret_t BL_CheckCFDFSeqEnd(void)
{
    /* Local variable definition */
    e_sample_ret_t l_e_sam_ret_value;
    uint8_t        l_u08_status_flag;
    
    /* Set local variables */
    l_e_sam_ret_value = SAMPLE_ENUM_RET_STS_OK;
    
    /* Sequencer busy loop step1 */
    while (R_RFD_ENUM_RET_STS_BUSY == R_RFD_CheckCFDFSeqEndStep1())
    {
        /* No operation */
        /* It is possible to write the program for detecting timeout here as necessity requires */
    }
    
    /* Sequencer busy loop step2 */
    while (R_RFD_ENUM_RET_STS_BUSY == R_RFD_CheckCFDFSeqEndStep2())
    {
        /* No operation */
        /* It is possible to write the program for detecting timeout here as necessity requires */
    }
    
    /* Action error check */
    R_RFD_GetSeqErrorStatus(&l_u08_status_flag);
    
    /* Check error status */
    if (SAMPLE_VALUE_U08_MASK0_8BIT != (l_u08_status_flag & SAMPLE_VALUE_U08_MASK1_FSQ_STATUS_ERR_CFDF_SEQUENCER))
    {
        /* Set return value */
        l_e_sam_ret_value = SAMPLE_ENUM_RET_ERR_CFDF_SEQUENCER;
    }
    else if (SAMPLE_VALUE_U08_MASK0_8BIT != (l_u08_status_flag & SAMPLE_VALUE_U08_MASK1_FSQ_STATUS_ERR_ERASE))
    {
        /* Set return value */
        l_e_sam_ret_value = SAMPLE_ENUM_RET_ERR_ACT_ERASE;
    }
    else if (SAMPLE_VALUE_U08_MASK0_8BIT != (l_u08_status_flag & SAMPLE_VALUE_U08_MASK1_FSQ_STATUS_ERR_WRITE))
    {
        /* Set return value */
        l_e_sam_ret_value = SAMPLE_ENUM_RET_ERR_ACT_WRITE;
    }
    else if (SAMPLE_VALUE_U08_MASK0_8BIT != (l_u08_status_flag & SAMPLE_VALUE_U08_MASK1_FSQ_STATUS_ERR_BLANKCHECK))
    {
        /* Set return value */
        l_e_sam_ret_value = SAMPLE_ENUM_RET_ERR_ACT_BLANKCHECK;
    }
    else if (SAMPLE_VALUE_U08_MASK0_8BIT != (l_u08_status_flag & SAMPLE_VALUE_U08_MASK1_FSQ_STATUS_ERR_IVERIFY))
    {
        /* Set return value */
        l_e_sam_ret_value = SAMPLE_ENUM_RET_ERR_ACT_IVERIFY;
    }
    else
    {
        /* Set return value */
        l_e_sam_ret_value = SAMPLE_ENUM_RET_STS_OK;
    }
    
    /* Clear sequencer registers */
    R_RFD_ClearSeqRegister();
    
    return (l_e_sam_ret_value);
}

/**********************************************************************************************************************
 End of function Sample_CheckCFDFSeqEnd
 *********************************************************************************************************************/

 
 
 
 

/*********************************************************************************************************************/
/**
 *  Sample function for code flash control.
 *  BlankCheck -> Erase -> Write -> IVerify
 *  
 *  @param[in]      i_u32_start_addr : 
 *                    Command start address (The start address of the block)
 *  @param[in]      i_u16_write_data_length : 
 *                    Write data length (MAX : 1 block size) 
 *                    (It must be a multiple of 4.)
 *  @param[in]      inp_u08_write_data : 
 *                    Write data pointer
 *  @return         Execution result status
 *                  - SAMPLE_ENUM_RET_STS_OK               : Successful completion
 *                  - SAMPLE_ENUM_RET_ERR_MODE_MISMATCHED  : Mode mismatched error
 *                  - SAMPLE_ENUM_RET_ERR_CHECK_WRITE_DATA : Check write data error
 *                  - SAMPLE_ENUM_RET_ERR_CMD_ERASE        : Erase command error
 *                  - SAMPLE_ENUM_RET_ERR_CMD_WRITE        : Write command error
 *                  - SAMPLE_ENUM_RET_ERR_CMD_BLANKCHECK   : Blankcheck command error
 *                  - SAMPLE_ENUM_RET_ERR_CMD_IVERIFY      : IVerify command error
 */
/*********************************************************************************************************************/
R_RFD_FAR_FUNC e_sample_ret_t BL_CodeFlashControl(uint32_t i_u32_start_addr, uint16_t i_u16_write_data_length, uint8_t __near * inp_u08_write_data)
{
    /* Local variable definition */
    e_rfd_ret_t    l_e_rfd_ret_status;
    e_sample_ret_t l_e_sam_ret_status;
    e_sample_ret_t l_e_sam_ret_value;
    bool           l_e_sam_error_flag;
    uint16_t       l_u16_count;
    uint16_t       l_u16_block_number;
    uint32_t       l_u32_check_write_data_addr;
    
    /* Set local variables */
    l_e_sam_ret_value           = SAMPLE_ENUM_RET_STS_OK;
    l_e_sam_error_flag          = false;
    
    /* This expression (actual block number) never exceeds the range of casting uint16_t */
    l_u16_block_number          = (uint16_t)(i_u32_start_addr >> SAMPLE_VALUE_U08_SHIFT_ADDR_TO_BLOCK_CF);
    l_u32_check_write_data_addr = i_u32_start_addr;
    
    /******************************************************************************************************************
     * Set the code flash programming mode
     *****************************************************************************************************************/
    l_e_rfd_ret_status = R_RFD_SetFlashMemoryMode(R_RFD_ENUM_FLASH_MODE_CODE_PROGRAMMING);
    
    if (R_RFD_ENUM_RET_STS_OK != l_e_rfd_ret_status)
    {
        l_e_sam_error_flag = true;
        l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_MODE_MISMATCHED;
    }
    else
    {
        /* No operation */
    }
    
    /******************************************************************************************************************
     * BLANKCHECK -> ERASE
     *****************************************************************************************************************/
    if (false == l_e_sam_error_flag)
    {
        /* BLANKCHECK (1 block) */
        R_RFD_BlankCheckCodeFlashReq(l_u16_block_number);
        l_e_sam_ret_status = BL_CheckCFDFSeqEnd();
        
        if (SAMPLE_ENUM_RET_ERR_ACT_BLANKCHECK == l_e_sam_ret_status)
        {
            /* ERASE (1 block) */
            R_RFD_EraseCodeFlashReq(l_u16_block_number);
            l_e_sam_ret_status = BL_CheckCFDFSeqEnd();
            
            if (SAMPLE_ENUM_RET_STS_OK != l_e_sam_ret_status)
            {
                l_e_sam_error_flag = true;
                l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_CMD_ERASE;
            }
            else
            {
                /* No operation */
            }
        }
        else if (SAMPLE_ENUM_RET_STS_OK != l_e_sam_ret_status)
        {
            l_e_sam_error_flag = true;
            l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_CMD_BLANKCHECK;
        }
        else
        {
            /* No operation */
        }
    }
    else /* true == l_e_sam_error_flag */
    {
        /* No operation */
    }

    /******************************************************************************************************************
     * WRITE
     *****************************************************************************************************************/
    if (false == l_e_sam_error_flag)
    {
        for (l_u16_count = 0u; l_u16_count < i_u16_write_data_length; l_u16_count += 4u)
        {
            R_RFD_WriteCodeFlashReq(i_u32_start_addr + l_u16_count, &inp_u08_write_data[l_u16_count]);
            l_e_sam_ret_status = BL_CheckCFDFSeqEnd();
            
            if (SAMPLE_ENUM_RET_STS_OK != l_e_sam_ret_status)
            {
                l_e_sam_error_flag = true;
                l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_CMD_WRITE;
                break;
            }
            else
            {
                /* No operation */
            }
        }
    }
    else /* true == l_e_sam_error_flag */
    {
        /* No operation */
    }
 
    /******************************************************************************************************************
     * IVERIFY (internal verify)
     *****************************************************************************************************************/
    if (false == l_e_sam_error_flag)
    {
        /* IVERIFY (1 block) */
        R_RFD_IVerifyCodeFlashReq(l_u16_block_number);
        l_e_sam_ret_status = BL_CheckCFDFSeqEnd();
        
        if (SAMPLE_ENUM_RET_STS_OK != l_e_sam_ret_status)
        {
            l_e_sam_error_flag = true;
            l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_CMD_IVERIFY;
        }
        else
        {
            /* No operation */
        }
    }
    else /* true == l_e_sam_error_flag */
    {
        /* No operation */
    }
    
    /******************************************************************************************************************
     * Set non-programmable mode
     *****************************************************************************************************************/
    l_e_rfd_ret_status = R_RFD_SetFlashMemoryMode(R_RFD_ENUM_FLASH_MODE_CODE_TO_NONPROGRAMMABLE);
    
    if (R_RFD_ENUM_RET_STS_OK != l_e_rfd_ret_status)
    {
        l_e_sam_error_flag = true;
        l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_MODE_MISMATCHED;
    }
    else
    {
        /* No operation */
    }
   
    /******************************************************************************************************************
     * Check write data
     *****************************************************************************************************************/
    DOUT(("l_e_sam_error_flag: 0x%x \n\r", l_e_sam_error_flag));
	if (false == l_e_sam_error_flag)
    {
        for (l_u16_count = 0u; l_u16_count < i_u16_write_data_length; l_u16_count++)
        {
            if (inp_u08_write_data[l_u16_count] != (*(uint8_t __far *)l_u32_check_write_data_addr))
            {
                l_e_sam_error_flag = true;
                l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_CHECK_WRITE_DATA;
                break;
            }
            else
            {
                /* No operation */
            }
            l_u32_check_write_data_addr++;
        }
    }
    else /* true == l_e_sam_error_flag */
    {
        /* No operation */
    }	
	
    DOUT(("l_e_sam_ret_value: 0x%x \n\r", l_e_sam_ret_value));
	DOUT(("0x4250: 0x%x \n\r", (*(uint16_t __far *)0x4250)));
	DOUT(("0x424E: 0x%x \n\r", (*(uint16_t __far *)0x424E)));

    return (l_e_sam_ret_value);
}

/**********************************************************************************************************************
 End of function Sample_CodeFlashControl
 *********************************************************************************************************************/
#pragma section







































































#if false
/***********************************************************************************************************************
* Function Name: 
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
R_RFD_FAR_FUNC e_sample_ret_t SetCFPgmMode(void)
{
	/* Local variable definition */
    e_rfd_ret_t    l_e_rfd_ret_status;
    e_sample_ret_t l_e_sam_ret_value;   
    
    /* Set local variables */
    l_e_sam_ret_value           = SAMPLE_ENUM_RET_STS_OK;
      
    /******************************************************************************************************************
     * Set the code flash programming mode
     *****************************************************************************************************************/
    l_e_rfd_ret_status = R_RFD_SetFlashMemoryMode(R_RFD_ENUM_FLASH_MODE_CODE_PROGRAMMING);
    
    if (R_RFD_ENUM_RET_STS_OK != l_e_rfd_ret_status)
    {       
        l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_MODE_MISMATCHED;
    }
    else
    {
        /* No operation */
    }
	
	 return (l_e_sam_ret_value);	
}

/***********************************************************************************************************************
* Function Name: 
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
R_RFD_FAR_FUNC e_sample_ret_t SetCFNonPgmMode(void)
{
	/* Local variable definition */
    e_rfd_ret_t    l_e_rfd_ret_status;
    e_sample_ret_t l_e_sam_ret_value;
        
    /* Set local variables */
    l_e_sam_ret_value           = SAMPLE_ENUM_RET_STS_OK;
       
     /******************************************************************************************************************
     * Set non-programmable mode
     *****************************************************************************************************************/
    l_e_rfd_ret_status = R_RFD_SetFlashMemoryMode(R_RFD_ENUM_FLASH_MODE_CODE_TO_NONPROGRAMMABLE);
    
    if (R_RFD_ENUM_RET_STS_OK != l_e_rfd_ret_status)
    {
        l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_MODE_MISMATCHED;
    }
    else
    {
        /* No operation */
    }
	
	 return (l_e_sam_ret_value);	
}


#endif

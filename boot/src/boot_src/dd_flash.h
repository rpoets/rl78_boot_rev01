/***********************************************************************************************************************
* File Name        : dd_flash.h
* Component Version: 
* Device(s)        : R7F123FLG3xFB
* Description      : This file implements device driver for isr handler
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#ifndef DD_FLASH_H
#define DD_FLASH_H


/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/


/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/

R_RFD_FAR_FUNC void BL_Code_INITSCT(void);
uint16_t InitBlFlashDriver(void);
void test_BlFlashDriver(void);
R_RFD_FAR_FUNC e_sample_ret_t BL_CheckCFDFSeqEnd(void);
R_RFD_FAR_FUNC e_sample_ret_t BL_CodeFlashControl(uint32_t i_u32_start_addr, uint16_t i_u16_write_data_length, uint8_t __near * inp_u08_write_data);
R_RFD_FAR_FUNC e_sample_ret_t AppFlashErase(uint32_t i_u32_start_addr);
R_RFD_FAR_FUNC e_sample_ret_t AppFlashWrite64B(uint32_t i_u32_start_addr, uint8_t __near * inp_u08_write_data);
R_RFD_FAR_FUNC e_sample_ret_t SetCFNonPgmMode(void);
R_RFD_FAR_FUNC e_sample_ret_t AppFlashEraseBlock(uint32_t i_u32_start_addr, uint16_t i_u16_block_nums);
#endif




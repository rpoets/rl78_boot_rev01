/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#ifndef TYPEDEF_H
#define TYPEDEF_H
/***********************************************************************************************************************
* File Name        : typedef.h
* Component Version: 
* Device(s)        : R7F123FLG3xFB
* Description      : This file implements typedef.
***********************************************************************************************************************/
typedef struct {
	uint16_t bl_access_key0;
	uint16_t bl_access_key1;
	uint16_t bl_session_key;
	uint8_t bl_app_mode_notice;
	uint8_t bl_resf;
	uint8_t bl_pocres;	
	uint8_t reset_request_app;	
	
} bootpara_t;

#if false
typedef struct {
	uint8_t bl_app_mode_notice;
	uint16_t bl_session_key;
	uint8_t reset_cause;
	uint8_t reset_count;	
	
} bootpara_t;
#endif

typedef enum {
	VECTOR_INTP1       = 0x4014,
	VECTOR_UART1_SEND  = 0x407C	
}israddr_e;

typedef enum {
	BL_SIGNATURE      = 0xBB,
	APP_SIGNATURE     = 0xAA,
	SW_RST_SIGNATURE  = 0x77
	
}signature_e;

typedef enum {
	ENUM_RET_STAY_BL 	= 1u,
	ENUM_RET_RUN_APP 	= 2u,
	ENUM_RET_BRANCH_ERR = 99u	
}branch_mode_ret_e;

/**
 * @enum e_sample_ret_t
 * Definition of the sample operation status
 */
typedef enum e_sample_ret
{
    SAMPLE_ENUM_RET_STS_OK                 = 0x00u,
    SAMPLE_ENUM_RET_ERR_PARAMETER          = 0x10u,
    SAMPLE_ENUM_RET_ERR_CONFIGURATION      = 0x11u,
    SAMPLE_ENUM_RET_ERR_MODE_MISMATCHED    = 0x12u,
    SAMPLE_ENUM_RET_ERR_CHECK_WRITE_DATA   = 0x13u,
    SAMPLE_ENUM_RET_ERR_CFDF_SEQUENCER     = 0x20u,
    SAMPLE_ENUM_RET_ERR_EXTRA_SEQUENCER    = 0x21u,
    SAMPLE_ENUM_RET_ERR_ACT_ERASE          = 0x22u,
    SAMPLE_ENUM_RET_ERR_ACT_WRITE          = 0x23u,
    SAMPLE_ENUM_RET_ERR_ACT_BLANKCHECK     = 0x24u,
    SAMPLE_ENUM_RET_ERR_ACT_IVERIFY        = 0x25u,
    SAMPLE_ENUM_RET_ERR_CMD_ERASE          = 0x30u,
    SAMPLE_ENUM_RET_ERR_CMD_WRITE          = 0x31u,
    SAMPLE_ENUM_RET_ERR_CMD_BLANKCHECK     = 0x32u,
    SAMPLE_ENUM_RET_ERR_CMD_IVERIFY        = 0x33u,
    SAMPLE_ENUM_RET_ERR_CMD_SET_EXTRA_AREA = 0x34u,
} e_sample_ret_t;

#endif
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#ifndef ATYPEDEF_H
#define ATYPEDEF_H

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
	
	BL_SIGNATURE = 0xBB,
	APP_SIGNATURE = 0xAA,
	SW_RST_SIGNATURE = 0x77	
	
}signature_e;

typedef struct {
	
	uint16_t hw_version;
	uint16_t sw_version;
	uint8_t Touch_ID;
	uint8_t Display_ID;
	
}fidm_version_id_t;

#endif
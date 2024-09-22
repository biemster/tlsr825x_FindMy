/********************************************************************************************************
 * @file     feature_adv_power.c 
 *
 * @brief    for TLSR chips
 *
 * @author	 public@telink-semi.com;
 * @date     May. 10, 2018
 *
 * @par      Copyright (c) Telink Semiconductor (Shanghai) Co., Ltd.
 *           All rights reserved.
 *           
 *			 The information contained herein is confidential and proprietary property of Telink 
 * 		     Semiconductor (Shanghai) Co., Ltd. and is available under the terms 
 *			 of Commercial License Agreement between Telink Semiconductor (Shanghai) 
 *			 Co., Ltd. and the licensee in separate contract or the terms described here-in. 
 *           This heading MUST NOT be removed from this file.
 *
 * 			 Licensees are granted free, non-transferable use of the information in this 
 *			 file under Mutual Non-Disclosure Agreement. NO WARRENTY of ANY KIND is provided. 
 *           
 *******************************************************************************************************/
#include <stack/ble/ble.h>
#include "tl_common.h"
#include "drivers.h"
#include "app_config.h"
#include "vendor/common/blt_led.h"
#include "application/keyboard/keyboard.h"
#include "vendor/common/tl_audio.h"
#include "vendor/common/blt_soft_timer.h"
#include "vendor/common/blt_common.h"

//#define		MY_RF_POWER_INDEX	RF_POWER_P10p29dBm // 10.29 dbm
#define	MY_RF_POWER_INDEX	RF_POWER_P0p04dBm
											
void user_init_normal(void)
{
	random_generator_init();

	u8 mac_addr[6] = {0xFF, 0xEE, 0xDD, 0xCC, 0xBB, 0xAA}; // reverse, for some reason

	////// Controller Initialization  //////////
	blc_ll_initBasicMCU();
	blc_ll_initStandby_module(mac_addr);
	blc_ll_initAdvertising_module(mac_addr);

	u8 tbl_advData[] = {
		0x1e, /* Length (30) */
		0xff, /* Manufacturer Specific Data (type 0xff) */
		0x4c, 0x00, /* Company ID (Apple) */
		0x12, 0x19, /* Offline Finding type and length */
		0x00, /* State */
		0x11, 0x22, 0x33, 0x22, 0x11, 0x22, 0x33, 0x22,
		0x11, 0x22, 0x33, 0x22, 0x11, 0x22, 0x33, 0x22,
		0x11, 0x22, 0x33, 0x22, 0x11, 0x22,
		0x00, /* First two bits */
		0x00, /* Hint (0x00) */
	};
	bls_ll_setAdvData( (u8 *)tbl_advData, sizeof(tbl_advData) );

	u8 status = bls_ll_setAdvParam( ADV_INTERVAL_2S,
									ADV_INTERVAL_2S,
									ADV_TYPE_NONCONNECTABLE_UNDIRECTED,
									OWN_ADDRESS_PUBLIC,
									0,
									NULL,
									BLT_ENABLE_ADV_ALL,
									ADV_FP_NONE);

	if(status != BLE_SUCCESS)
	{
		write_reg8(0x40000, 0x11);
		while(1);
	}

	rf_set_power_level_index (MY_RF_POWER_INDEX);
	bls_ll_setAdvEnable(1);
	irq_enable();
}


_attribute_ram_code_ void main_loop (void)
{
	blt_sdk_main_loop();
}


//#include "typedefine.h"
#include "r_usb_basic_if.h"
#include "r_usb_pcdc_if.h"
#include "r_usb_pcdc_descriptor.h"
#include "cg_src\r_cg_macrodriver.h"
#include "cg_src\r_cg_bsc.h"
#include "cg_src\r_cg_scifa.h"
#include "platform.h"
#include "r_pdc_rx_if.h"
//#include "r_dmaca_rx_if.h"
#include "r_pinset.h"
#include "Converter.h"


#define DATA_LEN        		(4096)
#define SDRAM_SIZE_IN_LWORD		(16777216)

void main(void);
static void     usb_pin_setting (void);
static void dmaca_callback(void);
static void pcdfi_callback(void*);
static void pcfei_callback(void*);
static void pceri_callback(void*);

static uint8_t  g_buf[DATA_LEN];
static int32_t  *sdram = 0x08000000;	// SDRAM start-address
static uint8_t* sdram_byte = 0x08000000;
static int32_t errorCount = 0;

static uint8_t sendData_LED_ON[] = {0x84, 0x02};
static uint8_t sendData_LED_OFF[] = {0x84, 0x00};
static uint8_t sendData_Mic_ON_Duty_Set_SP_ON[] = {0x83, 0x01, 0x82, 0x08, 0x81, 0x01};
static uint8_t sendData_Mic_OFF[] = {0x83, 0x00};

static uint8_t ACK[] = {0x31, 0xf8};
static uint8_t BUSSY[] = {0x01};
static uint8_t NA[] = {0x00};

static int32_t count = 0;
static uint8_t mic_state = 0;
static int32_t maxCount = 0;

//static dmaca_stat_t dmaca_status;
//static dmaca_transfer_data_cfg_t td_cfg;
//static dmaca_return_t dmaca_return;
static pdc_data_cfg_t pdc_dumy_data;
static pdc_stat_t pdc_dummy_stat;

const static usb_descriptor_t usb_descriptor =
{
    g_apl_device,
    g_apl_configuration,
    g_apl_hs_configuration,
    g_apl_qualifier_descriptor,
    g_apl_string_table
};

void main(void)
{
    usb_ctrl_t  ctrl;
    usb_cfg_t   cfg;
    uint32_t i;


    pdc_data_cfg_t pdc_data;

    pdc_return_t pdc_return;


    HardwareSetup();
    R_BSC_InitializeSDRAM();

//    R_DMACA_Init();
//    R_DMACA_Open(DMACA_CH1);
//    td_cfg.p_src_addr = (void*)0x000A0510;
////    td_cfg.p_src_addr = &dummyData;
//    td_cfg.act_source = IR_PDC_PCDFI;
//    td_cfg.transfer_mode = DMACA_TRANSFER_MODE_REPEAT;
//    td_cfg.repeat_block_side = DMACA_REPEAT_BLOCK_SOURCE;
//    td_cfg.data_size = DMACA_DATA_SIZE_LWORD;
//    td_cfg.request_source = DMACA_TRANSFER_REQUEST_SOFTWARE;
//    td_cfg.dtie_request = DMACA_TRANSFER_END_INTERRUPT_ENABLE;
//    td_cfg.esie_request = DMACA_TRANSFER_ESCAPE_END_INTERRUPT_ENABLE;
//    td_cfg.rptie_request = DMACA_REPEAT_SIZE_END_INTERRUPT_ENABLE;
//    td_cfg.sarie_request = DMACA_SRC_ADDR_EXT_REP_AREA_OVER_INTERRUPT_DISABLE;
//    td_cfg.darie_request = DMACA_DES_ADDR_EXT_REP_AREA_OVER_INTERRUPT_DISABLE;
//    td_cfg.src_addr_mode = DMACA_SRC_ADDR_FIXED;
//    td_cfg.src_addr_repeat_area = DMACA_SRC_ADDR_EXT_REP_AREA_NONE;
//    td_cfg.des_addr_mode = DMACA_DES_ADDR_INCR;
//    td_cfg.des_addr_repeat_area = DMACA_DES_ADDR_EXT_REP_AREA_NONE;
//    td_cfg.offset_value = 0x00000000;
//    td_cfg.interrupt_sel = DMACA_CLEAR_INTERRUPT_FLAG_BEGINNING_TRANSFER;
//    td_cfg.p_des_addr = (void*)buffer;
//    td_cfg.transfer_count = 1;
//    td_cfg.block_size = 8;
////    IR(PDC, PCDFI) = 0;
////    IEN(PDC, PCDFI) = 0;
//    dmaca_return = R_DMACA_Create(DMACA_CH1, &td_cfg);
//    dmaca_return = R_DMACA_Int_Callback(DMACA_CH1, dmaca_callback);
//    dmaca_return = R_DMACA_Int_Enable(DMACA_CH1, 10);
//    dmaca_return = R_DMACA_Control(DMACA_CH1, DMACA_CMD_ENABLE, &dmaca_status);

    pdc_data.priority.pcdfi_level = 15;
    pdc_data.priority.groupbl0_level = 14;
    pdc_data.inticu_req.pcdfi_ien = true;
    pdc_data.inticu_req.pcfei_ien = true;
    pdc_data.inticu_req.pceri_ien = true;
    pdc_data.intpdc_req.dfie_ien = true;
    pdc_data.intpdc_req.feie_ien = true;
    pdc_data.intpdc_req.ovie_ien = true;
    pdc_data.intpdc_req.udrie_ien = true;
    pdc_data.intpdc_req.verie_ien = true;
    pdc_data.vps_select = PDC_VSYNC_SIGNAL_POLARITY_HIGH;
    pdc_data.hps_select = PDC_HSYNC_SIGNAL_POLARITY_HIGH;
    pdc_data.capture_pos.vst_position = 0;
    pdc_data.capture_pos.hst_position = 0;
    pdc_data.capture_size.vsz_size = 1;
    pdc_data.capture_size.hsz_size = 256;
    pdc_data.p_callback.pcb_receive_data_ready = pcdfi_callback;
    pdc_data.p_callback.pcb_frame_end = pcfei_callback;
    pdc_data.p_callback.pcb_error = pceri_callback;
    R_PDC_PinSet();
    pdc_return = R_PDC_Open(&pdc_data);


    usb_pin_setting();
    ctrl.module     = USB_IP0;
    ctrl.type       = USB_PCDC;
    cfg.usb_speed   = USB_FS;
    cfg.usb_mode    = USB_PERI;
    cfg.p_usb_reg   = (usb_descriptor_t *)&usb_descriptor;
    R_USB_Open(&ctrl, &cfg);

    R_SCIFA11_Start();

    while (1)
    {
        switch (R_USB_GetEvent(&ctrl))
        {
            case USB_STS_CONFIGURED :
            case USB_STS_WRITE_COMPLETE :
                ctrl.type = USB_PCDC;
                R_USB_Read(&ctrl, g_buf, DATA_LEN);
            break;

            // 何も返信しなくてもR_USB_Write(&ctrl, g_buf, 0);しないとそれ以降の通信ができない？
            case USB_STS_READ_COMPLETE :
            	ctrl.type = USB_PCDC;
            	switch(g_buf[0])
            	{
            	case 0x31:	// '1' AcknowledgeRequest
            		R_USB_Write(&ctrl, ACK, 2);
            		R_SCIFA11_Serial_Send(sendData_LED_ON, 2);
            		break;

            	case 0x32:	// '2' SpeakerON
            		R_USB_Write(&ctrl, g_buf, 0);
            		count = 0;
            		maxCount = BytesToUInt32(g_buf, 1) * 8;
            		R_PDC_Control(PDC_CMD_CAPTURE_START, &pdc_dumy_data, &pdc_dummy_stat);
            		R_SCIFA11_Serial_Send(sendData_Mic_ON_Duty_Set_SP_ON, 6);
            		mic_state = 1;
            		break;

            	case 0x33:	// '3' GetMicData
            		R_USB_Write(&ctrl, sdram_byte + BytesToUInt32(g_buf, 1), BytesToUInt32(g_buf, 5));
            		break;

            	case 0x34:	// '4' GetStatus
            		if(mic_state)
            			R_USB_Write(&ctrl, BUSSY, 1);
            		else
            			R_USB_Write(&ctrl, NA, 1);
            		break;

            	case 0x7a:	// 'z' Disconnect
            		R_USB_Write(&ctrl, g_buf, 0);
            		R_SCIFA11_Serial_Send(sendData_LED_OFF, 2);
            		break;

            	default:
            		break;
            	}
//            	R_USB_Write(&ctrl, g_buf, 0);
            break;

            case USB_STS_DETACH:
        		R_SCIFA11_Serial_Send(sendData_LED_OFF, 2);
            	break;

            default :
            break;
        }
    }
}

static void usb_pin_setting (void)
{
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_MPC);

    PORT1.PMR.BIT.B6    = 0u;
    MPC.P16PFS.BYTE     = 0x11; /* USB0_VBUS */
    PORT1.PMR.BIT.B6    = 1u;

    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_MPC);
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);
}

//static void dmaca_callback(void)
//{
//	R_DMACA_Control(DMACA_CH1, DMACA_CMD_STATUS_GET, &dmaca_status);
//
//	R_DMACA_Control(DMACA_CH1, DMACA_CMD_DTIF_STATUS_CLR, &dmaca_status);
//
//	if(dmaca_status.esif_stat)
//	{
//		R_DMACA_Control(DMACA_CH1, DMACA_CMD_ESIF_STATUS_CLR, &dmaca_status);
//
//		if(count < 1000)
//		{
//			count += 32;
//			DMAC1.DMDAR = (uint32_t)buffer + count;
//
////			td_cfg.p_des_addr = (void*)(buffer + count);
////			R_DMACA_Create(DMACA_CH1, &td_cfg);
//
//			R_DMACA_Control(DMACA_CH1, DMACA_CMD_SOFT_REQ_CLR, &dmaca_status);
//			R_DMACA_Control(DMACA_CH1, DMACA_CMD_RESUME, &dmaca_status);
//		}
//		else
//		{
//			R_PDC_Control(PDC_CMD_DISABLE, &pdc_dumy_data, &pdc_dummy_stat);
//			R_DMACA_Control(DMACA_CH1, DMACA_CMD_SOFT_REQ_CLR, &dmaca_status);
//		}
//	}
//}

static void pcdfi_callback(void* pdata)
{
	PDC.PCCR0.BIT.DFIE = 0;

//	if(count <= SDRAM_SIZE_IN_LWORD - 8)
	if (count < maxCount)
	{
//		R_DMACA_Control(DMACA_CH1, DMACA_CMD_SOFT_REQ_NOT_CLR_REQ, &dmaca_status);
		sdram[count] = PDC.PCDR.LONG;
		sdram[count+1] = PDC.PCDR.LONG;
		sdram[count+2] = PDC.PCDR.LONG;
		sdram[count+3] = PDC.PCDR.LONG;
		sdram[count+4] = PDC.PCDR.LONG;
		sdram[count+5] = PDC.PCDR.LONG;
		sdram[count+6] = PDC.PCDR.LONG;
		sdram[count+7] = PDC.PCDR.LONG;
		count += 8;
	}
	else
	{
		R_PDC_Control(PDC_CMD_DISABLE, &pdc_dumy_data, &pdc_dummy_stat);
		if ( mic_state )
		{
			mic_state = 0;
			R_SCIFA11_Serial_Send(sendData_Mic_OFF, 2);
		}
	}

	PDC.PCCR0.BIT.DFIE = 1;

//
//	PDC.PCCR0.BIT.DFIE = 0;
//	PDC.PCCR0.BIT.DFIE = 1;
//	R_PDC_Control(PDC_CMD_CAPTURE_START, &pdc_dumy_data, &pdc_dummy_stat);

//	PDC.PCCR0.BIT.PRST = 1;
//	while(PDC.PCCR0.BIT.PRST);
//	PDC.PCCR1.BIT.PCE = 1;

//	if(!PDC.PCSR.BIT.FBSY)
//	{
//		R_PDC_Control(PDC_CMD_CAPTURE_START, &pdc_dumy_data, &pdc_dummy_stat);
//	}
//	if(!PDC.PCCR0.BIT.PCKE)
//	{
//		R_PDC_Control(PDC_CMD_CAPTURE_START, &pdc_dumy_data, &pdc_dummy_stat);
//	}
//	if(PDC.PCCR0.BIT.PRST)
//	{
//		R_PDC_Control(PDC_CMD_CAPTURE_START, &pdc_dumy_data, &pdc_dummy_stat);
//	}
//	R_PDC_Control(PDC_CMD_CAPTURE_START, &pdc_dumy_data, &pdc_dummy_stat);

//	pdc_stat_t stat_pdc;
//
//	R_PDC_Control(PDC_CMD_STATUS_GET, &pdc_dumy_data, &stat_pdc);
//
//	while(!PDC.PCSR.BIT.FEMPF)
//	{
//		if(PDC.PCSR.BIT.UDRF)
//		{
//			return;
//		}
//	}
//
//	R_DMACA_Control(DMACA_CH1, DMACA_CMD_DISABLE, &dmaca_status);
//
//	PDC.PCCR1.BIT.PCE = 0;
//	PDC.PCSR.BIT.FEF = 0;
}

static void pcfei_callback(void* pdata)
{
//	if(count < SDRAM_SIZE_IN_LWORD - 8)
	if (count < maxCount)
	{
		R_PDC_Control(PDC_CMD_CAPTURE_START, &pdc_dumy_data, &pdc_dummy_stat);
	}
	else
	{
		R_PDC_Control(PDC_CMD_DISABLE, &pdc_dumy_data, &pdc_dummy_stat);
		if ( mic_state )
		{
			mic_state = 0;
			R_SCIFA11_Serial_Send(sendData_Mic_OFF, 2);
		}
	}
}

static void pceri_callback(void* pdata)
{
	pdc_cb_arg_t* pdecode;
	pdecode = (pdc_cb_arg_t*)pdata;

//	switch(pdecode->event_id)
//	{
//	case PDC_EVT_ID_ERROR:
//
//		break;
//	case PDC_EVT_ID_OVERRUN:
//
//		break;
//	case PDC_EVT_ID_UNDERRUN:
//
//		break;
//	case PDC_EVT_ID_VERTICALLINE:
//
//	break;
//		case PDC_EVT_ID_HORIZONTALBYTE:
//
//	break;
//	default:
//		break;
//	}

	while(PDC.PCMONR.BIT.VSYNC);
	R_PDC_Control(PDC_CMD_CAPTURE_START, &pdc_dumy_data, &pdc_dummy_stat);
	errorCount++;
}

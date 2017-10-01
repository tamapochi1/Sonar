/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
 * SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2014(2016) Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : r_usb_pcdc_if.h
 * Description  : Interface file for USB PCDC API
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 ***********************************************************************************************************************/

#ifndef USB_PCDC_IF_H
#define USB_PCDC_IF_H

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
    
#include "r_usb_basic_if.h"
#include "r_usb_pcdc_config.h"

/******************************************************************************
 Macro definitions
 ******************************************************************************/
/* CDC Class Requests IDs*/
#define USB_PCDC_SET_LINE_CODING            (0x2000u)
#define USB_PCDC_GET_LINE_CODING            (0x2100u)
#define USB_PCDC_SET_CONTROL_LINE_STATE     (0x2200u)

/* setup packet table size (uint16_t * 5) */
#define     USB_CDC_SETUP_TBL_BSIZE             (10u)

/*******************************************************************************
 Typedef definitions
 *******************************************************************************/

typedef struct
{

    uint16_t brx_carrier :1; /* DCD signal */
    uint16_t btx_carrier :1; /* DSR signal */
    uint16_t b_break :1; /* State of break detection mechanism of teh device */
    uint16_t b_framing :1; /* Framing error */
    uint16_t b_parity :1; /* Parity error */
    uint16_t b_over_run :1; /* Over Run error */
    uint16_t rsv :9; /* reserve */
} usb_serial_state_bitmap_t;



/* Class Notification Serial State */
typedef union
{
    uint32_t                    word;
    usb_serial_state_bitmap_t   bit;
} usb_sci_serialstate_t; /*USB_SCI_SerialState_t; */

typedef struct
{
    uint32_t dw_dte_rate; /* Data terminal rate, in bits per second */
    uint8_t  b_char_format; /* Stop bits */
    uint8_t  b_parity_type; /* Parity */
    uint8_t  b_data_bits; /* Data bits */
    uint8_t  rsv; /* reserve */
} usb_pcdc_linecoding_t; /* USB_PCDC_LineCoding_t; */

typedef struct
{
    uint16_t b_dtr :1; /* DTR */
    uint16_t b_rts :1; /* RTS */
    uint16_t rsv :14;/* reserve */
} usb_pcdc_ctrllinestate_t; /* USB_PCDC_ControlLineState_t; */

/******************************************************************************
 Private global variables and functions
 ******************************************************************************/

/******************************************************************************
 Exported global variables
 ******************************************************************************/
/* variables */
extern uint32_t g_cdc_trans_len;

extern void R_USB_PcdcSetInterface (uint16_t data1);
extern void R_USB_PcdcSendData (uint8_t *table, uint32_t size, usb_cb_t complete);
extern void R_USB_PcdcReceiveData (uint8_t *table, uint32_t size, usb_cb_t complete);
extern void R_USB_PcdcSerialStateNotification (usb_sci_serialstate_t serial_state, usb_cb_t complete);
extern void R_USB_PcdcCtrltrans (usb_setup_t *preq, uint16_t ctsq);

#endif /* USB_PCDC_IF_H */

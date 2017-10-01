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
 * File Name    : r_usb_pcdc.h
 * Description  : USB PCDC Local Header
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 ***********************************************************************************************************************/
#ifndef R_USB_PCDC_LOCAL_H
#define R_USB_PCDC_LOCAL_H

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

/*****************************************************************************
 Macro definitions
 ******************************************************************************/

/******************************************************************************
 Exported global variables
 ******************************************************************************/
extern uint32_t g_usb_read_request_size[][USB_MAXPIPE_NUM + 1];

/******************************************************************************
 Exported global functions (to be accessed by other files)
******************************************************************************/

void usb_pcdc_data_trans (uint16_t pipe, uint32_t Size, uint8_t *table, usb_cb_t complete);
void usb_pcdc_ctrl_trans_idst (usb_setup_t * req);
void usb_pcdc_ctrl_trans_rdds (usb_setup_t * req);
void usb_pcdc_ctrl_trans_wrds (usb_setup_t * req);
void usb_pcdc_ctrl_trans_wrnd (usb_setup_t * req);
void usb_pcdc_ctrl_trans_rdss (usb_setup_t * req);
void usb_pcdc_ctrl_trans_wrss (usb_setup_t * req);
void cdc_configured (usb_utr_t *ptr, uint16_t data1, uint16_t data2);
void cdc_detach (usb_utr_t *ptr, uint16_t data1, uint16_t data2);
void cdc_default (usb_utr_t *ptr, uint16_t mode, uint16_t data2);
void cdc_suspend (usb_utr_t *ptr, uint16_t data1, uint16_t data2);
void cdc_resume (usb_utr_t *ptr, uint16_t data1, uint16_t data2);
void cdc_interface (usb_utr_t *ptr, uint16_t data1, uint16_t data2);
void cdc_detach_device (void);
uint16_t usb_pcdc_pipe_info (uint8_t *table, uint16_t speed, uint16_t length);
void cdc_registration (usb_ctrl_t *ctrl, usb_cfg_t *cfg);


/*
void pcdc_read_complete (usb_utr_t *mess, uint16_t data1, uint16_t data2);
void pcdc_write_complete (usb_utr_t *mess, uint16_t data1, uint16_t data2);
*/

#endif  /* R_USB_PCDC_LOCAL_H */
/******************************************************************************
 End  Of File
 ******************************************************************************/

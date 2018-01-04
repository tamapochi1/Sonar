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
 * Copyright (C) 2015(2017) Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : r_usb_phid.h
 * Description  : USB Peripheral HID header file
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 30.09.2015 1.11 First Release
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 30.09.2017 1.22 Deleted functions and variables.
 ***********************************************************************************************************************/

#ifndef R_USB_PHID_H
#define R_USB_PHID_H

/******************************************************************************
 Macro definitions
 ******************************************************************************/
#define     USB_EP_B_DESCRIPTORTYPE     (1u)                /* Descriptor type */

/*****************************************************************************
 Exported global variables
 ******************************************************************************/
/* variables */
extern uint32_t g_usb_read_request_size[][USB_MAXPIPE_NUM + 1];

extern void usb_phid_data_trans (uint16_t pipe, uint32_t size, uint8_t * table, usb_cb_t complete);

extern void usb_set_event (uint16_t event, usb_ctrl_t *ctrl);

/*****************************************************************************
 Exported global functions (to be accessed by other files)
 ******************************************************************************/


#endif  /* #ifndef R_USB_PHID_H */
/******************************************************************************
 End  Of File
 ******************************************************************************/

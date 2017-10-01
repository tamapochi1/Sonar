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
 * File Name    : r_usb_pcdc_api.c
 * Description  : USB PCDC API Functions
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 ***********************************************************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include "r_usb_basic_if.h"
#include "r_usb_typedef.h"
#include "r_usb_extern.h"
#include "r_usb_pcdc_if.h"
#include "r_usb_pcdc.h"
#include "r_usb_bitdefine.h"
#include "r_usb_reg_access.h"

/******************************************************************************
 Private global variables and functions
 ******************************************************************************/

/******************************************************************************
 Exported global variables (to be accessed by other files)
 ******************************************************************************/
/* Abstract Control Model Notification - SerialState */
uint8_t g_usb_pcdc_serialstate_table[USB_CDC_SETUP_TBL_BSIZE] =
{
    0xA1,       /* bmRequestType */
    0x20,       /* bNotification:SERIAL_STATE */
    0x00, 0x00, /* wValue:Zero */
    0x00, 0x00, /* wIndex:Interface */
    0x02, 0x00, /* wLength:2 */
    0x00, 0x00, /* Data:UART State bitmap */
};

/******************************************************************************
 Renesas Abstracted Peripheral Communications Devices Class Driver API functions
 ******************************************************************************/

/******************************************************************************
 Function Name   : R_USB_PcdcSetInterface
 Description     : Set_Interface
 Arguments       : uint16_t data1       ; Not use
 Return value    : none
 ******************************************************************************/
void R_USB_PcdcSetInterface (uint16_t data1)
{
    /* Non processing. */
} /* End of function R_USB_PcdcSetInterface */

/******************************************************************************
 Function Name   : R_USB_PcdcSendData
 Description     : Data send request for Host
 Arguments       : uint8_t       *Table      ; Pointer to Data stored buffer
                 : uint32_t      size        ; Data size
                 : usb_cb_t      complete    ; Pointer to Callback function
 Return value    : none
 ******************************************************************************/
void R_USB_PcdcSendData (uint8_t *table, uint32_t size, usb_cb_t complete)
{
    usb_pcdc_data_trans(USB_CFG_PCDC_BULK_IN, size, table, complete);
}
/******************************************************************************
 End of function R_USB_PcdcSendData
 ******************************************************************************/

/******************************************************************************
 Function Name   : R_USB_PcdcReceiveData
 Description     : Data Receive request for Host
 Arguments       : uint8_t       *Table      ; Pointer to Data stored buffer
                 : uint32_t      size        ; Data size
                 : usb_cb_t      complete    ; Pointer to Callback function
 Return value    : none
 ******************************************************************************/
void R_USB_PcdcReceiveData (uint8_t * Table, uint32_t size, usb_cb_t complete)
{
    usb_pcdc_data_trans(USB_CFG_PCDC_BULK_OUT, size, Table, complete);
}
/******************************************************************************
 End of function R_USB_PcdcReceiveData
 ******************************************************************************/

/******************************************************************************
 Function Name   : R_USB_PcdcSerialStateNotification
 Description     : Class Notification Serial State for USB Host
 Arguments       : uint16_t  serial_state   ; State of UART
                 : usb_cb_t  complete       ; Pointer to Callback function
 Return value    : none
 ******************************************************************************/
void R_USB_PcdcSerialStateNotification (usb_sci_serialstate_t serial_state, usb_cb_t complete)
{
    /* UART State bitmap set */
    g_usb_pcdc_serialstate_table[8] = (uint8_t) (serial_state.word & 0xff);
    g_usb_pcdc_serialstate_table[9] = (uint8_t) (serial_state.word >> 8);

    usb_pcdc_data_trans(USB_CFG_PCDC_INT_IN, 10, g_usb_pcdc_serialstate_table, complete);
}
/******************************************************************************
 End of function R_USB_PcdcSerialStateNotification
 ******************************************************************************/

/******************************************************************************
 End  Of File
 ******************************************************************************/

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
/*******************************************************************************
 * File Name    : r_usb_pcdc_apl.c
 * Description  : USB Peripheral Communications Devices Class Sample Code
 *******************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 ******************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include <string.h>

#include "r_usb_basic_if.h"
#include "r_usb_pcdc_if.h"
#include "r_usb_pcdc_apl_config.h"

#if OPERATION_MODE == USB_UART
#include "r_sci_rx_if.h"
#include "r_usb_rsk_sci.h"
#endif /* OPERATION_MODE == USB_UART */

#if defined(USE_LPW)
#include "r_usb_rsk_lowpower.h"
#endif /* defined(USE_LPW) */


/******************************************************************************
 Macro definitions
 ******************************************************************************/
#define USE_USBIP0              (USB_IP0)       /* USB0 module */
#define USE_USBIP1              (USB_IP1)       /* USB1 module */

#define USB_ECHO                (0)             /* Loop back(Echo) mode */
#define USB_UART                (1)             /* USB Serial(VCOM) converter mode */

#define USB_YES                 (1)
#define USB_NO                  (0)

/* #define DATA_LEN                (512) */
#define DATA_LEN                (64)

/* LINE_CODING request wLength */
#define LINE_CODING_LENGTH     (0x07u)


/******************************************************************************
 Exported global variables
 ******************************************************************************/
extern uint8_t g_apl_device[];
extern uint8_t g_apl_configuration[];
extern uint8_t g_apl_hs_configuration[];
extern uint8_t g_apl_qualifier_descriptor[];
extern uint8_t *g_apl_string_table[];

/******************************************************************************
 Exported global functions
 ******************************************************************************/

/******************************************************************************
 Exported global functions (to be accessed by other files)
 ******************************************************************************/
void usb_main (void);

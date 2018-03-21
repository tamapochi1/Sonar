/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIESREGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2015, 2017 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_scifa_user.c
* Version      : Code Generator for RX71M V1.01.00.05 [26 May 2017]
* Device(s)    : R5F571MFDxFB
* Tool-Chain   : CCRX
* Description  : This file implements device driver for SCIF module.
* Creation Date: 2018/01/08
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_scifa.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern uint8_t * gp_scifa10_tx_address;         /* SCIFA10 send buffer address */
extern uint16_t  g_scifa10_tx_count;            /* SCIFA10 send data number */
extern uint8_t * gp_scifa10_rx_address;         /* SCIFA10 receive buffer address */
extern uint16_t  g_scifa10_rx_count;            /* SCIFA10 receive data number */
extern uint16_t  g_scifa10_rx_length;           /* SCIFA10 receive data length */
extern uint8_t * gp_scifa11_tx_address;         /* SCIFA11 send buffer address */
extern uint16_t  g_scifa11_tx_count;            /* SCIFA11 send data number */
extern uint8_t * gp_scifa11_rx_address;         /* SCIFA11 receive buffer address */
extern uint16_t  g_scifa11_rx_count;            /* SCIFA11 receive data number */
extern uint16_t  g_scifa11_rx_length;           /* SCIFA11 receive data length */
/* Start user code for global. Do not edit comment generated here */
uint8_t temp;
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: r_scifa10_txif_interrupt
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#if FAST_INTERRUPT_VECTOR == VECT_SCIFA10_TXIF10
#pragma interrupt r_scifa10_txif_interrupt(vect=VECT(SCIFA10,TXIF10),fint)
#else
#pragma interrupt r_scifa10_txif_interrupt(vect=VECT(SCIFA10,TXIF10))
#endif
static void r_scifa10_txif_interrupt(void)
{
    uint16_t count = 0;

    /* Get the amount of untransmitted data stored in the FRDR register */
    uint16_t dummy_fdr = SCIFA10.FDR.BIT.T;

    /* Write data to the transmit FIFO data register */
    while ((0U < g_scifa10_tx_count) && (count < (_10_SCIF_FIFO_MAX_SIZE - dummy_fdr)))
    {
        SCIFA10.FTDR = *gp_scifa10_tx_address;
        gp_scifa10_tx_address++;
        g_scifa10_tx_count--;
        count++;
    }

    if (1U == SCIFA10.FSR.BIT.TDFE)
    {
        SCIFA10.FSR.BIT.TDFE = 0U;
    }

    if (0U >= g_scifa10_tx_count)
    {
        SCIFA10.SCR.BIT.TIE = 0U;
        SCIFA10.SCR.BIT.TEIE = 1U;
    }
}
/***********************************************************************************************************************
* Function Name: r_scifa10_teif_interrupt
* Description  : This function is TEIF10 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_scifa10_teif_interrupt(void)
{
    if (1U == SCIFA10.FSR.BIT.TEND)
    {
        SCIFA10.SCR.BIT.TE = 0U;
        SCIFA10.SCR.BIT.TEIE = 0U;
    }

    r_scifa10_callback_transmitend();
}
/***********************************************************************************************************************
* Function Name: r_scifa10_rxif_interrupt
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#if FAST_INTERRUPT_VECTOR == VECT_SCIFA10_RXIF10
#pragma interrupt r_scifa10_rxif_interrupt(vect=VECT(SCIFA10,RXIF10),fint)
#else
#pragma interrupt r_scifa10_rxif_interrupt(vect=VECT(SCIFA10,RXIF10))
#endif
static void r_scifa10_rxif_interrupt(void)
{
    uint16_t count = 0;

    /* Get the amount of receive data stored in FRDR register */
    uint16_t dummy_fdr = SCIFA10.FDR.BIT.R;

    /* Read data from the receive FIFO data register */
    while ((g_scifa10_rx_length > g_scifa10_rx_count) && (count < dummy_fdr))
    {
        *gp_scifa10_rx_address = SCIFA10.FRDR;
        gp_scifa10_rx_address++;
        g_scifa10_rx_count++;
        count++;
    }

    /* If remaining data is less than the receive trigger number, receive interrupt will not occur.
       In this case, set trigger number to 1 to force receive interrupt for each one byte of data in FRDR */
    if ((_01_SCIF_RX_TRIG_NUM > (g_scifa10_rx_length - g_scifa10_rx_count)) && (1U != SCIFA10.FTCR.BIT.RFTC))
    {
        SCIFA10.FTCR.BIT.RFTC = 1U;
    }

    /* Clear receive FIFO data full flag */
    if (1U == SCIFA10.FSR.BIT.RDF)
    {
        SCIFA10.FSR.BIT.RDF = 0U;
    }

    if (g_scifa10_rx_length <= g_scifa10_rx_count)
    {
        /* All data received */
        SCIFA10.SCR.BIT.RE = 0U;
        r_scifa10_callback_receiveend();
    }
}
/***********************************************************************************************************************
* Function Name: r_scifa10_erif_interrupt
* Description  : This function is ERIF10 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_scifa10_erif_interrupt(void)
{
    if (1U == SCIFA10.FSR.BIT.ER)
    {
        r_scifa10_callback_error(RECEIVE_ERROR);

        /* clear receive error flag */
        SCIFA10.FSR.BIT.ER = 0U;
    }
}
/***********************************************************************************************************************
* Function Name: r_scifa10_brif_interrupt
* Description  : This function is BRIF10 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_scifa10_brif_interrupt(void)
{
    if (1U == SCIFA10.LSR.BIT.ORER)
    {
        r_scifa10_callback_error(OVERRUN_ERROR);

        /* clear overrun error flag */
        SCIFA10.LSR.BIT.ORER = 0U;
    }

    if (1U == SCIFA10.FSR.BIT.BRK)
    {
        r_scifa10_callback_error(BREAK_DETECT);

        /* clear break detect flag */
        SCIFA10.FSR.BIT.BRK = 0U;
    }
}
/***********************************************************************************************************************
* Function Name: r_scifa10_callback_transmitend
* Description  : This function is a callback function when SCIFA10 finishes transmission.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_scifa10_callback_transmitend(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_scifa10_callback_receiveend
* Description  : This function is a callback function when SCIFA10 finishes reception.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_scifa10_callback_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_scifa10_callback_error
* Description  : This function is a callback function when SCIFA10 reception encounters error.
* Arguments    : error_type -
*                    receive error type
* Return Value : None
***********************************************************************************************************************/
static void r_scifa10_callback_error(scif_error_type_t error_type)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_scifa11_txif_interrupt
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#if FAST_INTERRUPT_VECTOR == VECT_SCIFA11_TXIF11
#pragma interrupt r_scifa11_txif_interrupt(vect=VECT(SCIFA11,TXIF11),fint)
#else
#pragma interrupt r_scifa11_txif_interrupt(vect=VECT(SCIFA11,TXIF11))
#endif
static void r_scifa11_txif_interrupt(void)
{
    uint16_t count = 0;

    /* Get the amount of untransmitted data stored in the FRDR register */
    uint16_t dummy_fdr = SCIFA11.FDR.BIT.T;

    /* Write data to the transmit FIFO data register */
    while ((0U < g_scifa11_tx_count) && (count < (_10_SCIF_FIFO_MAX_SIZE - dummy_fdr)))
    {
        SCIFA11.FTDR = *gp_scifa11_tx_address;
        gp_scifa11_tx_address++;
        g_scifa11_tx_count--;
        count++;
    }

    if (1U == SCIFA11.FSR.BIT.TDFE)
    {
        SCIFA11.FSR.BIT.TDFE = 0U;
    }

    if (0U >= g_scifa11_tx_count)
    {
        SCIFA11.SCR.BIT.TIE = 0U;
        SCIFA11.SCR.BIT.TEIE = 1U;
    }
}
/***********************************************************************************************************************
* Function Name: r_scifa11_teif_interrupt
* Description  : This function is TEIF11 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_scifa11_teif_interrupt(void)
{
    if (1U == SCIFA11.FSR.BIT.TEND)
    {
        SCIFA11.SCR.BIT.TE = 0U;
        SCIFA11.SCR.BIT.TEIE = 0U;
    }

    r_scifa11_callback_transmitend();
}
/***********************************************************************************************************************
* Function Name: r_scifa11_rxif_interrupt
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#if FAST_INTERRUPT_VECTOR == VECT_SCIFA11_RXIF11
#pragma interrupt r_scifa11_rxif_interrupt(vect=VECT(SCIFA11,RXIF11),fint)
#else
#pragma interrupt r_scifa11_rxif_interrupt(vect=VECT(SCIFA11,RXIF11))
#endif
static void r_scifa11_rxif_interrupt(void)
{
    uint16_t count = 0;

    /* Get the amount of receive data stored in FRDR register */
    uint16_t dummy_fdr = SCIFA11.FDR.BIT.R;

    /* Read data from the receive FIFO data register */
    while ((g_scifa11_rx_length > g_scifa11_rx_count) && (count < dummy_fdr))
    {
        *gp_scifa11_rx_address = SCIFA11.FRDR;
        gp_scifa11_rx_address++;
        g_scifa11_rx_count++;
        count++;
    }

    /* If remaining data is less than the receive trigger number, receive interrupt will not occur.
       In this case, set trigger number to 1 to force receive interrupt for each one byte of data in FRDR */
    if ((_01_SCIF_RX_TRIG_NUM > (g_scifa11_rx_length - g_scifa11_rx_count)) && (1U != SCIFA11.FTCR.BIT.RFTC))
    {
        SCIFA11.FTCR.BIT.RFTC = 1U;
    }

    /* Clear receive FIFO data full flag */
    if (1U == SCIFA11.FSR.BIT.RDF)
    {
        SCIFA11.FSR.BIT.RDF = 0U;
    }

    if (g_scifa11_rx_length <= g_scifa11_rx_count)
    {
        /* All data received */
        SCIFA11.SCR.BIT.RE = 0U;
        r_scifa11_callback_receiveend();
    }
}
/***********************************************************************************************************************
* Function Name: r_scifa11_erif_interrupt
* Description  : This function is ERIF11 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_scifa11_erif_interrupt(void)
{
    if (1U == SCIFA11.FSR.BIT.ER)
    {
        r_scifa11_callback_error(RECEIVE_ERROR);

        /* clear receive error flag */
        SCIFA11.FSR.BIT.ER = 0U;
    }
}
/***********************************************************************************************************************
* Function Name: r_scifa11_brif_interrupt
* Description  : This function is BRIF11 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_scifa11_brif_interrupt(void)
{
    if (1U == SCIFA11.LSR.BIT.ORER)
    {
        r_scifa11_callback_error(OVERRUN_ERROR);

        /* clear overrun error flag */
        SCIFA11.LSR.BIT.ORER = 0U;
    }

    if (1U == SCIFA11.FSR.BIT.BRK)
    {
        r_scifa11_callback_error(BREAK_DETECT);

        /* clear break detect flag */
        SCIFA11.FSR.BIT.BRK = 0U;
    }
}
/***********************************************************************************************************************
* Function Name: r_scifa11_callback_transmitend
* Description  : This function is a callback function when SCIFA11 finishes transmission.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_scifa11_callback_transmitend(void)
{
    /* Start user code. Do not edit comment generated here */
	temp = 100;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_scifa11_callback_receiveend
* Description  : This function is a callback function when SCIFA11 finishes reception.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_scifa11_callback_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_scifa11_callback_error
* Description  : This function is a callback function when SCIFA11 reception encounters error.
* Arguments    : error_type -
*                    receive error type
* Return Value : None
***********************************************************************************************************************/
static void r_scifa11_callback_error(scif_error_type_t error_type)
{
    /* Start user code. Do not edit comment generated here */
	temp = 114;
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

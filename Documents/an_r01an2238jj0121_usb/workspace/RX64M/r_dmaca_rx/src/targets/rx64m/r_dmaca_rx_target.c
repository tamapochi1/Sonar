/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2014(2015) Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* File Name    : r_dmaca_rx_target.c
* Device(s)    : RX
* Tool-Chain   : Renesas RXC Toolchain v2.01.00
* OS           : not use
* H/W Platform : not use
* Description  : Functions for DMACA driver
*******************************************************************************/
/*******************************************************************************
* History      : DD.MM.YYYY Version  Description
*              : 30.06.2014 1.00     Initial revision
*              : 27.08.2014 1.01     Not change program due to updating application note only.
*              : 30.01.2015 1.02     Added RX71M.
*              : 13.04.2015 1.03     Added RX231.
*******************************************************************************/

/*******************************************************************************
Includes <System Includes>, "Project Includes"
*******************************************************************************/
/* Definitions for DMACA support */
#include "r_dmaca_rx_if.h"
#include "./src/r_dmaca_rx_private.h"

/* Check MCU Group. */
#if defined(BSP_MCU_RX64M)

/*******************************************************************************
Macro definitions
*******************************************************************************/
typedef void (* DMACI_Callback)(void);

/*******************************************************************************
Private variables and functions
*******************************************************************************/

/* DMACA DMAC0I */
#pragma interrupt r_dmaca_intDMAC0I_isr(vect = VECT(DMAC, DMAC0I))
static void r_dmaca_intDMAC0I_isr(void);

/* DMACA DMAC1I */
#pragma interrupt r_dmaca_intDMAC1I_isr(vect = VECT(DMAC, DMAC1I))
static void r_dmaca_intDMAC1I_isr(void);

/* DMACA DMAC2I */
#pragma interrupt r_dmaca_intDMAC2I_isr(vect = VECT(DMAC, DMAC2I))
static void r_dmaca_intDMAC2I_isr(void);

/* DMACA DMAC3I */
#pragma interrupt r_dmaca_intDMAC3I_isr(vect = VECT(DMAC, DMAC3I))
static void r_dmaca_intDMAC3I_isr(void);

/* DMACA DMAC74I */
#pragma interrupt r_dmaca_intDMAC74I_isr(vect = VECT(DMAC, DMAC74I))
static void r_dmaca_intDMAC74I_isr(void);


/* Array of address of DMRSRm (m=DMACA channel number) */
volatile __evenaccess uint8_t *g_icu_dmrsr[] =
{
    &(ICU.DMRSR0), &(ICU.DMRSR1), &(ICU.DMRSR2), &(ICU.DMRSR3),
    &(ICU.DMRSR4), &(ICU.DMRSR5), &(ICU.DMRSR6), &(ICU.DMRSR7)
};

/*******************************************************************************
Exported global variables (to be accessed by other files)
*******************************************************************************/


/*******************************************************************************
* Function Name: r_dmaca_channel_valid_check
* Description  : Checks whether channel is valid or not.
* Arguments    : channel -
*                    Which channel to use
* Return Value : true -
*                    Channel is valid.
*                false -
*                    Channel is invalid.
*******************************************************************************/
bool r_dmaca_channel_valid_check(uint8_t channel)
{
    bool ret = false;

    switch (channel)
    {
        case DMACA_CH0:
        case DMACA_CH1:
        case DMACA_CH2:
        case DMACA_CH3:
        case DMACA_CH4:
        case DMACA_CH5:
        case DMACA_CH6:
        case DMACA_CH7:
            /* The channel number is valid. */
            ret = true;
        break;

        default:
            /* The channel number is invalid. */
            ret = false;
        break;
    }

    return ret;
}


/************************************************************************************
* Outline      : Interrupt DMAC0I handler
* Function Name: r_dmaca_intDMAC0I_isr
* Description  : Types of interrupt requests from DMACA channel 0.
*                If the pointer to function is 'FIT_NO_FUNC' or 'NULL',
*                write a program under "do something" in this
*                r_dmaca_intDMAC0I_isr() function.
* Arguments    : None
* Return Value : None
************************************************************************************/
static void r_dmaca_intDMAC0I_isr(void)
{
    if (((uint32_t)NULL != (uint32_t)p_DMACI_Handlers[DMACA_CH0]) &&
       ((uint32_t)FIT_NO_FUNC != (uint32_t)p_DMACI_Handlers[DMACA_CH0]))
    {
        ((DMACI_Callback)p_DMACI_Handlers[DMACA_CH0])();
    }
    else
    {
        /* do something */
    }

    return;
}


/************************************************************************************
* Outline      : Interrupt DMAC1I handler
* Function Name: r_dmaca_intDMAC1I_isr
* Description  : Types of interrupt requests from DMACA channel1.
*                If the pointer to function is 'FIT_NO_FUNC' or 'NULL',
*                write a program under "do something" in this 
*                r_dmaca_intDMAC1I_isr() function.
* Arguments    : None
* Return Value : None
************************************************************************************/
static void r_dmaca_intDMAC1I_isr(void)
{
    if (((uint32_t)NULL != (uint32_t)p_DMACI_Handlers[DMACA_CH1]) &&
       ((uint32_t)FIT_NO_FUNC != (uint32_t)p_DMACI_Handlers[DMACA_CH1]))
    {
        ((DMACI_Callback)p_DMACI_Handlers[DMACA_CH1])();
    }
    else
    {
        /* do something */
    }

    return;
}

/************************************************************************************
* Outline      : Interrupt DMAC2I handler
* Function Name: r_dmaca_intDMAC2I_isr
* Description  : Types of interrupt requests from DMACA channel2.
*                If the pointer to function is 'FIT_NO_FUNC' or 'NULL',
*                write a program under "do something" in this 
*                r_dmaca_intDMAC2I_isr() function.
* Arguments    : None
* Return Value : None
************************************************************************************/
static void r_dmaca_intDMAC2I_isr(void)
{
    if (((uint32_t)NULL != (uint32_t)p_DMACI_Handlers[DMACA_CH2]) &&
       ((uint32_t)FIT_NO_FUNC != (uint32_t)p_DMACI_Handlers[DMACA_CH2]))
    {
        ((DMACI_Callback)p_DMACI_Handlers[DMACA_CH2])();
    }
    else
    {
        /* do something */
    }

    return;
}


/************************************************************************************
* Outline      : Interrupt DMAC3I handler
* Function Name: r_dmaca_intDMAC3I_isr
* Description  : Types of interrupt requests from DMACA channel3.
*                If the pointer to function is 'FIT_NO_FUNC' or 'NULL',
*                write a program under "do something" in this 
*                r_dmaca_intDMAC3I_isr() function.
* Arguments    : None
* Return Value : None
************************************************************************************/
static void r_dmaca_intDMAC3I_isr(void)
{
    if (((uint32_t)NULL != (uint32_t)p_DMACI_Handlers[DMACA_CH3]) &&
       ((uint32_t)FIT_NO_FUNC != (uint32_t)p_DMACI_Handlers[DMACA_CH3]))
    {
        ((DMACI_Callback)p_DMACI_Handlers[DMACA_CH3])();
    }
    else
    {
        /* do something */
    }

    return;
}


/************************************************************************************
* Outline      : Interrupt DMAC74I handler
* Function Name: r_dmaca_intDMAC74I_isr
* Description  : Types of interrupt requests from DMACA channel4 to channel7.
*                If the pointer to function is 'FIT_NO_FUNC' or 'NULL',
*                write a program under the "do something" in this
*                r_dmaca_intDMAC74I_isr() function.
* Arguments    : None
* Return Value : None
************************************************************************************/
static void r_dmaca_intDMAC74I_isr(void)
{
    uint8_t channel;

    channel = DMAC.DMIST.BYTE;

    if (0x00 != (channel & DMACA_DMIS4_BIT_MASK))
    {
        if (((uint32_t)NULL != (uint32_t)p_DMACI_Handlers[DMACA_CH4]) &&
           ((uint32_t)FIT_NO_FUNC != (uint32_t)p_DMACI_Handlers[DMACA_CH4]))
        {
            ((DMACI_Callback)p_DMACI_Handlers[DMACA_CH4])();
        }
        else
        {
            /* do something */
        }
    }

    if (0x00 != (channel & DMACA_DMIS5_BIT_MASK))
    {
        if (((uint32_t)NULL != (uint32_t)p_DMACI_Handlers[DMACA_CH5]) &&
           ((uint32_t)FIT_NO_FUNC != (uint32_t)p_DMACI_Handlers[DMACA_CH5]))
        {
            ((DMACI_Callback)p_DMACI_Handlers[DMACA_CH5])();
        }
        else
        {
            /* do something */
        }
    }

    if (0x00 != (channel & DMACA_DMIS6_BIT_MASK))
    {
        if (((uint32_t)NULL != (uint32_t)p_DMACI_Handlers[DMACA_CH6]) &&
           ((uint32_t)FIT_NO_FUNC != (uint32_t)p_DMACI_Handlers[DMACA_CH6]))
        {
            ((DMACI_Callback)p_DMACI_Handlers[DMACA_CH6])();
        }
        else
        {
            /* do something */
        }
    }

    if (0x00 != (channel & DMACA_DMIS7_BIT_MASK))
    {
        if (((uint32_t)NULL != (uint32_t)p_DMACI_Handlers[DMACA_CH7]) &&
           ((uint32_t)FIT_NO_FUNC != (uint32_t)p_DMACI_Handlers[DMACA_CH7]))
        {
            ((DMACI_Callback)p_DMACI_Handlers[DMACA_CH7])();
        }
        else
        {
            /* do something */
        }
    }

    return;
}


/*******************************************************************************
* Function Name: r_dmaca_int_disable
* Description  : Disables DMACmI interrupt. (m = 0 to 3, or 74)
* Arguments    : channel -
*                    Which channel to use
* Return Value : DMACA_SUCCESS -
*                    DMACmI interrupt is disabled successfully.
*                DMACA_ERR_INVALID_CH -
*                    Channel is invalid.
*******************************************************************************/
dmaca_return_t r_dmaca_int_disable(uint8_t channel)
{

    /* Clear the DMACmI interrupt Enable bit. */
    /* Clear the DMACmI priority level. */
    switch (channel)
    {
        case DMACA_CH0:
            IEN(DMAC, DMAC0I) = 0;
            IPR(DMAC, DMAC0I) = 0;
        break;

        case DMACA_CH1:
            IEN(DMAC, DMAC1I) = 0;
            IPR(DMAC, DMAC1I) = 0;
        break;

        case DMACA_CH2:
            IEN(DMAC, DMAC2I) = 0;
            IPR(DMAC, DMAC2I) = 0;
        break;

        case DMACA_CH3:
            IEN(DMAC, DMAC3I) = 0;
            IPR(DMAC, DMAC3I) = 0;
        break;

        case DMACA_CH4:
            if (!(g_locking_sw[DMACA_CH5] || g_locking_sw[DMACA_CH6] || g_locking_sw[DMACA_CH7]))
            {
                IEN(DMAC, DMAC74I) = 0;
                IPR(DMAC, DMAC74I) = 0;
            }
        break;

        case DMACA_CH5:
            if (!(g_locking_sw[DMACA_CH4] || g_locking_sw[DMACA_CH6] || g_locking_sw[DMACA_CH7]))
            {
                IEN(DMAC, DMAC74I) = 0;
                IPR(DMAC, DMAC74I) = 0;
            }
        break;

        case DMACA_CH6:
            if (!(g_locking_sw[DMACA_CH4] || g_locking_sw[DMACA_CH5] || g_locking_sw[DMACA_CH7]))
            {
                IEN(DMAC, DMAC74I) = 0;
                IPR(DMAC, DMAC74I) = 0;
            }
        break;

        case DMACA_CH7:
            if (!(g_locking_sw[DMACA_CH4] || g_locking_sw[DMACA_CH5] || g_locking_sw[DMACA_CH6]))
            {
                IEN(DMAC, DMAC74I) = 0;
                IPR(DMAC, DMAC74I) = 0;
            }
        break;

        default:
            /* The channel number is invalid. */
            return DMACA_ERR_INVALID_CH;
        break;
    }

    if (0x00 == IPR(DMAC, DMAC0I))
    {
        /* do nothing */
    }

    return DMACA_SUCCESS;
}


/*******************************************************************************
* Function Name: r_dmaca_int_enable
* Description  : Enables DMACmI interrupt. (m = 0 to 3, or 74)
* Arguments    : channel -
*                    Which channel to use
*              : priority -
*                    DMACmI interrupt priority level
* Return Value : DMACA_SUCCESS -
*                    DMACmI interrupt is enabled successfully.
*                DMACA_ERR_INVALID_CH -
*                    Channel is invalid.
*******************************************************************************/
dmaca_return_t r_dmaca_int_enable(uint8_t channel, uint8_t priority)
{
    /* Set the DMACmI priority level. */
    /* Set the DMACmI interrupt Enable bit. */
    switch (channel)
    {
        case DMACA_CH0:
            IPR(DMAC, DMAC0I) = priority;
            IEN(DMAC, DMAC0I) = 1;
        break;

        case DMACA_CH1:
            IPR(DMAC, DMAC1I) = priority;
            IEN(DMAC, DMAC1I) = 1;
        break;

        case DMACA_CH2:
            IPR(DMAC, DMAC2I) = priority;
            IEN(DMAC, DMAC2I) = 1;
        break;

        case DMACA_CH3:
            IPR(DMAC, DMAC3I) = priority;
            IEN(DMAC, DMAC3I) = 1;
        break;

        case DMACA_CH4:
        case DMACA_CH5:
        case DMACA_CH6:
        case DMACA_CH7:
            /* The interrupt number is DMAC74I. */
            if (IPR(DMAC, DMAC74I) < priority)
            {
                IPR(DMAC, DMAC74I) = priority;
            }
            IEN(DMAC, DMAC74I) = 1;
        break;

        default:
            /* The channel number is invalid. */
            return DMACA_ERR_INVALID_CH;
        break;
    }

    if (0x00 == IEN(DMAC, DMAC0I))
    {
        /* do nothing */
    }

    return DMACA_SUCCESS;
}

/*******************************************************************************
* Function Name: r_dmaca_module_enable
* Description  : Releases module stop state.
* Arguments    : None
* Return Value : None
*******************************************************************************/
void r_dmaca_module_enable(void)
{
    /* Enable writing to MSTP registers. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);
    /* Release from module stop state. */
    MSTP(DMAC) = 0;
    /* Disable writing to MSTP registers. */
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);

    return;
}

/*******************************************************************************
* Function Name: r_dmaca_module_disable
* Description  : Sets to module stop state.
* Arguments    : None
* Return Value : None
*******************************************************************************/
void r_dmaca_module_disable(void)
{
    /* Enable writing to MSTP registers. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);
    /* Set to module stop state. */
    MSTP(DMAC) = 1;
    /* Disable writing to MSTP registers. */
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);

    return;
}

#if ((0 == BSP_CFG_USER_LOCKING_ENABLED) && (bsp_lock_t == BSP_CFG_USER_LOCKING_TYPE))
#if (1 != DMACA_CFG_USE_DTC_FIT_MODULE)
/*******************************************************************************
* Function Name: r_dmaca_check_DTC_locking_byUSER
* Description  : Checks DTC locking by user.
* Arguments    : none -
* Return Value : DMACA_ALL_CH_UNLOCKED_AND_DTC_UNLOCKED -
*                    All DMAC channels and DTC are unlocked.
*                DMACA_ALL_CH_UNLOCKED_BUT_DTC_LOCKED -
*                    All DMAC channels are unlocked, but DTC is locked.
*******************************************************************************/
dmaca_chk_locking_sw_t r_dmaca_check_DTC_locking_byUSER(void)
{
    dmaca_chk_locking_sw_t  ret = DMACA_ALL_CH_UNLOCKED_AND_DTC_UNLOCKED;
    
    /* User has to check the locking of DTC by themselves. */
    /* do something */

    return ret;
}
#endif  /* defined(1 != DMACA_CFG_USE_DTC_FIT_MODULE) */

#else
/*******************************************************************************
* Function Name: r_dmaca_check_DMACA_DTC_locking_byUSER
* Description  : Checks DMACA and DTC locking by user.
* Arguments    : none -
* Return Value : DMACA_ALL_CH_UNLOCKED_AND_DTC_UNLOCKED -
*                    All DMAC channels and DTC are unlocked.
*                DMACA_ALL_CH_UNLOCKED_BUT_DTC_LOCKED -
*                    All DMAC channels are unlocked, but DTC is locked.
*                DMACA_LOCKED_CH_EXIST -
*                    Other DMAC channels are locked.
*******************************************************************************/
dmaca_chk_locking_sw_t r_dmaca_check_DMACA_DTC_locking_byUSER(void)
{
    dmaca_chk_locking_sw_t  ret = DMACA_ALL_CH_UNLOCKED_AND_DTC_UNLOCKED;

    /* User has to check the locking of DMACA and DTC by themselves. */
    /* do something */

    return ret;
}

#endif

#endif /* defined(BSP_MCU_RX64M) */

/* End of File */


/*******************************************************************************
* File Name: VFD_CLOCK.h  
* Version 2.0
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_VFD_CLOCK_H) /* Pins VFD_CLOCK_H */
#define CY_PINS_VFD_CLOCK_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "VFD_CLOCK_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 VFD_CLOCK__PORT == 15 && ((VFD_CLOCK__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    VFD_CLOCK_Write(uint8 value) ;
void    VFD_CLOCK_SetDriveMode(uint8 mode) ;
uint8   VFD_CLOCK_ReadDataReg(void) ;
uint8   VFD_CLOCK_Read(void) ;
uint8   VFD_CLOCK_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define VFD_CLOCK_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define VFD_CLOCK_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define VFD_CLOCK_DM_RES_UP          PIN_DM_RES_UP
#define VFD_CLOCK_DM_RES_DWN         PIN_DM_RES_DWN
#define VFD_CLOCK_DM_OD_LO           PIN_DM_OD_LO
#define VFD_CLOCK_DM_OD_HI           PIN_DM_OD_HI
#define VFD_CLOCK_DM_STRONG          PIN_DM_STRONG
#define VFD_CLOCK_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define VFD_CLOCK_MASK               VFD_CLOCK__MASK
#define VFD_CLOCK_SHIFT              VFD_CLOCK__SHIFT
#define VFD_CLOCK_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define VFD_CLOCK_PS                     (* (reg8 *) VFD_CLOCK__PS)
/* Data Register */
#define VFD_CLOCK_DR                     (* (reg8 *) VFD_CLOCK__DR)
/* Port Number */
#define VFD_CLOCK_PRT_NUM                (* (reg8 *) VFD_CLOCK__PRT) 
/* Connect to Analog Globals */                                                  
#define VFD_CLOCK_AG                     (* (reg8 *) VFD_CLOCK__AG)                       
/* Analog MUX bux enable */
#define VFD_CLOCK_AMUX                   (* (reg8 *) VFD_CLOCK__AMUX) 
/* Bidirectional Enable */                                                        
#define VFD_CLOCK_BIE                    (* (reg8 *) VFD_CLOCK__BIE)
/* Bit-mask for Aliased Register Access */
#define VFD_CLOCK_BIT_MASK               (* (reg8 *) VFD_CLOCK__BIT_MASK)
/* Bypass Enable */
#define VFD_CLOCK_BYP                    (* (reg8 *) VFD_CLOCK__BYP)
/* Port wide control signals */                                                   
#define VFD_CLOCK_CTL                    (* (reg8 *) VFD_CLOCK__CTL)
/* Drive Modes */
#define VFD_CLOCK_DM0                    (* (reg8 *) VFD_CLOCK__DM0) 
#define VFD_CLOCK_DM1                    (* (reg8 *) VFD_CLOCK__DM1)
#define VFD_CLOCK_DM2                    (* (reg8 *) VFD_CLOCK__DM2) 
/* Input Buffer Disable Override */
#define VFD_CLOCK_INP_DIS                (* (reg8 *) VFD_CLOCK__INP_DIS)
/* LCD Common or Segment Drive */
#define VFD_CLOCK_LCD_COM_SEG            (* (reg8 *) VFD_CLOCK__LCD_COM_SEG)
/* Enable Segment LCD */
#define VFD_CLOCK_LCD_EN                 (* (reg8 *) VFD_CLOCK__LCD_EN)
/* Slew Rate Control */
#define VFD_CLOCK_SLW                    (* (reg8 *) VFD_CLOCK__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define VFD_CLOCK_PRTDSI__CAPS_SEL       (* (reg8 *) VFD_CLOCK__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define VFD_CLOCK_PRTDSI__DBL_SYNC_IN    (* (reg8 *) VFD_CLOCK__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define VFD_CLOCK_PRTDSI__OE_SEL0        (* (reg8 *) VFD_CLOCK__PRTDSI__OE_SEL0) 
#define VFD_CLOCK_PRTDSI__OE_SEL1        (* (reg8 *) VFD_CLOCK__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define VFD_CLOCK_PRTDSI__OUT_SEL0       (* (reg8 *) VFD_CLOCK__PRTDSI__OUT_SEL0) 
#define VFD_CLOCK_PRTDSI__OUT_SEL1       (* (reg8 *) VFD_CLOCK__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define VFD_CLOCK_PRTDSI__SYNC_OUT       (* (reg8 *) VFD_CLOCK__PRTDSI__SYNC_OUT) 


#if defined(VFD_CLOCK__INTSTAT)  /* Interrupt Registers */

    #define VFD_CLOCK_INTSTAT                (* (reg8 *) VFD_CLOCK__INTSTAT)
    #define VFD_CLOCK_SNAP                   (* (reg8 *) VFD_CLOCK__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_VFD_CLOCK_H */


/* [] END OF FILE */

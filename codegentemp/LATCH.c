/*******************************************************************************
* File Name: LATCH.c  
* Version 2.0
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "LATCH.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 LATCH__PORT == 15 && ((LATCH__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: LATCH_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None
*  
*******************************************************************************/
void LATCH_Write(uint8 value) 
{
    uint8 staticBits = (LATCH_DR & (uint8)(~LATCH_MASK));
    LATCH_DR = staticBits | ((uint8)(value << LATCH_SHIFT) & LATCH_MASK);
}


/*******************************************************************************
* Function Name: LATCH_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  LATCH_DM_STRONG     Strong Drive 
*  LATCH_DM_OD_HI      Open Drain, Drives High 
*  LATCH_DM_OD_LO      Open Drain, Drives Low 
*  LATCH_DM_RES_UP     Resistive Pull Up 
*  LATCH_DM_RES_DWN    Resistive Pull Down 
*  LATCH_DM_RES_UPDWN  Resistive Pull Up/Down 
*  LATCH_DM_DIG_HIZ    High Impedance Digital 
*  LATCH_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void LATCH_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(LATCH_0, mode);
}


/*******************************************************************************
* Function Name: LATCH_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro LATCH_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 LATCH_Read(void) 
{
    return (LATCH_PS & LATCH_MASK) >> LATCH_SHIFT;
}


/*******************************************************************************
* Function Name: LATCH_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 LATCH_ReadDataReg(void) 
{
    return (LATCH_DR & LATCH_MASK) >> LATCH_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(LATCH_INTSTAT) 

    /*******************************************************************************
    * Function Name: LATCH_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 LATCH_ClearInterrupt(void) 
    {
        return (LATCH_INTSTAT & LATCH_MASK) >> LATCH_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */

/*******************************************************************************
* File Name: VFD_CLOCK.c  
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
#include "VFD_CLOCK.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 VFD_CLOCK__PORT == 15 && ((VFD_CLOCK__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: VFD_CLOCK_Write
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
void VFD_CLOCK_Write(uint8 value) 
{
    uint8 staticBits = (VFD_CLOCK_DR & (uint8)(~VFD_CLOCK_MASK));
    VFD_CLOCK_DR = staticBits | ((uint8)(value << VFD_CLOCK_SHIFT) & VFD_CLOCK_MASK);
}


/*******************************************************************************
* Function Name: VFD_CLOCK_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  VFD_CLOCK_DM_STRONG     Strong Drive 
*  VFD_CLOCK_DM_OD_HI      Open Drain, Drives High 
*  VFD_CLOCK_DM_OD_LO      Open Drain, Drives Low 
*  VFD_CLOCK_DM_RES_UP     Resistive Pull Up 
*  VFD_CLOCK_DM_RES_DWN    Resistive Pull Down 
*  VFD_CLOCK_DM_RES_UPDWN  Resistive Pull Up/Down 
*  VFD_CLOCK_DM_DIG_HIZ    High Impedance Digital 
*  VFD_CLOCK_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void VFD_CLOCK_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(VFD_CLOCK_0, mode);
}


/*******************************************************************************
* Function Name: VFD_CLOCK_Read
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
*  Macro VFD_CLOCK_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 VFD_CLOCK_Read(void) 
{
    return (VFD_CLOCK_PS & VFD_CLOCK_MASK) >> VFD_CLOCK_SHIFT;
}


/*******************************************************************************
* Function Name: VFD_CLOCK_ReadDataReg
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
uint8 VFD_CLOCK_ReadDataReg(void) 
{
    return (VFD_CLOCK_DR & VFD_CLOCK_MASK) >> VFD_CLOCK_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(VFD_CLOCK_INTSTAT) 

    /*******************************************************************************
    * Function Name: VFD_CLOCK_ClearInterrupt
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
    uint8 VFD_CLOCK_ClearInterrupt(void) 
    {
        return (VFD_CLOCK_INTSTAT & VFD_CLOCK_MASK) >> VFD_CLOCK_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */

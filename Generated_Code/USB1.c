/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : USB1.c
**     Project     : ProcessorExpert
**     Processor   : MK60DN512ZVLQ10
**     Component   : FSL_USB_Stack
**     Version     : Component 01.024, Driver 01.00, CPU db: 3.00.001
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-01-08, 10:58, # CodeGen: 2
**     Abstract    :
**         This component implements a wrapper to the FSL USB Stack.
**     Settings    :
**          Component name                                 : USB1
**          Freescale USB Stack Version                    : v4.1.1
**          USB                                            : Init_USB_OTG_VAR0
**          Device Class                                   : CDC Device
**          CDC Device                                     : Enabled
**            CDCDevice                                    : FSL_USB_CDC_Device
**          HID Keyboard Device                            : Disabled
**          MSD Host                                       : Disabled
**          Call Init Method                               : yes
**     Contents    :
**         Init - byte USB1_Init(void);
**
**     (c) Copyright Freescale, all rights reserved, 2013.
**     Ported as Processor Expert component: Erich Styger
**     http: www.mcuoneclipse.com
** ###################################################################*/
/*!
** @file USB1.c
** @version 01.00
** @brief
**         This component implements a wrapper to the FSL USB Stack.
*/         
/*!
**  @addtogroup USB1_module USB1 module documentation
**  @{
*/         

/* MODULE USB1. */

#include "USB1.h"
#include "derivative.h"     /* include peripheral declarations */
#include "types.h"          /* Contains User Defined Data Types */

/*
** ===================================================================
**     Method      :  USB1_usb_int_dis (component FSL_USB_Stack)
**
**     Description :
**         Disables USB interrupts (if supported)
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void USB1_usb_int_dis(void)
{
  /* Kinetis K60 */
#if !HIGH_SPEED_DEVICE
  NVICICER2 = (1<<9);   /* Disable interrupts from USB module (Interrupt Clear-Enable Register) */
#else
  NVICICER3 = 1;        /* Disable interrupts on USBHS (Interrupt Clear-Enable Register) */
#endif
}

/*
** ===================================================================
**     Method      :  USB1_usb_int_en (component FSL_USB_Stack)
**
**     Description :
**         Enables USB interrupts (if supported).
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void USB1_usb_int_en(void)
{
  /* Kinetis K60 */
#if !HIGH_SPEED_DEVICE
  NVICICPR2 = (1<<9);   /* Clear any pending interrupts on USB (Interrupt Clear-Pending Register) */
  NVICISER2 = (1<<9);   /* Enable interrupts from USB module (Interrupt Set-Enable Register) */
#else
  NVICICPR3 = 1;        /* Clear any pending interrupts on USBHS (Interrupt Clear-Pending Register) */
  NVICISER3 = 1;        /* Enable interrupts on USBHS (Interrupt Set-Enable Register) */
#endif
}

/*
** ===================================================================
**     Method      :  USB1_Init (component FSL_USB_Stack)
**     Description :
**         Initializes the driver
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
byte USB1_Init(void)
{
  byte err;

  /* Initialize the USB interface */
  err = CDC1_Init();
  if(err != ERR_OK) {
    /* Error initializing USB Class */
    return ERR_FAILED;
  }
  USB1_usb_int_en();
  return ERR_OK;
}

/* END USB1. */

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.2 [05.07]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/

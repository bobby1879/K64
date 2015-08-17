/* ###################################################################
**     Filename    : rtos_main_task.c
**     Project     : K64
**     Processor   : MK64FN1M0VLL12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-06-05, 12:53, # CodeGen: 1
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         main_task - void main_task(os_task_param_t task_init_data);
**
** ###################################################################*/
/*!
** @file rtos_main_task.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup rtos_main_task_module rtos_main_task module documentation
**  @{
*/         
/* MODULE rtos_main_task */

#include "Cpu.h"
#include "Events.h"
#include "rtos_main_task.h"
#include "gmeter/FXOS8700CQ.h"
#include <math.h>
#ifdef __cplusplus
extern "C" {
#endif 


#ifdef MainTask_PEX_RTOS_COMPONENTS_INIT
extern void PEX_components_init(void);
#endif 

void main_task(os_task_param_t task_init_data)
{

	SRAWDATA AccelData;
	float angleX,angleY,tmp;
	int i;
  PEX_components_init(); 

  gmeterInit();
  PORT_MemMapPtr pctl;
  pctl = (PORT_MemMapPtr)PORTC_BASE_PTR;
  pctl->PCR[1] = PORT_PCR_MUX(4) | PORT_PCR_ODE_MASK ;	// alternate function
  SIM_SCGC6 |= (1 << 24); // FTM0 CLK enable
  FTM0_MODE |= (1 <<  2); //write protect --enable
  FTM0_SC |= (1 << 3); //system clock clk div
  FTM0_SC |= 0x07; // 128 clk div
  FTM0_C0SC |= ( 1 << 5) | ( 1 << 3) ; // write protected
  FTM0_MOD = 9380; // bse freq
  FTM0_C0V = 469;  //duty cycle
  FTM0_MODE |= (1 <<  1); //initialize



  while (1) {
	  gmeterRead(&AccelData,NULL);
	  //printf("%+4d  %+4d  %+4d\n",AccelData.x, AccelData.y,AccelData.z);
	 // calculateAngle(&AccelData);
	  for( i = 469; i < 938; i++ )
	  {
		  FTM0_C0V = i;
		  OSA_TimeDelay(10);
	  }


    

  }

}

/* END rtos_main_task */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/

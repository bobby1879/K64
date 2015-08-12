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
  PEX_components_init(); 

  gmeterInit();

  while (1) {
	  gmeterRead(&AccelData,NULL);
	  //printf("%+4d  %+4d  %+4d\n",AccelData.x, AccelData.y,AccelData.z);
	  calculateAngle(&AccelData);
	  OSA_TimeDelay(100);
    

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

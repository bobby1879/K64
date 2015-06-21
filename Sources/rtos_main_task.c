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


/* User includes (#include below this line is not maintained by Processor Expert) */

/* Initialization of Processor Expert components function prototype */
#ifdef MainTask_PEX_RTOS_COMPONENTS_INIT
extern void PEX_components_init(void);
#endif 

/*
** ===================================================================
**     Event       :  main_task (module rtos_main_task)
**
**     Component   :  MainTask [OS_Task]
*/
/*!
**     @brief
**         RTOS task routine. The routine is generated into os_tasks.c
**         file.
**     @param
**         task_init_data  - Parameter to be passed to the
**         task when it is created.
*/
/* ===================================================================*/
void main_task(os_task_param_t task_init_data)
{

	SRAWDATA AccelData;
	float angleX,angleY,tmp;
  PEX_components_init(); 

  gmeterInit();

  while (1) {

	  int16_t x,y;
	  gmeterRead(&AccelData,NULL);

	  tmp = (float)AccelData.y/(float)AccelData.z;
	  angleY = atan(tmp);
	  angleY *= 57.2958; // to rad (pi / 180)
	  tmp = (float)AccelData.x/(float)AccelData.z;
	  angleX = atan(tmp);
	  angleX *= 57.2958; // to rad (pi / 180)
	  x = round(angleX);
	  y = round(angleY);

	  printf("%d %d\n",x, y);
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

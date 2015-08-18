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
  FTM0_C0V = 690;  //duty cycle
  FTM0_MODE |= (1 <<  1); //initialize

  setFtmDegrees(85);
  _mqx_int pitch,roll;
  while (1)
  {

	  for( i = 0; i < 180; i++ )
	  {
		  gmeterRead(&AccelData,NULL);
		  calculateAngle(&AccelData, &roll, &pitch);
		//  setFtmDegrees(i);
		  OSA_TimeDelay(50);
		  printf("%3d  %+3d\n",roll,pitch);
	  }
  }

}

// range -90:90 = 469:938
_mqx_int getFtmDegrees(void)
{
	float bulharka = 2.6,tmp;
	uint16_t reg = FTM0_C0V;
	_mqx_int degrees = (reg - 469);
	tmp = (float)degrees / 2.6;
	return (_mqx_int)tmp;
}

void setFtmDegrees( _mqx_int degrees)
{
	float bulharka = 2.6,tmp;
	tmp = 2.6 * (float)degrees;
	FTM0_C0V = (uint16_t)tmp + 469;

}

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

/*
 * FXOS8700CQ.h
 *
 *  Created on: Jun 21, 2015
 *      Author: madman
 */

#ifndef SOURCES_GMETER_FXOS8700CQ_H_
#define SOURCES_GMETER_FXOS8700CQ_H_

#include "i2c_compS.h"

#define FXOS8700CQ_STATUS 0x00
#define FXOS8700CQ_WHOAMI 0x00
#define FXOS8700CQ_XYZ_DATA_CFG 0x0E
#define FXOS8700CQ_CTRL_REG1 0x2A
#define FXOS8700CQ_M_CTRL_REG1 0x5B
#define FXOS8700CQ_M_CTRL_REG2 0x5C
#define FXOS8700CQ_WHOAMI_VAL 0xC7
#define FXOS8700CQ_READ_LEN 13

typedef struct
{
int16_t x;
int16_t y;
int16_t z;

} SRAWDATA;

int gmeterIdentify(void);
void gmeterInit(void);
void gmeterRead(SRAWDATA *pAccelData, SRAWDATA *pMagnData);



#endif /* SOURCES_GMETER_FXOS8700CQ_H_ */

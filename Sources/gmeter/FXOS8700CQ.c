/*
 * FXOS8700CQ.c
 *
 *  Created on: Jun 21, 2015
 *      Author: madman
 *      configuration from datasheet
 */
#include "FXOS8700CQ.h"


int gmeterIdentify(void){
	  uint8_t data;
	  uint8_t addr = FXOS8700CQ_WHOAMI;

	  I2C_DRV_MasterReceiveDataBlocking(FSL_I2C_COMPS,&i2c_gmeter,&addr,1,&data,1,20);
	  if(data != FXOS8700CQ_WHOAMI_VAL)
		  return 1;
	  return 0;
}

void gmeterInit(void){

	uint8_t data[2];

	//standby
	data[0] = FXOS8700CQ_CTRL_REG1;
	data[1] = 0;
	I2C_DRV_MasterSendDataBlocking(FSL_I2C_COMPS,&i2c_gmeter,0,0,data,2,10);

	// write 0001 1111 = 0x1F to magnetometer control register 1
	// [7]: m_acal=0: auto calibration disabled
	// [6]: m_rst=0: no one-shot magnetic reset
	// [5]: m_ost=0: no one-shot magnetic measurement
	// [4-2]: m_os=111=7: 8x oversampling (for 200Hz) to reduce magnetometer noise
	// [1-0]: m_hms=11=3: select hybrid mode with accel and magnetometer active
	data[0] =  FXOS8700CQ_M_CTRL_REG1;
	data[1] = 0x1f;
	I2C_DRV_MasterSendDataBlocking(FSL_I2C_COMPS,&i2c_gmeter,0,0,data,2,10);

	// write 0010 0000 = 0x20 to magnetometer control register 2
	// [7]: reserved
	// [6]: reserved
	// [5]: hyb_autoinc_mode=1 to map the magnetometer registers to follow the
	// accelerometer registers
	// [4]: m_maxmin_dis=0 to retain default min/max latching even though not used
	// [3]: m_maxmin_dis_ths=0
	// [2]: m_maxmin_rst=0
	// [1-0]: m_rst_cnt=00 to enable magnetic reset each cycle
	data[0] =  FXOS8700CQ_M_CTRL_REG2;
	data[1] = 0x20;
	I2C_DRV_MasterSendDataBlocking(FSL_I2C_COMPS,&i2c_gmeter,0,0,data,2,10);

	// write 0000 0001= 0x01 to XYZ_DATA_CFG register
	// [7]: reserved
	// [6]: reserved
	// [5]: reserved
	// [4]: hpf_out=0
	// [3]: reserved
	// [2]: reserved
	// [1-0]: fs=01 for accelerometer range of +/-4g range with 0.488mg/LSB
	data[0] =  FXOS8700CQ_XYZ_DATA_CFG;
	data[1] = 0x01;
	I2C_DRV_MasterSendDataBlocking(FSL_I2C_COMPS,&i2c_gmeter,0,0,data,2,10);

	// write 0000 1101 = 0x0D to accelerometer control register 1
	// [7-6]: aslp_rate=00
	// [5-3]: dr=001 for 200Hz data rate (when in hybrid mode)
	// [2]: lnoise=1 for low noise mode
	// [1]: f_read=0 for normal 16 bit reads
	// [0]: active=1 to take the part out of standby and enable sampling
	data[0] =   FXOS8700CQ_CTRL_REG1;
	data[1] = 0x0D;
	I2C_DRV_MasterSendDataBlocking(FSL_I2C_COMPS,&i2c_gmeter,0,0,data,2,10);
}

void gmeterRead(SRAWDATA *pAccelData, SRAWDATA *pMagnData){
	uint8_t addr =  FXOS8700CQ_STATUS;
	uint8_t Buffer[FXOS8700CQ_READ_LEN] = {0};
	I2C_DRV_MasterReceiveDataBlocking(FSL_I2C_COMPS,&i2c_gmeter,&addr,1,Buffer,FXOS8700CQ_READ_LEN,50);
	if( pAccelData != NULL){
	// copy the 14 bit accelerometer byte data into 16 bit words
	pAccelData->x = (int16_t)(((Buffer[1] << 8) | Buffer[2]))>> 2;
	pAccelData->y = (int16_t)(((Buffer[3] << 8) | Buffer[4]))>> 2;
	pAccelData->z = (int16_t)(((Buffer[5] << 8) | Buffer[6]))>> 2;
	}
	if( pMagnData != NULL){
	// copy the magnetometer byte data into 16 bit words
	pMagnData->x = (Buffer[7] << 8) | Buffer[8];
	pMagnData->y = (Buffer[9] << 8) | Buffer[10];
	pMagnData->z = (Buffer[11] << 8) | Buffer[12];
	}
}



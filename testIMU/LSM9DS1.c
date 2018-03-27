/***************************************************************
*
* LSM9DS1 chip on Sparkfun 9DOF Stick Module
* Author: Simon Reinbold
* Last Update: 26.03.2018
*
***************************************************************/

#include <stdint.h>
#include <avr/io.h>
#include "LSM9DS1.h"
#include "../I2C/twi.h"

/*******************************
*
*  Setup Methods
*
********************************/

uint8_t setup_LSM9DS1(){	
	setup_acceleration_sensor();
	setup_gyro_sensor();
	// TODO return parameter neglected
	return SENSOR_OK;
}

uint8_t setup_acceleration_sensor(){
	master_config_register(ADDR_ACC_GYRO,CTRL_REG6_XL,CTRL_REG6_XL_SCALE_2_G);
	// TODO return parameter neglected
	return SENSOR_OK;
}

uint8_t setup_gyro_sensor(){
	master_config_register(ADDR_ACC_GYRO,CTRL_REG1_G,CTRL_REG1_G_DATA_RATE_119_HZ|CTRL_REG1_G_SCALE_245_DPS|CTRL_REG1_G_BW);
	master_config_register(ADDR_ACC_GYRO,CTRL_REG3_G,CTRL_REG3_G_LOW_POWER_ENABLE);
	// TODO return parameter neglected
	return SENSOR_ERROR;
}

/*******************************
*
* Sensor Readout Methods
*
********************************/

uint8_t get_acc_and_gyro_data(){
	if(master_read_register(ADDR_ACC_GYRO,OUT_X_L_XL,12) == OK_FLG){
		return SENSOR_OK;
	}
	else{
		return SENSOR_ERROR;
	}
}
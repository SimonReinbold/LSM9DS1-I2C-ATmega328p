/***************************************************************
*
* Definition header for LSM9DS1 chip on Sparkfun 9DOF Stick Module
* Author: Simon Reinbold
* Last Update: 26.03.2018
*
***************************************************************/

#ifndef _LSM9DS1_
#define _LSM9DS1_

/*******************************
*
* Config Parameter
*
********************************/

// GYRO parameters

#define CTRL_REG1_G_POWER_DOWN			0x00
#define CTRL_REG1_G_DATA_RATE_14_9_HZ	0x20
#define CTRL_REG1_G_DATA_RATE_59_5_HZ	0x40
#define CTRL_REG1_G_DATA_RATE_119_HZ	0x60
#define CTRL_REG1_G_DATA_RATE_238_HZ	0x80
#define CTRL_REG1_G_DATA_RATE_476_HZ	0xA0
#define CTRL_REG1_G_DATA_RATE_952_HZ	0xC0

#define CTRL_REG1_G_SCALE_245_DPS		0x00
#define CTRL_REG1_G_SCALE_500_DPS		0x08
#define CTRL_REG1_G_SCALE_2000_DPS		0x18

#define CTRL_REG1_G_BW					0x00

#define CTRL_REG3_G_LOW_POWER_ENABLE	0x80

// ACCELEROMETER parameters

#define CTRL_REG6_XL_POWER_DOWN			0x00
#define CTRL_REG6_XL_DATA_RATE_10_HZ	0x20
#define CTRL_REG6_XL_DATA_RATE_50_HZ	0x40
#define CTRL_REG6_XL_DATA_RATE_119_HZ	0x60
#define CTRL_REG6_XL_DATA_RATE_238_HZ	0x80
#define CTRL_REG6_XL_DATA_RATE_476_HZ	0xA0
#define CTRL_REG6_XL_DATA_RATE_952_HZ	0xC0

#define CTRL_REG6_XL_SCALE_2_G			0x00
#define CTRL_REG6_XL_SCALE_4_G			0x10
#define CTRL_REG6_XL_SCALE_8_G			0x18
#define CTRL_REG6_XL_SCALE_16_G			0x08
// Bandwidth auto select set automatically

/*******************************
*
* Flags
*
********************************/

#define SENSOR_ERROR					0xFF
#define SENSOR_OK						0x00

/*******************************
*
* Function List
*
********************************/

uint8_t setup_LSM9DS1();
uint8_t setup_acceleration_sensor();
uint8_t setup_gyro_sensor();
uint8_t get_acc_and_gyro_data();

// Addresses

#define ADDR_MAGNETO 	0x1E		
#define ADDR_ACC_GYRO 	0x6B

/*******************************
*
* Register List
*
********************************/

// Accelerometer and Gyroscope	

#define ACT_THS 			0x04
#define ACT_DUR 			0x05
#define INT_GEN_CFG_XL 		0x06
#define INT_GEN_THS_X_XL 	0x07
#define INT_GEN_THS_Y_XL 	0x08
#define INT_GEN_THS_Z_XL 	0x09
#define INT_GEN_DUR_XL 		0x0A
#define REFERENCE_G 		0x0B
#define INT1_CTRL 			0x0C
#define INT2_CTRL 			0x0D
#define WHO_AM_I 			0x0F
#define CTRL_REG1_G 		0x10
#define CTRL_REG2_G 		0x11
#define CTRL_REG3_G 		0x12
#define ORIENT_CFG_G 		0x13
#define INT_GEN_SRC_G 		0x14
#define OUT_TEMP_L 			0x15
#define OUT_TEMP_H 			0x16
#define STATUS_REG1 			0x17
#define OUT_X_L_G 			0x18
#define OUT_X_H_G 			0x19
#define OUT_Y_L_G 			0x1A
#define OUT_Y_H_G 			0x1B
#define OUT_Z_L_G 			0x1C
#define OUT_Z_H_G 			0x1D
#define CTRL_REG4 			0x1E
#define CTRL_REG5_XL 		0x1F
#define CTRL_REG6_XL 		0x20
#define CTRL_REG7_XL 		0x21
#define CTRL_REG8 			0x22
#define CTRL_REG9 			0x23
#define CTRL_REG10 			0x24
#define INT_GEN_SRC_XL 		0x26
#define STATUS_REG2 			0x27
#define OUT_X_L_XL 			0x28
#define OUT_X_H_XL 			0x29
#define OUT_Y_L_XL 			0x2A
#define OUT_Y_H_XL 			0x2B
#define OUT_Z_L_XL 			0x2C
#define OUT_Z_H_XL 			0x2D
#define FIFO_CTRL 			0x2E
#define FIFO_SRC 			0x2F
#define INT_GEN_CFG_G 		0x30
#define INT_GEN_THS_XH_G 	0x31
#define INT_GEN_THS_XL_G 	0x32
#define INT_GEN_THS_YH_G 	0x33
#define INT_GEN_THS_YL_G 	0x34
#define INT_GEN_THS_ZH_G 	0x35
#define INT_GEN_THS_ZL_G 	0x36
#define INT_GEN_DUR_G 		0x37

// Magnetic Sensor

#define OFFSET_X_REG_L_M 	0x05
#define OFFSET_X_REG_H_M 	0x06
#define OFFSET_Y_REG_L_M 	0x07
#define OFFSET_Y_REG_H_M 	0x08
#define OFFSET_Z_REG_L_M 	0x09
#define OFFSET_Z_REG_H_M 	0x0A
#define WHO_AM_I			0x0F
#define CTRL_REG1_M 		0x20
#define CTRL_REG2_M 		0x21
#define CTRL_REG3_M 		0x22
#define CTRL_REG4_M 		0x23
#define CTRL_REG5_M 		0x24
#define STATUS_REG_M 		0x27 
#define OUT_X_L_M 			0x28 
#define OUT_X_H_M 			0x29 
#define OUT_Y_L_M 			0x2A 
#define OUT_Y_H_M 			0x2B 
#define OUT_Z_L_M 			0x2C 
#define OUT_Z_H_M 			0x2D 
#define INT_CFG_M 			0x30 
#define INT_SRC_M 			0x31
#define INT_THS_L_M 		0x32 
#define INT_THS_H_M 		0x33

#endif /* _LSM9DS1_ */
/***************************************************************
*
* IMU module communication
* Author: Simon Reinbold
* Last Update: 26.03.2018
*
***************************************************************/

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "LSM9DS1.h"
#include "../I2C/twi.h"
#include "imu.h"

void init_IMU(){
	init_twi();
	setup_LSM9DS1();
	calc_stationary_alignment();
}

void calc_stationary_alignment(){
	int16_t counter = 0;
	float gRange = 0.061*1000;
	
	while(counter < 100){
		if(get_acc_and_gyro_data()==SENSOR_OK){
			counter += 1;
			//Handle Data
			a_x_K_G_IB_B_mDs2 = ((float)( (int16_t)(payload[1]<<8 | payload[0]) ) )*gRange;
			a_y_K_G_IB_B_mDs2 = ((float)( (int16_t)(payload[3]<<8 | payload[2]) ) )*gRange;
			a_z_K_G_IB_B_mDs2 = ((float)( (int16_t)(payload[5]<<8 | payload[4]) ) )*gRange;
			
			a_x_K_G_IB_B_ave_mDs2 = ( (a_x_K_G_IB_B_ave_mDs2*(counter-1))+a_x_K_G_IB_B_mDs2 )/counter;
			a_y_K_G_IB_B_ave_mDs2 = ( (a_y_K_G_IB_B_ave_mDs2*(counter-1))+a_y_K_G_IB_B_mDs2 )/counter;
			a_z_K_G_IB_B_ave_mDs2 = ( (a_z_K_G_IB_B_ave_mDs2*(counter-1))+a_z_K_G_IB_B_mDs2 )/counter;
			acc_K_G_IB_B_abs_ave_mDs2 = sqrt(pow(a_x_K_G_IB_B_ave_mDs2,1)+pow(a_y_K_G_IB_B_ave_mDs2,2)+pow(a_z_K_G_IB_B_ave_mDs2,2));
			
			theta_SA_rad = asin(a_x_K_G_IB_B_ave_mDs2/acc_K_G_IB_B_abs_ave_mDs2)*180/PI;
			phi_SA_rad = atan2(-a_y_K_G_IB_B_ave_mDs2,a_z_K_G_IB_B_ave_mDs2)*180/PI;
		}
	}
}

/***************************************************************
*
* IMU module communication
* Author: Simon Reinbold
* Last Update: 26.03.2018
*
***************************************************************/

#ifndef IMU_H_
#define IMU_H_

/*******************************
*
* Variables
*
********************************/

// Public Variables
float a_x_K_G_IB_B_mDs2, a_y_K_G_IB_B_mDs2, a_z_K_G_IB_B_mDs2;
float w_x_K_IB_B_radDs, w_y_K_IB_B_radDs, w_z_K_IB_B_radDs;
float psi_SA_rad, theta_SA_rad, phi_SA_rad;

// Internal variables
float a_x_K_G_IB_B_ave_mDs2, a_y_K_G_IB_B_ave_mDs2, a_z_K_G_IB_B_ave_mDs2, acc_K_G_IB_B_abs_ave_mDs2;

/*******************************
*
* Constants
*
********************************/

#define STATIONARY_ALIGN_TIME_S		10
#define PI 3.14159265358979323846

/*******************************
*
* Functions
*
********************************/

void init_IMU();
void calc_stationary_alignment();

#endif /* IMU_H_ */
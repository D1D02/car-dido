/*
 * MPU6050.h
 *
 *  Created on: 21 mag 2026
 *      Author: arrow
 */

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_

#include "hal.h"
#include "cfg/MPU6050_CFG.h"

extern const I2CConfig i2ccfg;

typedef struct MPU6050_STRUCT {
  float ax;
  float ay;
  float az;
  float t;
  float gx;
  float gy;
  float gz;
}mpu6050_data_t;

void MPU6050_init( I2CDriver * );

#endif /* INC_MPU6050_H_ */

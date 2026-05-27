/*
 * MPU6050.c
 *
 *  Created on: 21 mag 2026
 *      Author: arrow
 */
#include "../inc/MPU6050.h"

//100khz configuration
const I2CConfig i2ccfg = {
  STM32_TIMINGR_PRESC(15U) |
  STM32_TIMINGR_SCLDEL(4U) | STM32_TIMINGR_SDADEL(2U) |
  STM32_TIMINGR_SCLH(15U)  | STM32_TIMINGR_SCLL(21U),
  0,
  0
};

static void MPU6050_write_reg( I2CDriver *i2cp, uint8_t reg, uint8_t val )
{

  uint8_t txbuf[2] = { reg, val };
  i2cAcquireBus( i2cp );
  i2cMasterTransmitTimeout( i2cp, MPU6050_ADDR, txbuf, 2, NULL, 0, TIME_MS2I(10) );
  i2cReleaseBus( i2cp );

}

void MPU6050_init( I2CDriver * i2cd )
{

  MPU6050_write_reg( i2cd, SMPLRT_DIV_CFG_REG, SMPLRT_DIV_CFG_REG_VAL );
  MPU6050_write_reg( i2cd, MPU6050_LPF_CFG_REG, MPU6050_LPF_3_DEL_5 );
  MPU6050_write_reg( i2cd, MPU6050_GYRO_RAD_CFG_REG, MPU6050_GYROSCOPE_250d_s );
  MPU6050_write_reg( i2cd, MPU6050_ACC_G_CFG_REG, MPU6050_ACCELEROMETER_2g );

}

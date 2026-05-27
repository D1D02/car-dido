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
  MPU6050_write_reg( i2cd, MPU6050_LPF_CFG_REG, MPU6050_LPF_CFG_VAL );
  MPU6050_write_reg( i2cd, MPU6050_GYRO_RAD_CFG_REG, MPU6050_GYROSCOPE_CFG_VAL );
  MPU6050_write_reg( i2cd, MPU6050_ACC_G_CFG_REG, MPU6050_ACCELEROMETER_CFG_VAL );

}

msg_t MPU6050_read_data(  I2CDriver * i2cd, mpu6050_data_t * dest )
{
  uint8_t tx_buf[1] = { MPU6050_DATA_START };
  uint8_t rx_buf[14];
  msg_t status;

  i2cAcquireBus(i2cd);
  status = i2cMasterTransmitTimeout(i2cd, MPU6050_ADDR, tx_buf, 1, rx_buf, 14, TIME_MS2I(10));
  i2cReleaseBus(i2cd);

  if ( status == MSG_OK )
  {
    int16_t raw_ax = (int16_t)((rx_buf[0]  << 8) | rx_buf[1]);
    int16_t raw_ay = (int16_t)((rx_buf[2]  << 8) | rx_buf[3]);
    int16_t raw_az = (int16_t)((rx_buf[4]  << 8) | rx_buf[5]);
    int16_t raw_t  = (int16_t)((rx_buf[6]  << 8) | rx_buf[7]);
    int16_t raw_gx = (int16_t)((rx_buf[8]  << 8) | rx_buf[9]);
    int16_t raw_gy = (int16_t)((rx_buf[10] << 8) | rx_buf[11]);
    int16_t raw_gz = (int16_t)((rx_buf[12] << 8) | rx_buf[13]);

    dest->ax = (float)raw_ax / MPU6050_ACCELEROMETER_LSB_SENS;
    dest->ay = (float)raw_ay / MPU6050_ACCELEROMETER_LSB_SENS;
    dest->az = (float)raw_az / MPU6050_ACCELEROMETER_LSB_SENS;

    dest->t  = ((float)raw_t / 340.0f) + 36.53f;

    dest->gx = (float)raw_gx / MPU6050_GYRO_LSB_SENS;
    dest->gy = (float)raw_gy / MPU6050_GYRO_LSB_SENS;
    dest->gz = (float)raw_gz / MPU6050_GYRO_LSB_SENS;

  }

  return status;

}

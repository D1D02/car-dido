/*
 * MPU6050.c
 *
 *  Created on: 21 mag 2026
 *      Author: arrow
 */
#include "../inc/MPU6050.h"

const I2CConfig i2ccfg = {
  STM32_TIMINGR_PRESC(15U) |
  STM32_TIMINGR_SCLDEL(4U) | STM32_TIMINGR_SDADEL(2U) |
  STM32_TIMINGR_SCLH(15U)  | STM32_TIMINGR_SCLL(21U),
  0,
  0
};


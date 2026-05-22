#include "ch.h"
#include "hal.h"
#include "inc/main.h"
#include "rt_test_root.h"
#include "oslib_test_root.h"

static THD_WORKING_AREA(waLedBlink, 128);
static THD_FUNCTION(ThreadLed, arg) {

  (void)arg;
  chRegSetThreadName("led_thread");
  while (true)
  {

    palClearLine(LINE_LED_GREEN);
    chThdSleepMilliseconds(1500);
    palSetLine(LINE_LED_GREEN);
    chThdSleepMilliseconds(1500);

  }

}



int main(void) {

  halInit();
  chSysInit();


  i2cStart(&I2CD2, &i2ccfg);
  chThdCreateStatic(waLedBlink, sizeof(waLedBlink), NORMALPRIO, ThreadLed, NULL);

  while (true) {

    chThdSleepMilliseconds(10000);
  }
}

/*

  sioStart(&LPSIOD1, NULL);
  if (palReadLine(LINE_BUTTON)) {
      test_execute((BaseSequentialStream *)&LPSIOD1, &rt_test_suite);
      test_execute((BaseSequentialStream *)&LPSIOD1, &oslib_test_suite);
    }*/


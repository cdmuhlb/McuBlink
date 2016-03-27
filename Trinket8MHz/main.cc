#include "GpioPin.h"
#include "Timer1Overflow.h"

#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdint.h>

constexpr uint8_t LedPin = 1;
volatile bool ledStatus = false;

int main() __attribute__ ((OS_main));
int main() {
  /* Setup */
  cli();

  /* Set up LED for blinking */
  GpioPin::setModeToOutput<LedPin>();

  /* Timer1 provides ~2Hz interrupts */
  Timer1Overflow::setup();

  sei();

  /* Loop */
  while (true) {
    // Sleep (sleep mode defaults to idle)
    sleep_mode();
  }
  // Never returns
}

/* Interrupt handler for Timer1 overflow */
ISR(TIMER1_OVF_vect) {
  if (ledStatus) GpioPin::setLow<LedPin>();
  else GpioPin::setHigh<LedPin>();
  ledStatus = !ledStatus;
}

#include "GpioPin.h"
#include "Timer1Overflow.h"

#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdint.h>

constexpr uint8_t LedPin = 13;
volatile bool ledStatus = false;

int main() __attribute__ ((OS_main));
int main() {
  /* Setup */
  cli();

  /* Reset USB controller */
  USBCON &= ~(1 << USBE);

  /* Set up LED for blinking */
  GpioPin::setModeToOutput<LedPin>();

  /* Timer1 provides ~0.5Hz interrupts */
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

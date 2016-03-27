#ifndef TIMER1OVERFLOW_H_
#define TIMER1OVERFLOW_H_

#include <avr/io.h>

namespace Timer1Overflow {
  inline void setup() {
    // Normal mode is default
    // 256 prescaler (0.5Hz in Normal mode)
    TCCR1B |= (1<<CS12);
    // Enable overflow interrupt
    TIMSK1 |= (1<<TOIE1);
  }
}

#endif  // TIMER1OVERFLOW_H_

#ifndef TIMER1OVERFLOW_H_
#define TIMER1OVERFLOW_H_

#include <avr/io.h>

namespace Timer1Overflow {
  inline void setup() {
    // Normal mode is default
    // 16384 prescaler (2Hz in Normal mode)
    TCCR1 |= (1<<CS10) | (1<<CS11) | (1<<CS12) | (1<<CS13);
    // Enable overflow interrupt
    TIMSK |= (1<<TOIE1);
  }
}

#endif  // TIMER1OVERFLOW_H_

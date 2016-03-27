#ifndef GPIOPIN_H_
#define GPIOPIN_H_

#include <avr/io.h>
#include <stdint.h>

namespace {
  /* Adapted from Wiring and modified for Feather */
  template<uint8_t pin>
  constexpr volatile uint8_t* digitalPinToPortReg() {
    static_assert((pin <= 3) || (pin >= 5 && pin <= 6) || (pin >= 9 && pin <= 13),
        "Illegal digital pin number");
    return (pin <= 3 || pin == 6 || pin == 12) ? &PORTD : ((pin >= 9 && pin <= 11) ? &PORTB : &PORTC);
  }

  template<uint8_t pin>
  constexpr volatile uint8_t* digitalPinToModeReg() {
    static_assert((pin <= 3) || (pin >= 5 && pin <= 6) || (pin >= 9 && pin <= 13),
        "Illegal digital pin number");
    return (pin <= 3 || pin == 6 || pin == 12) ? &DDRD : ((pin >= 9 && pin <= 11) ? &DDRB : &DDRC);
  }

  template<uint8_t pin>
  constexpr volatile uint8_t* digitalPinToInputReg() {
    static_assert((pin <= 3) || (pin >= 5 && pin <= 6) || (pin >= 9 && pin <= 13),
        "Illegal digital pin number");
    return (pin <= 3 || pin == 6 || pin == 12) ? &PIND : ((pin >= 9 && pin <= 11) ? &PINB : &PINC);
  }

  template<uint8_t pin>
  constexpr uint8_t digitalPinToBit() {
    static_assert((pin <= 3) || (pin >= 5 && pin <= 6) || (pin >= 9 && pin <= 13),
        "Illegal digital pin number");
    return (pin <= 1) ? (pin + 2) : ((pin <= 3) ? (3 - pin) : ((pin <= 6) ? (pin + 1) : ((pin <= 10) ? (pin - 4) : (pin - 6))));
  }
}

namespace GpioPin {
  template<uint8_t pin>
  static inline void setModeToOutput() {
    *(digitalPinToModeReg<pin>()) |= (1<<digitalPinToBit<pin>());
  }

  template<uint8_t pin>
  static inline void setModeToInput() {
    *(digitalPinToModeReg<pin>()) &= ~(1<<digitalPinToBit<pin>());
  }

  template<uint8_t pin>
  static inline void setHigh() {
    *(digitalPinToPortReg<pin>()) |= (1<<digitalPinToBit<pin>());
  }

  template<uint8_t pin>
  static inline void setLow() {
    *(digitalPinToPortReg<pin>()) &= ~(1<<digitalPinToBit<pin>());
  }

  template<uint8_t pin>
  static inline bool read() {
    return *(digitalPinToInputReg<pin>()) & (1<<digitalPinToBit<pin>());
  }
}

#endif  // GPIOPIN_H_

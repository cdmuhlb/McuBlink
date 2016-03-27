#ifndef GPIOPIN_H_
#define GPIOPIN_H_

#include <avr/io.h>
#include <stdint.h>

namespace {
  /* Adapted from Wiring */
  template<uint8_t pin>
  constexpr volatile uint8_t* digitalPinToPortReg() {
    static_assert(pin <= 19, "Illegal digital pin number");
    return (pin <= 7) ? &PORTD : ((pin <= 13) ? &PORTB : &PORTC);
  }

  template<uint8_t pin>
  constexpr volatile uint8_t* digitalPinToModeReg() {
    static_assert(pin <= 19, "Illegal digital pin number");
    return (pin <= 7) ? &DDRD : ((pin <= 13) ? &DDRB : &DDRC);
  }

  template<uint8_t pin>
  constexpr volatile uint8_t* digitalPinToInputReg() {
    static_assert(pin <= 19, "Illegal digital pin number");
    return (pin <= 7) ? &PIND : ((pin <= 13) ? &PINB : &PINC);
  }

  template<uint8_t pin>
  constexpr uint8_t digitalPinToBit() {
    static_assert(pin <= 19, "Illegal digital pin number");
    return (pin <= 7) ? pin : ((pin <= 13) ? (pin - 8) : (pin - 14));
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

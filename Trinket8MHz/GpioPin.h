#ifndef GPIOPIN_H_
#define GPIOPIN_H_

#include <avr/io.h>
#include <stdint.h>

namespace {
  /* Adapted from Wiring */
  template<uint8_t pin>
  constexpr volatile uint8_t* digitalPinToPortReg() {
    static_assert(pin <= 4, "Illegal digital pin number");
    return &PORTB;
  }

  template<uint8_t pin>
  constexpr volatile uint8_t* digitalPinToModeReg() {
    static_assert(pin <= 4, "Illegal digital pin number");
    return &DDRB;
  }

  template<uint8_t pin>
  constexpr volatile uint8_t* digitalPinToInputReg() {
    static_assert(pin <= 4, "Illegal digital pin number");
    return &PINB;
  }

  template<uint8_t pin>
  constexpr uint8_t digitalPinToBit() {
    static_assert(pin <= 4, "Illegal digital pin number");
    return pin;
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

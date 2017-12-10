/// @file led.cpp

#include "led.h"


void Led::begin(uint8_t pin){
  _pin = pin;
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
  _pattern = 
}


/// @file button.cpp
#include "button.h"

void Button::begin(int pin, uint32_t now){
  _pin = pin;
  pinMode(_pin, INPUT_PULLUP);
  _stat = digitalRead(_pin);
  _notified = false;
  _msStatChanged = now;
}

bool Button::update(uint32_t now){
  uint8_t lastStat = _stat;
  _stat = digitalRead(_pin);
  if (_stat != lastStat){
    _notified = false;
    _msStatChanged = now;
    return false;
  }
  if (_notified){
    return false;
  }
  uint32_t span = now - _msStatChanged;
  if (span < SPAN_DEBOUNCE){
    return false;
  }
  _notified = true;
  return (_stat == LOW);
}


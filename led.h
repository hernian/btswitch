/// @file led.h
#ifndef LED_H
#define LED_H

#include <Arduino.h>

enum LedBlinkPattern : uint8_t {
  OFF,
  ON,
  DASH_DASH_DASH_DASH,
  DOT_DOT_DOT_DOT,
  DASH_DOT_DASH_DOT
};

class Led {
  public:
    void  begin(uint8_t pin);
    void  blink(LedBlinkPattern pattern);
    void  update(uint32_t now);
  private:
    uint8_t         _pin;
    const uint8_t*  _pattern;
    uint8_t         _count;
    uint8_t         _index;
    uint32_t        _msLastUpdate;
};


#endif // LED_H


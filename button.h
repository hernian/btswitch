// @file button.h
#ifndef BUTTON_H
#define BUTTON_H

class Button {
  public:
    void  begin(uint8_t pin, uint32_t now);
    bool  update(uint32_t now);

  private:
    uint8_t   _pin;
    uint8_t   _stat;
    bool      _notified;
    uint32_t  _msStatChanged;
};


#endif // BUTTON_H


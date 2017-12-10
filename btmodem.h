/// @file btmodem.h
#ifndef BTMODEM_H
#define BTMODEM_H

class Stream;

class BtModem {
  public:
    void  begin(uint8_t pinReset, Stream* serial, uint32_t now);
    void  update(uint32_t now);

  private:
    uint8_t   _pinReset;
    Stream*   _serial;
};


#endif // BTMODEM_H


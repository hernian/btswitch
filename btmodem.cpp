/// @file btmodem.cpp

#include "btmodem.h"

void BtModem::begin(uint8_t pinReset, Stream* serial, uint32_t now){
  _pinReset = pinReset;
  pinMode(_pinMode, OUTPUT);
  digitalWrite(_pinMode, HIGH);
  _serial = serial;
  _callback = NULL;
  _lenBuf = 0;
  _seqReset = SEQ_RESET_NONE;
  _msSeqReset = 0;
}


void BtModem::update(uint32_t now){
  while (_serial->available() > 0){
    int c = _serial->read();
    if (_lenBuf < LEN_BUF){
      if (c != '\r'){
        _buf[_lenBuf++] = static_cast<uint8_t>(c);
      }
      else {
        _buf[_lenBuf] = '\0';
        if (_callback != NULL){
          Callback callback = _callback;
          _callback = NULL;
          (this->*callback)(_buf);
          _lenBuf = 0;
        }
      }
    }
  }
  updateReset();
}


void BtModem::reset(){
  _seqReset = SEQ_RESET_START;
  digitalWrite(_pinReset, LOW);
}

void BtModem::updateReset(){
  if (_seqReset == SEQ_RESET_NONE){
    return;
  }
  switch (_seqReset){
    case SEQ_RESET_START:
      break;    
    case SEQ_RESET_HIGH1:
      break;
    case SEQ_RESET_LOW2:
      break;
    case SEQ_RESET_HIGH2:
      break;
    case SEQ_RESET_CONFIG:
      break;
    case SEQ_RESET_END:
      _seqReset = SEQ_RESET_NONE;
      return;
  }
  ++_seqReset;
}






#include "button.h"
#include "btmodem.h"

const uint8_t   PIN_LED_ONBOARD   = 13;
const uint8_t   PIN_MODEM_RESET   = 3;
const uint8_t   PIN_BUTTON_RESET  = 4;

const uint32_t  BAUDRATE_BDMODEM  = 115200;
const uint32_t  MS_SPAN_BLINK_LED = 500;

Button buttonReset;
BtModem btModem;


///////////////////////////////////////////////////////
// LED

uint32_t msLastLED;
uint8_t statLED;

void initLED(){
    msLastLED = millis();
    statLED = LOW;
    pinMode(PIN_LED, OUTPUT);
    digitalWrite(PIN_LED, statLED);
}

void taskLED(){
    uint32_t now = millis();
    uint32_t span = now - msLastLED;
    if (span < SPAN_BLINK_LED){
        return;
    }
    msLastLED = now;
    statLED = (statLED == LOW) ? HIGH: LOW;
    digitalWrite(PIN_LED, statLED);
}

// LED
///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
// Serial

void initSerial(){
    Serial.begin(115200);
    Serial.print(F("Hello"));

    Serial1.begin(115200);
    delay(1000);
    Serial1.write("$$$");
}

void taskSerial()
{
    while (Serial.available() > 0){
        int c = Serial.read();
        if (c == '\t'){
            c = '\0';
        }
        Serial.write(c);
        Serial1.write(c);
    }
    while (Serial1.available() > 0){
        int c = Serial1.read();
        Serial.write(c);
    }
}

// Serial
///////////////////////////////////////////////////////

void setup() {
    delay(3000);
    pinMode(PIN_LED, OUTPUT);
    initLED();
    initSerial();
    uint32_t now = millis();
    buttonReset.begin(PIN_BUTTON_RESET, now);
    Serial1.begin(BAUDRATE_BTMODEM);
    btModem.begin(PIN_BTMODEM_RESET, &Serial1);
}

void loop() {
    taskLED();
    taskSerial();
    uint32_t now = millis();
    bool isReset = buttonReset.update(now);
    if (isReset){
      btModem.reset();
    }
    btModem.update(now);
}


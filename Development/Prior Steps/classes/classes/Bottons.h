#include <Arduino.h>

#include "Board.h"
#include "Person.h"
#include "Leds.h"


class Button {
private:
    byte pin;
    byte state;
    byte lastReading;
    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay = 50;
public:
    Button() {};
    Button(byte pin) {};
    void init() {};
    void update() {};
    byte getState() {};
    bool isPressed() {};
};


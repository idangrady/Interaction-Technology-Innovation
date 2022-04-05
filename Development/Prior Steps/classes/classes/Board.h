
#include <Arduino.h>

#include "Person.h"
#include "Leds.h"
#include"Bottons.h"

class Board {
private:
    byte pin;
    byte state;

    Person ppl[5];
    Led leds[9];
    Button bottons[10];

    int a = 0;
    int numPerson;
    int numLed;
    int numBottons;


public:
    //Person(a);
    Board() {};
    Board(byte pin, Person* p, int maxP, Led* led, int numLed, Button* btns, int numBottons) {};
    void turnOffLed() {};
    void lightOneAtTheTime() {};
};
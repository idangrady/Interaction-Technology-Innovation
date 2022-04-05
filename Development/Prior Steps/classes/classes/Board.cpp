#include <Arduino.h>

#include "Board.h"
#include "Person.h"
#include "Bottons.h"
#include "Leds.h"

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
    Board() {};
    Board(byte pin, Person* p, int maxP, Led* led, int numLed, Button* btns, int numBottons)
    {
        this->pin = pin;

        this->numPerson = maxP;
        this->numBottons = numBottons;
        this->numLed = numLed;



        for (int i = 0; i < maxP; i++) {
            ppl[i] = p[i];
        }

        for (int j = 0; j < numLed; j++) {
            leds[j] = led[j];
        }

        for (int n = 0; n < numBottons; n++) {
            bottons[n] = btns[n];
        }

        turnOffLed();

    }

    void turnOffLed() {
        for (int i = 0; i < numLed; i++) {
            leds[i].off();
        }
    }
    void lightOneAtTheTime() {
        for (int i = 0; i < numLed; i++) {
            leds[i].on();
            delay(2000);
        }
    }
};
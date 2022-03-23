#include <Arduino.h>


#define LED_1_PIN 8
#define LED_2_PIN 9
#define LED_3_PIN 11
#define LED_4_PIN 12

#define BUTTON_PIN1 22
#define BUTTON_PIN2 24
#define BUTTON_PIN3 26

#define VALUE_PERSON_1 3
#define VALUE_PERSON_2 257


class Led {
private:
    byte pin;
public:
    Led() {};
    Led(byte pin) {
        this->pin = pin;
        init();
    }
    void init() {
        pinMode(pin, OUTPUT);
        off();
    }
    void on() {
        digitalWrite(pin, HIGH);
    }
    void off() {
        digitalWrite(pin, LOW);
    }
};


class Button {
private:
    byte pin;
    byte state;
    byte lastReading;
    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay = 50;
public:
    Button() {};
    Button(byte pin) {
        this->pin = pin;
        lastReading = HIGH;
        init();
    }
    void init() {
        pinMode(pin, INPUT_PULLUP);
        update();
    }
    void update() {
        byte newReading = digitalRead(pin);

        if (newReading != lastReading) {
            lastDebounceTime = millis();
        }
        if (millis() - lastDebounceTime > debounceDelay) {
            // Update the 'state' attribute only if debounce is checked
            state = newReading;
        }
        lastReading = newReading;
    }
    byte getState() {
        update();
        return state;
    }
    bool isPressed() {
        return (getState() == LOW);
    }
};


class Person
{
private:
    byte Morning;
    byte Noon;
    byte Evening;

    int availabllity;
    int sceduale;
    bool assign;
    byte myarray[3];

    byte morningDesplay[10];
    byte NoonDisplay[10];
    byte EveningDisplay[10];

    byte listLight[20];


public:
    Person() {};
    Person(int avai)
    {

        this->availabllity = avai;
        this->sceduale = 0;
        this->Morning = 0;
        this->Noon = 0;
        this->Evening = 0;

        this->assign = true;
        init();
    }

    void init()
    {
        for (int i = 0; i < 10; i++) {
            if (i < 3) { myarray[i] = 0; }
            this->morningDesplay[i] = 0;
            this->NoonDisplay[i] = 0;
            this->EveningDisplay[i] = 0;
        }

        updateBytes();
    }
    void update()
    {
        //Serial.println(" update");

        this->Morning = myarray[0];
        this->Noon = myarray[1];
        this->Evening = myarray[2];
    }
    void updateBytes() {
        //Serial.println(" updateBytes");

        this->myarray[0] = availabllity & 0xFF;
        this->myarray[1] = (availabllity >> 8) & 0xFF;
        this->myarray[2] = (availabllity >> 16) & 0xFF;

        update();
    }
    int getavailability() {
        return availabllity;
    }
    void pringAvailability() {
        Serial.println(availabllity);
    }
    void printBits() {
        //Serial.println("Bits: ");
        for (int i = 0; i < 3; i++) {
            Serial.print(myarray[i]);
            delay(200);
        }
    }
    void getArray(byte(&myarray_)[3]) {
        for (int i = 0; i < 3; i++) {
            *(myarray_ + i) = myarray[i];
        }
    }

    void displayAvailable() {

        byte num_morning = 0;
        byte num_non = 0;
        byte num_eve = 0;

        for (byte i = 0; i < 3; i++)
        {
            String time = "";
            int time_pin = -1;
            int time_int;

            switch (i) {
            case 0:
                time_pin = 0;
                time = "Morning";
                break;
            case 1:
                time_pin = 1;
                time = "Noon";
                break;
            case 2:
                time_pin = 2;
                time = "Evening";
            }
            byte state = myarray[i];

            auto size_ = sizeof(state);
            for (int j = 0; j < 8; j++)
            {
                int time_Day = 0;
                int number = 1 << j;
                if ((state & (1 << j))) {
                    switch (j) {
                    case 0:
                        Serial.print("Monday ");
                        Serial.println(time);
                        Serial.println(time_Day);
                        time_Day = time_pin + 8;
                        listLight[j + i] = time_Day;
                        break;
                    case 1:
                        Serial.print(time_Day);
                        Serial.print("Tuesday ");
                        Serial.println(time);
                        time_Day = time_pin + 11;
                        listLight[j + i] = time_Day;
                        break;
                    case 2:
                        Serial.print("Wednesday ");
                        Serial.println(time);
                        break;
                    case 3:
                        Serial.print("Thursday ");
                        Serial.println(time);
                        break;
                    case 4:
                        Serial.print("Friday ");
                        Serial.println(time);
                        break;
                    case 5:
                        Serial.print("Saturday ");
                        Serial.println(time);
                        break;
                    case 6:
                        Serial.print("Sunday ");
                        Serial.println(time);
                        break;
                    }
                }
                else
                {
                    //cout << "0";
                }
            }
        }

    };

};



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


// initlizer Classes
Led led1(LED_1_PIN);
Led led2(LED_2_PIN);
Led led3(LED_3_PIN);
Led led4(LED_4_PIN);


Button button1(BUTTON_PIN1);
Button button2(BUTTON_PIN2);
Button button3(BUTTON_PIN3);

//
Person person_1(VALUE_PERSON_1);
Person person_2(VALUE_PERSON_2);


Button arrauButtons[3] = { button1 ,button2 ,button3 };
Led arrayLED[4] = { led1, led2, led3, led4 };
Person ppl[1] = { person_1 };

byte a = 0;

Board b(a, ppl, 1, arrayLED, 4, arrauButtons, 3);



void setup() {

    Serial.begin(9600);
}
void loop() {
    Serial.println("Loop");


    if (button1.isPressed()) {
        Serial.println("button1");

        led1.on();
        led2.off();
        led3.on();
        led4.off();
        person_1.displayAvailable();
    }
    else if (button2.isPressed()) {
        Serial.println("button2");
        led1.off();
        led2.off();
        led3.on();
        led4.on();
        person_2.displayAvailable();
    }
    else if (button3.isPressed()) {
        Serial.println("button3");
        //arrauPPL[2].displayAvailable();
        led1.on();
        led2.off();
        led3.on();
        led4.off();
    }
    //delay(2000);
    for (int i = 0; i < 4; i++) {
        //arrayLED[i].off();
    }



}


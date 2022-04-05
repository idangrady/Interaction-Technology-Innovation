#include "Person.h"
#include <Arduino.h>

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
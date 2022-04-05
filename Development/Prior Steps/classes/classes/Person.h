#pragma once

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
    Person(int avai) {};
    void init() {};
    void update() {};
    void updateBytes() {};
    int getavailability() {};
    void pringAvailability() {};
    void printBits() {};

    void getArray(byte(&myarray_)[3]) {};

    void displayAvailable() {};

};

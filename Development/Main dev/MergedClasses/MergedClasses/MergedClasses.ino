#include <Arduino.h>


// LEDS Pins
//MondayMorning
#define RGBMondayMorningp1 22
#define RGBMondayMorningp2 23
#define RGBMondayMorningboth 24
// Monday Noon
#define RGBMondayNoonp1 25
#define RGBMondayNoonp2 26
#define RGBMondayNoonboth 27
//Monday Evening
#define RGBMondayEveningp1 28
#define RGBMondayEveningp2 29
#define RGBMondayEveningboth 30
//
//
//TuesdayMorning
#define RGBTuesdayMorningp1 31
#define RGBTuesdayMorningp2 32
#define RGBTuesdayMorningboth 33
// Tuesday Noon
#define RGBTuesdayNoonp1 34
#define RGBTuesdayNoonp2 35
#define RGBTuesdayNoonboth 36
//Tuesday Evening
#define RGBTuesdayEveningp1 37
#define RGBTuesdayEveningp2 38
#define RGBTuesdayEveningboth 39

// Wednesday

//Wednesday Morning
#define RGBWednesdayMorningp1 40//
#define RGBWednesdayMorningp2 41
#define RGBWednesdayMorningboth 42
// Wednesday Noon
#define RGBWednesdayNoonp1 43
#define RGBWednesdayNoonp2 44
#define RGBWednesdayNoonboth 45
//Wednesday Evening
#define RGBWednesdayEveningp1 46
#define RGBWednesdayEveningp2 47
#define RGBWednesdayEveningboth 48


#define RGBTuesdayp1 25
#define RGBTuesdayp2 26
#define RGBTuesdayboth 27

// pin value -> initilize manually (Either we create a logic for pin design ()
#define RGBWednsdayMorning 28
#define RGBWednsdayNoon 29
#define RGBWednsdayEvening 30

// define tiem button -> each time gets a button with initlizer of its correponding int. 

// monday 
#define BUTTON_PINMondayMorning 2
#define MondayMorningInt 1 // will add a function that initilize all these value automatically. Yet for now , I write it manually

#define BUTTON_PINMondayNoon 3
#define MondaynoongInt 256 // will add a function that initilize all these value automatically. Yet for now , I write it manually

#define BUTTON_PINMondayEvening 4
#define MondayeveInt 65536 // will add a function that initilize all these value automatically. Yet for now , I write it manually


//tuesday
#define BUTTON_PINTuesdayMorning 5
#define TuesdayMorningInt 2

#define BUTTON_PINTuesdayNoon 6
#define TuesdayNoongInt 512

#define BUTTON_PINTuesdayEve 7
#define TuesdayEveInt 131072

// wednsday
#define BUTTON_PINWednesdayMorning 8
#define WednesdayMorningInt 4

#define BUTTON_PINWednesdayNoon 9
#define WednesdayNoongInt 1024

#define BUTTON_PINWednesdayEve 10
#define WednesdayEveInt 262144



#define PINPersonOne 52
#define PinPersonTwo  12

#define VALUE_PERSON_1 0
#define VALUE_PERSON_2 1

#define DAYINWEEK 3
#define NUMBitTotal 24

bool but1 = false;;

bool debug = false;


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


class RGBLed {
private:
    byte pinbegin;
    byte pin[9];

    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay = 2000;

    unsigned long initSequence = 0;
public:
    RGBLed() {};
    RGBLed(byte *pinList, byte begin) {
        this->pinbegin = begin;
        for (int i = 0; i < 9; i++) {
            this->pin[i] = pinList[i];
        }
        
        init();
    }
    void init() {
        for (int i = 0; i < 9; i++) {
            pinMode(pin[i], OUTPUT);
        }
        
        off();
    }
    void on(int i) {
        if(debug){ Serial.print("Turn on: Pin: "); Serial.println(i); }
        digitalWrite(pin[i], HIGH);
        //delay(500);
    }
    void onFull(int idx) {
        if (debug) { Serial.print("Turn on: Pin: "); Serial.println(idx); }
        digitalWrite(pin[idx], HIGH);
        //delay(500);
    }
    void onBegin() { digitalWrite(pinbegin, HIGH);}
    void turnPinOff(int i){ digitalWrite(pin[i], HIGH); }
    void off() {
        for (int i = 0; i < sizeof(pin) / sizeof(pin[0]); i++) {
            digitalWrite(pin[i], LOW);
        }
    }
    void printTime() {
        for (int i = 0; i < 9; ++i) { Serial.println(pin[i]); }
    }
    //void fullOff() { for (int i = 0; i < sizeof(pin) / sizeof(pin[0]); ++i) {} }

};

class Button {
private:
    byte pin;
    byte state;
    byte lastReading;
    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay = 150;

    unsigned long LastBountDelay = 0;
    unsigned long presseddelay = 1000;
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
        update();
        return (getState() == LOW);
    }
    bool isPressedWithTime() {
        //update();
        if (LastBountDelay + presseddelay < millis()) { LastBountDelay = millis(); return true; }
        else { return false; }
        //return (getState() == LOW);
    }

    byte getPinNum() {
        return pin;
    }
};

// derived class Button -> for time button
class TimeButton : public Button {
public:
    int valuePerTime;
    String timeName;
    bool activated;

    long lastupdate;
    int durationToUpdate = 2000;


    TimeButton() {};
    TimeButton(byte pin, int val, String nameTime):Button(pin) {
        this->valuePerTime = val;
        this->activated = true;
        this->timeName = nameTime;
};

    void printTime(bool er) {
        if (er) {
            Serial.println("Mistake");
        }
        
        if (!er) {
            Serial.print("Bottun ");
            Serial.print(getPinNum());
            Serial.print(" .Int: ");
            Serial.println(valuePerTime);
        }
    }
    bool isActivated() {
        return(activated);
    }
    int getButtonVal() {
        if (activated) {  return valuePerTime; } //activated = false;
        else { return -valuePerTime; } // activated = true;  
    }
    bool delayUpdate() 
    {
        if (debug) {
            Serial.print("millis() "); Serial.println(millis());
            Serial.print("lastupdate() "); Serial.println(lastupdate);
            Serial.print("millis() - lastupdate() ");  Serial.println(millis() - lastupdate);
        }
        if (millis() - lastupdate > durationToUpdate) { return true; }
        else { return false; };
    }
    // activate
    void activate() {activated = true;}
    void deactivate() { activated = false; }
    void flipActived() 
    {
        if (isActivated()) { activated = false; }
        else { activated = true; }
    }
    void updateTime() { 
        this->lastupdate = millis(); 
        //if (activated) { activated = false; } 
        //else { activated = true; } 
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
        for (int i = 0; i < 10; ++i) {
            if (i < 3) { myarray[i] = 0; }
            this->morningDesplay[i] = 0;
            this->NoonDisplay[i] = 0;
            this->EveningDisplay[i] = 0;
        }

        updateBytes();
    }
    void update()
    {
        if (debug) { Serial.println(" update"); }

        this->Morning = myarray[0];
        this->Noon = myarray[1];
        this->Evening = myarray[2];
    }
    void updateBytes() {
        if (debug) { Serial.println(" updateBytes"); }

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
        if (debug) { Serial.println("Bits: "); }
        for (int i = 0; i < 3; ++i) {
            Serial.print(myarray[i]);
            //delay(200);
        }
    }
    void getArray(byte(&myarray_)[3]) {
        for (int i = 0; i < 3; ++i) {
            *(myarray_ + i) = myarray[i];
        }
    }
    void updateVal(int v) 
    {
        this->availabllity = this->availabllity + v;
    }
    void displayAvailable() {

        byte num_morning = 0;
        byte num_non = 0;
        byte num_eve = 0;

        int totalAccomulate = -1;
        for (byte i = 0; i < 3; ++i)
        {
            String time = "";
            int time_pin = -1;
            int time_int;

            int accomulate = 0;

            switch (i) {
            case 0:
                time_pin = 0;
                time = "Morning";
                accomulate = 0;

                break;
            case 1:
                time_pin = 1;
                time = "Noon";
                accomulate = 256;
                break;
            case 2:
                time_pin = 2;
                time = "Evening";
                accomulate = 65536;
            }
            byte state = myarray[i];

            auto size_ = sizeof(state);
            for (int j = 0; j < 8; ++j)
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
                        accomulate = accomulate + 0;
                        break;
                    case 1:
                        Serial.print(time_Day);
                        Serial.print("Tuesday ");
                        Serial.println(time);
                        time_Day = time_pin + 11;
                        listLight[j + i] = time_Day;
                        accomulate = accomulate + 1;

                        break;
                    case 2:
                        Serial.print("Wednesday ");
                        Serial.println(time);
                        accomulate = accomulate + 2;

                        break;
                    case 3:
                        Serial.print("Thursday ");
                        Serial.println(time);
                        accomulate = accomulate + 3;

                        break;
                    case 4:
                        Serial.print("Friday ");
                        Serial.println(time);
                        accomulate = accomulate + 4;

                        break;
                    case 5:
                        Serial.print("Saturday ");
                        Serial.println(time);
                        accomulate = accomulate + 5;

                        break;
                    case 6:
                        Serial.print("Sunday ");
                        Serial.println(time);
                        accomulate = accomulate + 6;
                        break;
                    }
                }
                else
                {
                    //cout << "0";
                }
                totalAccomulate = totalAccomulate + accomulate;
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
    Button Buttons[10];
    RGBLed RHBLeds[9];

    TimeButton DaysDottons[10];


    int a = 0;
    int numPerson;
    int numLed;
    int numButtons;
    int numDaysButtons;
    int numRGVLed;

    unsigned long lastPressed = 0; 
    unsigned long debounceDelay = 1000;

    bool anyPressed;

public:
    //Person(a);
    Board() {};
    Board(byte pin, Person* p, int maxP, Led* led, int numLed, Button* btns, int numButtons, TimeButton* daysButtons, int numDaysButtons, RGBLed* rgbLedList, int rgbLedListNum)
    {
        this->pin = pin;

        this->numPerson = maxP;
        this->numButtons = numButtons;
        this->numLed = numLed;
        this->numDaysButtons = numDaysButtons;
        this->numRGVLed = rgbLedListNum;


        for (int i = 0; i < maxP; ++i) {
            ppl[i] = p[i];
        }

        for (int j = 0; j < numLed; ++j) {
            leds[j] = led[j];
        }

        for (int n = 0; n < numButtons; ++n) {
            Buttons[n] = btns[n];
        }
        for (int i = 0; i < numDaysButtons; ++i) {
            DaysDottons[i] = daysButtons[i];
        }
        for (int i = 0; i < rgbLedListNum; ++i) 
        {
            RHBLeds[i] = rgbLedList[i];
        }

        turnOffLed();
    }
    void printTimeButtons() {
        for (int i = 0; i < numRGVLed; ++i)
        {
            RHBLeds[i].printTime();
        }
    }
    void turnOffLed() {

        for (int i = 0; i < numLed; ++i) {
            leds[i].off();
        }
        for (int i = 0; i < numRGVLed; ++i) 
        {
            RHBLeds[i].off();
        }
        
    }

    void initilizeTimeButton() {
        for (int i = 0; i < numDaysButtons; ++i) {
            if (DaysDottons[i].valuePerTime<0) {
                if(debug){DaysDottons[i].printTime(true); }
                
            }
        }
    }

    void lightOneAtTheTime() {
        for (int i = 0; i < numLed; ++i) {
            leds[i].on();
            delay(2000);
        }
    }
    void rgbLightInit()
    {
        for (int i = 0; i < numRGVLed; ++i) {
            for (int j = 0; j < 9; ++j) {
                RHBLeds[i].on(j);
                delay(150);
                RHBLeds[i].turnPinOff(j);

            }
    }
    }

    void detectTimePressed() {
        for (int i = 0; i < numDaysButtons; ++i) {

            if (DaysDottons[i].isPressed()) { //&& (but1 == false)
                
                if (DaysDottons[i].isPressedWithTime()) //  DaysDottons[i].delayUpdate()
                {
                    Serial.println("Pressed To update Value"); Serial.println(DaysDottons[i].valuePerTime);
                    if(debug){
                        Serial.println("Pressed To update Value"); 
                    }
                    // check wheether this button was pressen recently. if there is a good sequence of time -> update the params
                    // needs to have a break of 100 mil between each update
                    if (!DaysDottons[i].isActivated() ) {
                        int getval = DaysDottons[i].getButtonVal();
                        ppl[0].updateVal(getval); // the person "owner" of the board always at pos 0 -> at the end this will be separate
                        
                        if (debug) { Serial.println(ppl[0].getavailability());Serial.print("After update Val is: "); Serial.println(DaysDottons[i].getButtonVal());
                        }
                        DaysDottons[i].updateTime();
                    }

                    else{
                        int getval = DaysDottons[i].getButtonVal();
                        if(debug){ Serial.print("Else: ");  Serial.println(getval); }
                        
                        ppl[0].updateVal(getval); // the person "owner" of the board always at pos 0 -> at the end this will be separate
                        DaysDottons[i].updateTime();
                                                                         //return  int(-DaysDottons[i].getButtonVal()); 
                    /*    break;*/
                    }
                    but1 = true;
                    DaysDottons[i].flipActived();
                }
                else 
                {
                    if(debug){
                        Serial.println("Delay Detected : Button - "); Serial.print(i);
                    }
                }
            }
        }
       
    }
    int checkoverLab( int personone,int person2, int overlap, int i)
    {
        if (debug) {
        Serial.println(personone);
        Serial.println(person2);
        Serial.println(overlap);
        Serial.println(1 << i);
        Serial.println(personone & (1 << i));
        delay(1000);
        }

        if (personone & (1 << i))
        {   
            if(debug){
                Serial.print("Got personone right ");  Serial.println(1 << i);
            }
        return 0;
        }
        else if (person2 & (1 << i))
        {
            if (debug) {
                Serial.print("Got person2 right "); Serial.println(1 << i);
            }
            return 1;
        }
        else if (overlap & (1 << i))
        {
            if (debug) {
                Serial.println("Overlap");
            }
            return 2;
        }

        return -1;
    }
    int get_idx (int n)
    {
        return (int(n)/int(8))*3;
    }
    void displayAvailability(int personone, int person2, int overlap)
    {   
        for (int n = 0; n < 24; n++) {
            //// check which RGB should light based on the bits
            int result = checkoverLab(personone, person2, overlap, n);
            int idx = get_idx(n) ;
            if (debug) {
                Serial.print("Result: ");
                Serial.println(result);
                Serial.print("idx: ");
                Serial.println(idx);
                delay(1000);
            }
            //Serial.print("result: "); Serial.print(result); Serial.print("n: "); Serial.println(n);
            if (result >-1) 
            {
                if (debug) {
                    Serial.print("Day"); Serial.println(n);
                }
                if (n <= 7) {
                    // morening
                    // index = i
                    if (debug) {
                        Serial.print("result: "); Serial.println(result); Serial.print("n+result: "); Serial.println(n + result);
                    }

                    //Serial.print("Amount buttons: : "); Serial.println(sizeof();

                    RHBLeds[n].on(result);
                    if(debug){
                        RHBLeds[n].printTime();
                    }
                    }

                else 
                {
                    int idx;
                    if (n <= 15) { idx = 1; }
                    else { idx = 2; }
                    //Serial.println("Else");
                    //RHBLeds[int(n % 8)].printTime();
                    //Serial.print("idx: "); Serial.println((idx)); 
                    // index = %idxPButton -> overlap -> third
                    RHBLeds[int(n % 8)].on(result+ idx *3); //int(n % 7)
                    /*RHBLeds[0].on(4); RHBLeds[0].on(5);*/
                    
                    //Serial.println()
                    //RHBLeds[0].printTime();
                    if (debug) {
                        Serial.print("RHBLeds "); Serial.println(n % 7);
                    }
                }
            }
            
        }
    }
    void updateLastPress() {
        this->lastPressed = millis();
        this->anyPressed = true;
    }
    void checkIntAvailabale(int person, int person2) {
        updateLastPress();
        // here should come update
        // update()

        // note: Person 1 is always the one pressing where preson 2 is the one the is pressed.
        int outInt;
        int personOneAvailableWithout;
        int personTwoAvailableWithout;

        for (int i = 0; i < numPerson; ++i) {
            if (i == 0) { outInt = ppl[i].getavailability(); }
            else {
                outInt = outInt & ppl[i].getavailability();
            }
        }   

        // display both -> num  = 2 for each value (the both color)
        personOneAvailableWithout = ppl[person].getavailability() ^ outInt;
        personTwoAvailableWithout = ppl[person2].getavailability() ^ outInt;
        //Serial.print("outInt: "); Serial.println(outInt);
        //Serial.print("personOneAvailableWithout: "); Serial.println(personOneAvailableWithout);
        //Serial.print("personTwoAvailableWithout: "); Serial.println(personTwoAvailableWithout);

        if (debug) {
            Serial.print("outInt: "); Serial.println(outInt);
            Serial.print("personOneAvailableWithout: "); Serial.println(personOneAvailableWithout);
            Serial.print("personTwoAvailableWithout: "); Serial.println(personTwoAvailableWithout);
        }
        displayAvailability(personOneAvailableWithout, personTwoAvailableWithout, outInt);

    }
    void checkLastPress() 
    {
        if (debug) { Serial.println(millis());  Serial.println(lastPressed); Serial.println(millis() - lastPressed); }

        if ((millis() - lastPressed > debounceDelay)) { //&& (anyPressed)
            // initlize all the RGBLED
            turnOffLed();
            anyPressed = false;
        }
    }
    void initSensorLightAtTheTime() 
    {

    }
};

class movementSensor
{
private:
    bool activated;
    byte inputPin;
    byte outputPin;

    long lastActivate=0;
    long trashHoldVal;

public:
    movementSensor();
    movementSensor(byte inputP, byte outputP, long tresh)
    {
        this->inputPin = inputP;
        this->outputPin = outputP;
        this->trashHoldVal = tresh;
        init();
    }
    void init()
    {
        pinMode(inputPin, INPUT);
        pinMode(outputPin, OUTPUT);
        update();
    }
    void update() 
    {
        int val = digitalRead(inputPin);
        if((val==HIGH) && (millis() - lastActivate >trashHoldVal))
        {
        // motion detected
            activated = true;
            lastActivate = millis();
        }
        else { activated = false; }
    }
    bool getState() 
    {
        update();
        // if motion detedted - > hence activated = true
        return activated;
        Serial.print("Activated= "); Serial.println(activated);
     }
    byte getInputPin() { return inputPin;}
    byte getOutputPin() { return outputPin;}
    void setTresholdVal(long t) { trashHoldVal = t; }
};


void createRGBLED(int numLED, short beginPin) {
    int num_LED = numLED / 3; // each LED has three time slot a day

    // time slots for initilization
    String nameDay[3] = { "Nonday", "Tuesday", "Wednsday" };
    String timeDay[3] = { "morning", "Noon", "Evening" };
    
    int timeNum[3] = { 0,1,2 };

    // Note: for the initilization, when creating the int it is simply 1>> x , where each button corresponds to a different specific int

    for (int i = beginPin; i < beginPin +3; ++i) {
        for (int j = 0; j < 3; ++j) {
            String name = nameDay[i] + " " + timeDay[j];
            TimeButton bu();
        }
    }

}


void createMorning(int numPeople)
{
    String nameDay[3] = { "Nonday", "Tuesday", "Wednsday" };
    String timeDay[3] = { "morning", "Noon", "Evening" };

    String dayNames[9] = {};

    byte begin = 22;
    for (int i = 0; i < 3; ++i) 
    {
        String nameCurrent = nameDay[0] + " " + timeDay[i];
        dayNames[i] = nameCurrent;
    }
    for (int j = 0; j < sizeof(dayNames)/ sizeof(dayNames[0]); ++j) {
        for (int i = 0; i < numPeople; ++i) 
        {
            //TimeButton t(begin; 1 << j; dayNames[j]);

            begin + begin + 1;
        }
        Serial.println(dayNames[j]);
    }
}

//RGBLed
byte monday[9] = { RGBMondayMorningp1 ,RGBMondayMorningp2,  RGBMondayMorningboth ,RGBMondayNoonp1 ,RGBMondayNoonp2,  RGBMondayNoonboth,RGBMondayEveningp1,RGBMondayEveningp2, RGBMondayEveningboth };
byte tuesday[9] = { RGBTuesdayMorningp1 ,RGBTuesdayMorningp2 ,RGBTuesdayMorningboth ,RGBTuesdayNoonp1 ,RGBTuesdayNoonp2 ,RGBTuesdayNoonboth ,RGBTuesdayEveningp1 ,RGBTuesdayEveningp2 ,RGBTuesdayEveningboth };
byte wednsday[9] = { RGBWednesdayMorningp1 ,RGBWednesdayMorningp2 ,RGBWednesdayMorningboth ,RGBWednesdayNoonp1 ,RGBWednesdayNoonp2 ,RGBWednesdayNoonboth ,RGBWednesdayEveningp1,RGBWednesdayEveningp2,RGBWednesdayEveningboth };



RGBLed rgbLedmonday(monday, RGBMondayMorningp1);
RGBLed rgbLedtueday(tuesday, RGBTuesdayMorningp1);
RGBLed rgbLedwednsday(wednsday, RGBWednesdayMorningp1);


Button buttonPerson1(PINPersonOne);
Button buttonPerson2(PinPersonTwo);

Button buttoninit(13);



// Time Button - > each Led would have its own value correponding to value it carries
// Monday Time Button
TimeButton buttonMondayMorning(BUTTON_PINMondayMorning,MondayMorningInt,"Monday Morning");
TimeButton buttonMondayNoon(BUTTON_PINMondayNoon, MondaynoongInt, "Monday Noon");
TimeButton buttonMondayEve(BUTTON_PINMondayEvening, MondayeveInt, "Monday eve");

// Tuesday Time Button
TimeButton buttonTuedayMorning(BUTTON_PINTuesdayMorning, TuesdayMorningInt, "Tueday Morning");
TimeButton buttonTuedayNoon(BUTTON_PINTuesdayNoon, TuesdayNoongInt, "Tueday Noon");
TimeButton buttonTuedayEve(BUTTON_PINTuesdayEve, TuesdayEveInt, "Tueday eve");

// Wednesday Time Button
TimeButton buttonWednesdayMorning(BUTTON_PINWednesdayMorning, WednesdayMorningInt, "Wednesday Morning");
TimeButton buttonWednesdayNoon(BUTTON_PINWednesdayNoon, WednesdayNoongInt, "Wednesday Noon");
TimeButton buttonWednesdayEve(BUTTON_PINWednesdayEve, WednesdayEveInt, "Wednesday eve");



// Init Perople
Person person_1(VALUE_PERSON_1);
Person person_2(VALUE_PERSON_2);

// List Per objects -> this will be fed to the Board object
Button arrauButtons[1] = { };
Led arrayLED[1] = { };


Person ppl[2] = { person_1 , person_2 };

RGBLed RgbLeds[3] = { rgbLedmonday ,rgbLedtueday ,rgbLedwednsday }; // ,rgbLedtuesday ,rgbLedwednsday

// time button
TimeButton daysButtons[9] = { buttonMondayMorning,buttonMondayNoon,buttonMondayEve, buttonTuedayMorning,buttonTuedayNoon, buttonTuedayEve,buttonWednesdayMorning ,buttonWednesdayNoon, buttonWednesdayEve }; // buttonMondayNoon

byte a = 0;

Board b(a, ppl, sizeof(ppl) / sizeof(ppl[0]), arrayLED, sizeof(arrayLED) / sizeof(arrayLED[0]), arrauButtons, sizeof(arrauButtons)/ sizeof(arrauButtons[0]), daysButtons, sizeof(daysButtons) / sizeof(daysButtons[0]), RgbLeds, sizeof(RgbLeds) / sizeof(RgbLeds[0])); // TODO: Transfer it to automatic len


void setup() {

    Serial.begin(9600);
}

bool hereSerial = true;
bool got = false;
long pressed = 0;
int i = 0;
void loop() {
    //if (i == 0) { createMorning(2); i = i + 1; }

    //Serial.println("Loop");
    b.detectTimePressed();
    if (buttonPerson1.isPressed()) {
    b.checkIntAvailabale(0, 1);
    }
    if (buttonPerson2.isPressed()) {
        b.checkIntAvailabale(1, 0);
    }

    if (buttoninit.isPressed()) {
        b.rgbLightInit();
    }
    b.checkLastPress();

    
    // check if data is available
    if (!hereSerial) {
        if ((Serial.available() > 0)) {
            // read the incoming byte:
            int incomingByte = Serial.read();
            pressed = millis();
            //prints the received data
            got = true;
            Serial.print((char)incomingByte);
        }
    }
    


    //if (millis() - pressed > 2000) { got = false;}
}



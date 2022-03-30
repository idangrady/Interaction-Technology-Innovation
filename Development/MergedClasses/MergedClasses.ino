#include <Arduino.h>


#define RGBMondayp1 2
#define RGBMondayp2 3
#define RGBMondayboth 4


#define RGBTuesdayp1 5
#define RGBTuesdayp2 5
#define RGBTuesdayboth 7

// pin value -> initilize manually (Either we create a logic for pin design ()
#define RGBWednsdayMorning 39
#define RGBWednsdayNoon 41
#define RGBWednsdayEvening 43

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


#define PINPersonOne 52
#define PinPersonTwo  12

#define VALUE_PERSON_1 0
#define VALUE_PERSON_2 0

#define DAYINWEEK 3
#define NUMBitTotal 24

bool but1 = false;;


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
    byte pin[3];

    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay = 2000;
public:
    RGBLed() {};
    RGBLed(byte *pinList, byte begin) {
        this->pinbegin = begin;
        for (int i = 0; i < 3; i++) {
            this->pin[i] = pinList[i];
        }
        
        init();
    }
    void init() {
        for (int i = 0; i < 3; i++) {
            pinMode(pin[i], OUTPUT);
        }
        
        off();
    }
    void on(int i) {
        Serial.print("Turn on: Pin: "); Serial.println(i);
        digitalWrite(pin[i], HIGH);
        //delay(500);
    }
    void turnPinOff(int i){ digitalWrite(pin[i], HIGH); }
    void off() {
        for (int i = 0; i < 3; i++) {
            digitalWrite(pin[i], LOW);
        }
    }
    //void timesOn(int i) {
    //    lastDebounceTime = millis();
    //    if(millis() - lastDebounceTime> )
    //}

};

class Button {
private:
    byte pin;
    byte state;
    byte lastReading;
    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay = 150;
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
        this->activated = false;
        this->timeName = nameTime;
};

    void printTime(bool er) {
        if (er) {
            Serial.println("Mistake");
        }
        Serial.print("Bottun ");
        Serial.print(getPinNum());
        Serial.print(" .Int: ");
        Serial.println(valuePerTime);
    }
    bool isActivated() {
        return(activated);
    }
    int getButtonVal() {
        if (activated) { return valuePerTime; }
        else { return -valuePerTime; }
    }
    bool delayUpdate() 
    {
        Serial.print("millis() "); Serial.println(millis());
        Serial.print("lastupdate() "); Serial.println(lastupdate);
        Serial.print("millis() - lastupdate() ");  Serial.println(millis() - lastupdate);
        if (millis() - lastupdate > durationToUpdate) { return true; }
        else { return false; };
    }
    // activate
    bool activate() {activated = true;}
    bool deactivate() { activated = false; }
    void updateTime() { 
        this->lastupdate = millis(); 
        if (activated) { activated = false; } 
        else { activated = true; } 
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
    RGBLed RHBLeds[8];

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
                DaysDottons[i].printTime(true);
            }
        }
        Serial.println("Initlize Time Bottums");
    }

    void lightOneAtTheTime() {
        //delay(2000);
        for (int i = 0; i < numLed; ++i) {
            leds[i].on();
            delay(2000);
        }
    }
    void detectTimePressed() {
        for (int i = 0; i < numDaysButtons; ++i) {

            if ((DaysDottons[i].isPressed() )&& (but1 == false)) {
                if (DaysDottons[i].delayUpdate())
                {
                    Serial.print("DaysDottons[i].isPressed() )&& (but1 == false)");

                    
                    //delay(1000);
                    Serial.println("Pressed To update Value");
                    // check wheether this button was pressen recently. if there is a good sequence of time -> update the params
                    // needs to have a break of 100 mil between each update
                    if (!DaysDottons[i].isActivated()) {
                        
                        ppl[0].updateVal(DaysDottons[i].getButtonVal()); // the person "owner" of the board always at pos 0 -> at the end this will be separate
                        Serial.println(ppl[0].getavailability());
                        Serial.print("After update Val is: "); Serial.println(DaysDottons[i].getButtonVal());
                        DaysDottons[i].updateTime();

                        
                    }

                    else{
                        Serial.print("Else: ");
                        ppl[0].updateVal(DaysDottons[i].getButtonVal()); // the person "owner" of the board always at pos 0 -> at the end this will be separate
                        DaysDottons[i].updateTime();
                                                                         
                                                                         //return  int(-DaysDottons[i].getButtonVal()); 
                    /*    break;*/
                    }
                    but1 = true;
                    //updateLastPress();
                    Serial.print("Is Activated: "); Serial.println(DaysDottons[i].isActivated());
                    //delay(1000);
                }


                //delay(1000);
            }
        }
       
    }
    int checkoverLab( int personone,int person2, int overlap, int i)
    {
        //Serial.println(personone);
        ////Serial.println(person2);
        ////Serial.println(overlap);
        //Serial.println(1 << i);
        //Serial.println(personone & (1 << i));
        //delay(1000);
        if (personone & (1 << i))
        {   
            Serial.print("Got personone right ");  Serial.println(1 << i);
            //delay(1000);

        return 0;
        }
        else if (person2 & (1 << i))
        {
            Serial.print("Got person2 right "); Serial.println(1 << i);
            //delay(1000);
            return 1;
        }
        else if (overlap & (1 << i))
        {
            Serial.println("Overlap");
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
        for (int n = 0; n < 10; n++) {
            //// check which RGB should light based on the bits
            int result = checkoverLab(personone, person2, overlap, n);
            int idx = get_idx(n) ;
            Serial.print("Result: ");
            Serial.println(result);
            Serial.print("idx: ");
            Serial.println(idx);
            //delay(1000);
            //Serial.print("result: "); Serial.print(result); Serial.print("n: "); Serial.println(n);
            if (result >-1) 
            {
                Serial.print("Day"); Serial.println(n);
                if (n <= 7) {
                    // morening
                    // index = i
                    RHBLeds[n].on(result);
                    Serial.print("Size: "); Serial.println(sizeof(RHBLeds));
                    }

                //else if (n < 16 && n >= 8)
                //{
                //    // index = %idxPButton -> second
                //    RHBLeds[int(n % 8)].on(result);
                //}
                else
                {
                    // index = %idxPButton -> overlap -> third
                    RHBLeds[int(n % 8)].on(result);
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

        Serial.print("outInt: "); Serial.println(outInt);
        Serial.print("personOneAvailableWithout: "); Serial.println(personOneAvailableWithout);
        Serial.print("personTwoAvailableWithout: "); Serial.println(personTwoAvailableWithout);

        displayAvailability(personOneAvailableWithout, personTwoAvailableWithout, outInt);

    }
    void checkLastPress() {
        Serial.println(millis());  Serial.println(lastPressed); Serial.println(millis() - lastPressed);

        if ((millis() - lastPressed > debounceDelay)) { //&& (anyPressed)
            // initlize all the RGBLED
            turnOffLed();
            anyPressed = false;
        }
    }
};


void createRGBLED() {
    int begin = 2;
    String nameDay[3] = { "Nonday", "Tuesday", "Wednsday" };
    String timeDay[3] = { "morning", "Noon", "Evening" };
    int timeNum[3] = { 0,1,2 };
    for (int i = begin; i < begin+3; ++i) {
        for (int j = 0; j < 3; ++j) {
            TimeButton bu();
        }
    }

}


//RGBLed
byte monday[3] = { RGBMondayp1 ,RGBMondayp2,  RGBMondayboth };
byte tuesday[3] = { RGBTuesdayp1 ,RGBTuesdayp2,  RGBTuesdayboth };
byte wednsday[3] = { RGBWednsdayMorning ,RGBWednsdayNoon,  RGBWednsdayEvening };

RGBLed rgbLedmonday(monday, RGBMondayp1);
RGBLed rgbLedtuesday(tuesday, RGBTuesdayp1);
// for later
RGBLed rgbLedwednsday(wednsday, RGBWednsdayMorning);



Button buttonPerson1(PINPersonOne);
Button buttonPerson2(PinPersonTwo);


// Time Button - > each Led would have its own value correponding to value it carries
// Monday Time Button
TimeButton buttonMondayMorning(BUTTON_PINMondayMorning,MondayMorningInt,"Monday Morning");
TimeButton buttonMondayNoon(BUTTON_PINMondayNoon, MondaynoongInt, "Monday Noon");
TimeButton buttonMondayEve(BUTTON_PINMondayEvening, MondayeveInt, "Monday eve");

// Tuesday Time Button
TimeButton buttonTuedayMorning(BUTTON_PINTuesdayMorning, TuesdayMorningInt, "Tueday Morning");
TimeButton buttonTuedayNoon(BUTTON_PINTuesdayNoon, TuesdayNoongInt, "Tueday Noon");
TimeButton buttonTuedayEve(BUTTON_PINTuesdayEve, TuesdayEveInt, "Tueday eve");

// Init Perople
Person person_1(VALUE_PERSON_1);
Person person_2(VALUE_PERSON_2);

// List Per objects -> this will be fed to the Board object
Button arrauButtons[1] = { };
Led arrayLED[1] = { };


Person ppl[2] = { person_1 , person_2 };

RGBLed RgbLeds[3] = { rgbLedmonday ,rgbLedtuesday ,rgbLedwednsday};

// time button
TimeButton daysButtons[6] = { buttonMondayMorning,buttonMondayNoon,buttonMondayEve, buttonTuedayMorning,buttonTuedayNoon, buttonTuedayEve }; // buttonMondayNoon

byte a = 0;

Board b(a, ppl, sizeof(ppl) / sizeof(ppl[0]), arrayLED, sizeof(arrayLED) / sizeof(arrayLED[0]), arrauButtons, sizeof(arrauButtons)/ sizeof(arrauButtons[0]), daysButtons, sizeof(daysButtons) / sizeof(daysButtons[0]), RgbLeds, sizeof(RgbLeds) / sizeof(RgbLeds[0])); // TODO: Transfer it to automatic len


void setup() {

    Serial.begin(9600);
}
int i = 0;
void loop() {
    Serial.println("Loop");

    //if (buttonPerson1.isPressed()) {
    //    b.checkIntAvailabale(0, 1);
    //}
    //b.detectTimePressed();
    //b.checkLastPress();
    //if (buttonPerson2.isPressed()) {
    //    but1 = false;
    //    Serial.println("Update");
    //} 
    for (int i = 0; i < 6; ++i) { if (daysButtons[i].isPressed()) { Serial.println(i);}}
}


    











// Regular LED
//Led led1(LED_1_PIN);
//Led led2(LED_2_PIN);
//Led led3(LED_3_PIN);
//Led led4(LED_4_PIN);

// regular Button
//Button button1(BUTTON_PIN1);
//Button button2(BUTTON_PIN2);
//Button button3(BUTTON_PIN3);



//
//// monday 
//#define BUTTON_PINMondayMorning 22
//#define MondayMorningInt 1 // will add a function that initilize all these value automatically. Yet for now , I write it manually
//
//#define BUTTON_PINMondayNoon 23
//#define MondaynoongInt 256 // will add a function that initilize all these value automatically. Yet for now , I write it manually
//
//#define BUTTON_PINMondayEvening 24
//#define MondayeveInt 65536 // will add a function that initilize all these value automatically. Yet for now , I write it manually
//
//
////tuesday
//#define BUTTON_PINTuesdayMorning 24
//#define TuesdayMorningInt 2
//
//#define BUTTON_PINTuesdayMorning 25
//#define TuesdayMorningInt 512
//
//#define BUTTON_PINTuesdayMorning 26
//#define TuesdayMorningInt 131072
//
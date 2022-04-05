/*
 Name:		bitoperations.ino
 Created:	3/18/2022 1:16:23 PM
 Author:	admin
*/
void splitter(int(&myarray)[3], int a) {
    byte   by1 = a & 0xFF;
    byte   by2 = (a >> 8) & 0xFF;
    byte   by3 = (a >> 16) & 0xFF;
    int myPins[] = { 2, 4, 8, 3, 6 };

    byte msg[3] = { by1, by2, by3 };
}



class Person {
public:
    int state;
    int availability;

    Person() {
        Serial.println("Person Init");

        state = 0;
        availability = 0;
    }

    int getState() {
        Serial.println(state);
        return state;
    }

    int getAvailability() {
        Serial.println(availability);
        return availability;
    }


    void setAvailability(int a) {
        Serial.print("setAvailability");

        this->availability += a;
    }

    void setState(int a) {
        Serial.print("setState");

        this->state = a;
    }
    void splitter(byte(&myarray)[3], int a) {
        byte   by1 = a & 0xFF;
        byte   by2 = (a >> 8) & 0xFF;
        byte   by3 = (a >> 16) & 0xFF;
        int myPins[] = { 2, 4, 8, 3, 6 };

        byte msg[3] = { by1, by2, by3 };
        for (int i = 0; i < 3; i++) {
            *(myarray + i) = msg[i];
        }
    }

    int CombineWord16toLong32(short s1, short s2, short s3)
    {
        state = ((s3 << 24) | (s2 << 16) | (s1 & 0xffff));
        return state;
    }

    void checkAvailability() {
        byte myInts[3] = { 0,0,0 };
        splitter(myInts, availability);

        for (byte i = 0; i < 3; i++)
        {
            String time = "";
            switch (i) {
            case 0:
                time = "Morning";
                break;
            case 1:
                time = "Noon";
                break;
            case 2:
                time = "Evening";
            }
            unsigned short state = myInts[i];
            auto size = sizeof(state);
            for (int j = 0; j < sizeof(state) * 4; j++)
            {
                int number = 1 << j;
                if ((state & (1 << j)))
                {
                    //cout << "1";
                    switch (j) {
                    case 0:
                        Serial.print("Monday");
                        Serial.println(time);
                        break;
                    case 1:
                        Serial.print("Tuesday ");
                        Serial.println(time);
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
    }
};
Person person1 = Person();

// the setup function runs once when you press reset or power the board
// the setup function runs once when you press reset or power the board
void setup() {
    Serial.print(9600);
}

// the loop function runs over and over again until power down or reset
void loop() {
    Serial.print("start ");

    person1.setState(3);
    person1.getState();
    person1.setState(3);

    delay(1000);

}

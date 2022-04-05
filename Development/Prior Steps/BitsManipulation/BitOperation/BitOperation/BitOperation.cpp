// BitOperation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <bits/stdc++.h>
#include<tuple>
#include <iostream>

using namespace std;
//
//class Person {
//public:
//    string name;
//    int id;
//    int state;
//    int availability;
//
//    Person() {
//        state = 0;
//        availability = 0;
//    }
//    
//    int getState() {
//        cout << state << endl;
//        return state;
//    }
//
//    int getAvailability() {
//        cout << availability << endl;
//        return availability;
//    }
//
//    //void set_availability() {
//
//    //    std::vector<vector<int>> d(3);
//    //    //std::vector<int> d;
//    //    int in;
//    //    cout << "Enter Amount of times:" << endl;
//    //    cin >> in;
//    //    for (int i = 0; i < d.size(); i++) {
//
//    //    }
//    //    cout << "\Enter preference etc..:\n";
//    //    for (int i = 0; i < in; i++) {
//    //        cout << "ship" << i + 1 << ":" << ' ';
//    //        for (int j = 0; j < in; j++) {
//    //            cin >> temp;
//    //            d[i].push_back(temp);
//    //        }
//    //    }
//    //}
//
//
//    void setAvailability(int a) {
//
//       
//        this->availability += a;
//    }
//
//    void setState(int a) {
//        this->state= a;
//    }
//
//    vector<unsigned short> splitter(int a) {
//        unsigned short by1 = a & 0xFF;
//        unsigned short by2 = (a >> 8) & 0xFF;
//        unsigned short by3 = (a >> 16) & 0xFF;
//        vector<unsigned short> out = { by1, by2, by3 };
//        return out;
//    }
//
//
//    int CombineWord16toLong32(short s1, short s2, short s3)
//    {
//        state = ((s3 << 24) | (s2 << 16) | (s1 & 0xffff));
//        return state;
//    }
//
//    void checkAvailability() {
//        vector<unsigned short> currentAvailability = splitter(availability);
//
//        for (int i = 0; i < currentAvailability.size(); i++)
//        {
//            string time = "";
//            switch (i) {
//            case 0:
//                time = "Morning";
//                // cout << "Morning" << endl;;
//                break;
//            case 1:
//                time = "Noon";
//                break;
//            case 2:
//                time = "Evening";
//            }
//            unsigned short state = currentAvailability[i];
//            auto size = sizeof(state);
//            for (int j = 0; j < sizeof(state) * 4; j++)
//            {
//                int number = 1 << j;
//                if ((state & (1 << j)))
//                {
//                    //cout << "1";
//                    switch (j) {
//                    case 0:
//                        cout << "Monday " << time << endl;;
//                        break;
//                    case 1:
//                        cout << "Tuesday " << time << endl;;
//                        break;
//                    case 2:
//                        cout << "Wednesday " << time << endl;;
//                        break;
//                    case 3:
//                        cout << "Thursday " << time << endl;;
//                        break;
//                    case 4:
//                        cout << "Friday " << time << endl;;
//                        break;
//                    case 5:
//                        cout << "Saturday " << time << endl;;
//                        break;
//                    case 6:
//                        cout << "Sunday " << time << endl;;
//                        break;
//                    }
//                }
//                else
//                {
//                    //cout << "0";
//                }
//            }
//        }
//    }
//};


/*
 Name:    bitoperations.ino
 Created: 3/18/2022 1:16:23 PM
 Author:  admin
*/

//class Person {
//public:
//    int state;
//    int availability;
//
//    Person() {
//        state = 0;
//        availability = 0;
//    }
//
//    int getState() {
//        Serial.println(state);
//        return state;
//    }
//
//    int getAvailability() {
//        Serial.println(availability);
//        return availability;
//    }
//
//
//    void setAvailability(int a) {
//        this->availability += a;
//    }
//
//    void setState(int a) {
//        this->state = a;
//    }
//    void splitter(byte(&myarray)[3], int a) {
//        byte   by1 = a & 0xFF;
//        byte   by2 = (a >> 8) & 0xFF;
//        byte   by3 = (a >> 16) & 0xFF;
//        int myPins[] = { 2, 4, 8, 3, 6 };
//
//        byte msg[3] = { by1, by2, by3 };
//        for (int i = 0; i < 3; i++) {
//            *(myarray + i) = msg[i];
//        }
//    }
//
//    int CombineWord16toLong32(short s1, short s2, short s3)
//    {
//        state = ((s3 << 24) | (s2 << 16) | (s1 & 0xffff));
//        return state;
//    }
//
//    void checkAvailability() {
//        byte myInts[3] = { 0,0,0 };
//        splitter(myInts, availability);
//
//        for (byte i = 0; i < 3; i++)
//        {
//            String time = "";
//            switch (i) {
//            case 0:
//                time = "Morning";
//                break;
//            case 1:
//                time = "Noon";
//                break;
//            case 2:
//                time = "Evening";
//            }
//            unsigned short state = myInts[i];
//            auto size = sizeof(state);
//            for (int j = 0; j < sizeof(state) * 4; j++)
//            {
//                int number = 1 << j;
//                if ((state & (1 << j)))
//                {
//                    //cout << "1";
//                    switch (j) {
//                    case 0:
//                        Serial.print("Monday");
//                        Serial.println(time);
//                        break;
//                    case 1:
//                        Serial.print("Tuesday ");
//                        Serial.println(time);
//                        break;
//                    case 2:
//                        Serial.print("Wednesday ");
//                        Serial.println(time);
//                        break;
//                    case 3:
//                        Serial.print("Thursday ");
//                        Serial.println(time);
//                        break;
//                    case 4:
//                        Serial.print("Friday ");
//                        Serial.println(time);
//                        break;
//                    case 5:
//                        Serial.print("Saturday ");
//                        Serial.println(time);
//                        break;
//                    case 6:
//                        Serial.print("Sunday ");
//                        Serial.println(time);
//                        break;
//                    }
//                }
//                else
//                {
//                    //cout << "0";
//                }
//            }
//        }
//    }
//};
// the setup function runs once when you press reset or power the board

int main() {



    //Person person1 = Person();

    //person1.setAvailability(2);
    ////person1.setAvailability(256);

    //person1.checkAvailability();


    string value = "25";

    cout << "val" << "ue" << endl;

}


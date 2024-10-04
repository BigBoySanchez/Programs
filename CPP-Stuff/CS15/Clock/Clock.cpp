#include "Clock.h"
#include <iostream>
#include <ctime>
using namespace std;
Clock::Clock(int h, int m , int s , bool ismorn ) {
    setHour(h); // hour = h;
    setMinute(m); //minute = m;
    setSecond(s); //second = s;
    setIsMorning(ismorn); //isMorning = ismorn;
}

Clock::Clock(char timeZone, bool isDST) {
    time_t curr = time(0);
    int zoneOffset = 0;
    int h = 0;

    //"grabbing" the offset for the timezone
    switch(timeZone) {
        //USA! USA! USA!
        case 'p':
            zoneOffset = -8;
            break;
        case 'm':
            zoneOffset = -7;
            break;
        case 'c':
            zoneOffset = -6;
            break;
        case 'e':
            zoneOffset = -5;
            break;
        case 'a':
            zoneOffset = -4;
            break;
        case 'h':
            zoneOffset = -10;
            break;
        //Other countries...
        case 'u':
            zoneOffset = 0;
            break;
        case 'g':
            zoneOffset = 2;
            break;
        case 'i':
            zoneOffset = 7;
            break;
        case 't':
            zoneOffset = 8;
            break;
        case 'f':
            zoneOffset = 1;
            break;
        case 'z':
            zoneOffset = 12;
            break;
    }

    h = (curr / (60 * 60)) % 24 + zoneOffset + isDST;   //gets regular hours then adds offset and +1 if isDST
    if(h < 0) {h += 24;}                                //"rolls back" if hours is negative
    else if(h >= 24) {h -= 24;}                          //"rolls over" if hours is too big
    
    if(h == 0 || h == 12) {hour = 12;}                  //if midnight or noon            
    else {hour = h % 12;}                               //otherwise, h should be 1-11

    minute = (curr / 60) % 60;
    second = curr % 60;
    isMorning = (h < 12);
}

int Clock::getSecond() const {
    return second;
}
int Clock::getMinute() const {
    return minute;
}
int Clock::getHour() const {
    return hour;
}
bool Clock::getIsMorning() const {
    return isMorning;
}
// Mutators
void Clock::setSecond(int s) {
    if (s < 0) {
        s = 0;
    }
    else if (s > 59) {
        s = 59;
    }
    second = s;
}
void Clock::setMinute(int m) {
    if (m < 0) {
        m = 0;
    }
    else if (m > 59) {
        m = 59;
    }
    minute = m;
}
void Clock::setHour(int h) {
    if (h > 12)
        h = 12;
    if (h < 1)
        h = 1;
    hour = h;
}
void Clock::setIsMorning(bool ismorn) {
    isMorning = ismorn;
}

void Clock::tick() {
    if (second < 59)
        second++;
    else {
        second = 0;
        if (minute < 59) 
            minute++;
        else {
            minute = 0;
            if (hour == 11) {
                hour = 12;
                isMorning = !isMorning;
            }
            else if (hour == 12) 
                hour = 1;
            else 
                hour++;
        }
    }  
} 

// Alternatve version of tick()
void Clock::tickAlternateVersion () {
    second++; // Advance second and correct if value reaches 60.
    if (second == 60) {
        second = 0;
        minute++;  // Advance minute and correct if value reaches 60.
        if (minute == 60) {
           minute = 0;
           hour++;  // Handle special cases where hour reaches 12 or 13 below.
           if (hour == 12)
                isMorning = !isMorning;
           else if (hour == 13) 
                hour = 1; // Since this is a 12 hour clock.
        }
    }
}

void Clock::printTime() const {
    cout << hour << ":";
    if (minute < 10)
        cout << "0";
    cout << minute << ":";
    if (second < 10)
        cout << "0";
    cout << second << " ";
    if (isMorning)
        cout << "AM";
    else cout << "PM";
}
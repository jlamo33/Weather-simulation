//
//  Time.h
//  UpdatedSim
//
//  Created by Joshua LaMoria on 7/20/26.
//
using namespace std;
#include "string"
#pragma once

enum class DayState {
    
    DAY,
    NIGHT,
    EVENING,
    AFTERNOON,
    EARLY_MORNING,
    MORNING,
    DAWN,
    DUSK,
    SUNRISE,
    SUNSET,
    MIDNIGHT,
    NOON
    
};


class Time {
    
    
    /***
     Private variables:
     Time of day variable controls time of day
     Day counter will count number of days passed
     Total Seconds of day variable will control total seconds in day
     ---- depends on how much seconds you want the total day, can be mutable.
     for example on earth, total seconds is 86400
     Day state variable controls what state of the day it is, i.e dawn, dusk, night, day etc
     ------ will add functionailty for controlling weather, events, and other things.
     
     ***/
private:
    
    
    double timeOfDay;
    int dayCounter;
    int totalSecondsOfDay;
    double sunSet;
    double sunRise;
    double dawn;
    double dusk;
    DayState dayState;
    
    
    
public:
    
    // time constructor
    Time();
    
    
    // getter methods for returning time of day and day counter
    double getTimeOfDay() const;
    double getDayCounter() const;
    
    
    // resets the day to midnight (time of day = 0)
    void resetDay();
    
    
    void setTimeOfDay(double newTime);
    void setDayCounter(int newCounter);
    void setDayState(DayState state);
    void setTotalSecondsOfDay(int newSeconds);
    void setSunRise(int sunrise);
    void setSunSet(int sunset);
    
    bool isDay();
    bool isNight();
    bool isDawn();
    bool isDusk();
    
    
    void tick(double deltaTime, const double timeSpeed, int secondsOfDay);
    void setDawn(double newDawn);
    void updateDawn(double dawnSpan);
    void updateDusk(double duskSpan);
    
    double calcMinutesFromMidNight();
    double calcSecondsFromMidNight();
    double calcHoursFromMidNight();
    
    
    DayState determineDayState();
    string displayClock();
    string displayDayState();
    
    
};





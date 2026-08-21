//
//  Time.cpp
//  UpdatedSim
//
//  Created by Joshua LaMoria on 7/20/26.
//

#include "Time.h"
#include "cmath"
#include <iostream>
#include "sstream"
#include "iomanip"
using namespace std;

/**
 -------------
 Constructor:
    initlaize time of day to be 0 (Midnight)
    and day counter to be 0 and time of day 0
 ------------
 */
Time::Time()

: dayCounter(0),
  timeOfDay(0),
  dayState(DayState::MIDNIGHT)

{
    
}

/**
 ------------
 Tick method that updates time of day based on deltatime.
 wraps time of day with total seconds in day and updates day counter
 */
void Time::tick(double deltaTime, const double timeSpeed, int totalSecondsOfDay) {
    
    
    setTotalSecondsOfDay(totalSecondsOfDay);
    
    timeOfDay +=  timeSpeed * deltaTime;
    
    
    if(timeOfDay >= totalSecondsOfDay) {
        
        dayCounter += static_cast<int>(timeOfDay / totalSecondsOfDay);
        
    }
    
    // update dawn and dusk 
    updateDawn(30);
    updateDusk(30);
    timeOfDay = fmod(timeOfDay, totalSecondsOfDay);
    
}

/**
 ------------
 Resets the day to midnight and time of day = 0
 ----------
 */
void Time::resetDay() {
    
    timeOfDay = 0;
    setDayState(DayState::MIDNIGHT);
}


/**
 Returns time of day
 */
double Time::getTimeOfDay() const {
    
    return timeOfDay;
}

/**
 Returns day counter
 */
double Time::getDayCounter() const {
    
    return dayCounter;
}

/**
 sets time of day to desired time of day
 */

void Time::setTimeOfDay(double newTime) {
    
    timeOfDay = newTime;
}

/**
 Sets day state to desired day state
 */

void Time::setDayState(DayState newDayState) {
    
    dayState = newDayState;
}

/**
 sets day counter to desired day count
 */

void Time::setDayCounter(int newDayCounter) {
    
    dayCounter = newDayCounter;
}

/**
 sets total seconds of day to desired  total seconds of day,
 controls how long the day length is
 standard is 86400 seconds
 */

void Time::setTotalSecondsOfDay(int seconds) {
    
    totalSecondsOfDay = seconds;
}

/**
 sets  a specfic time for dawn
 */

void Time::setDawn(double newDawn) {
    
    dawn = newDawn;
}

/**
 sets a specfic time for dusk
 */

void Time::setSunRise(int sunrise) {
    
    sunRise = sunrise;
}

/**
 sets sunset to desired sunset
 */

void Time::setSunSet(int sunset) {
    
    sunSet = sunset;
}

/**
 updates dawn based on sunrise time
 allows user to specify the dawn span i.e how long is dawn before sunrise
 */

void Time::updateDawn(double dawnSpan) {
    
    dawn = (sunRise - dawnSpan * 60);
}

/**
 updates dusk based on sunset time
 allows user to specify the dusk span i.e how long dusk is after sunset
 */

void Time::updateDusk(double duskSpan) {
    
    dusk = (sunSet + duskSpan * 60);
}

/**
 flagger method, checks if it is daytime
 */

bool Time::isDay() {
    
    return timeOfDay >= sunRise && timeOfDay < sunSet;
}

/**
 flagger method, checks if it is dawn
 */


bool Time::isDawn() {
    
    return timeOfDay >= dawn && timeOfDay < sunRise;
}

/**
 flagger method, checks if it is dusk
 */

bool Time::isDusk() {
    
    return timeOfDay > sunSet && timeOfDay <= dusk;
}

/**
 flagger method, checks if it is night
 */
bool Time::isNight() {
    
    return timeOfDay > dusk || timeOfDay < dawn;
}



/**
 time calculation for miniutes.
 60 minutes per hour
 */


double Time::calcMinutesFromMidNight() {
    
    return fmod(timeOfDay, 3600) / 60;
}

/**
 time calculation for seconds
 60 seconds per minute
 */

double Time::calcSecondsFromMidNight() {
    
    return fmod(timeOfDay, 60);
}

/**
 time calculation for hours
 */

double Time::calcHoursFromMidNight() {
    
    return timeOfDay / 3600;
}

/**
 Determines the day state based on time of day
 */
DayState Time::determineDayState() {
    
    
    if(timeOfDay == sunRise) {
        
        return dayState = DayState::SUNRISE;
    }
    
    if(timeOfDay == sunSet) {
        
        return dayState = DayState::SUNSET;
    }
    
    
    if(isDawn()) {
        
        return dayState = DayState::DAWN;
    }
    
    else if(isDusk()) {
        
        return dayState = DayState::DUSK;
    }
    
    else if(isDay()) {
        
        return dayState = DayState::DAY;
    }
    
    else {
        
        return dayState = DayState::NIGHT;
    }
    
}


/**
 String method, displays day state
 */
std::string Time::displayDayState() {
    
    switch(dayState) {
            
        case DayState::DAY:
            
            return "Day☀️";
            
        case DayState::NIGHT:
            
            return "Night 🌌";
            
        case DayState::DUSK:
            
            return "Dusk🌙";
            
        case DayState::DAWN:
            
            return "Dawn🌙";
            
        case DayState::SUNSET:
            
            return "Sunset 🌅 ";
            
        case DayState::SUNRISE:
            
            return "Sunrise 🌅";
            
            
        default:
            
            return "UNKNOWN ";
            
            
    }
    
}
    
/**
String method,
displays clock
*/
std::string Time::displayClock() {
        
        int hours = calcHoursFromMidNight();
        int minutes = calcMinutesFromMidNight();
        int seconds = calcSecondsFromMidNight();
        
        std::string period = (hours < 12) ? "AM" : "PM";
        
        int hour12 = hours % 12;
        if (hour12 == 0) hour12 = 12;
        
        // Format as HH:MM:SS AM/PM
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << hour12 << ":"
        << std::setw(2) << std::setfill('0') << minutes << ":"
        << std::setw(2) << std::setfill('0') << seconds << " "
        << period;
        
        return oss.str();
    }

    

    


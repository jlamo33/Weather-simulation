//
//  Weather.h
//  UpdatedSim
//
//  Created by Joshua LaMoria on 8/20/26.
//

#include "Time.h"
#include <random>

enum weatherState {
    
    RAIN,
    CLEAR,
    THUNDERSTORM,
    CLOUDY,
    PARTLY_CLOUDY,
    SNOW
    
};


struct Rain {
    
};

struct Snow {
    
    
};

struct Thunder {
    
    
};

struct Clouds {
    
    
};

struct Temperature {
    
    
};

struct ClearWeather {
    
    
};

struct wind {
    
    
    
};

struct naturalDiaster {
    
    
};

class Weather {
    
    
private:
    
    /**
            Two important variables in the weather simultion,
            weather change interval controls the length of a weather state,
            and last change interval is the previous weather state length
     */
    int weatherChangeInterval;
    int lastChangeInterval;
    std::random_device rd;
    std::mt19937 gen;
     
    
    static const int MIN_WEATHER_CHANGE = 30; // half a minute
    static const int MAX_WEATHER_CHANGE = 120; // 2 minutes
    
    
public:
    
    // constructor for weather class
    Weather(Time& t);
    
    Time& t;
    
    
    /**
            getter and setter for weather change interval.
     */
    int getWeatherChangeInterval();
    void setweatherChangeInterval(int newChangeInterval);
    
    
    // updates weather interval.
    void updateWeatherInterval(double deltaTime);
};


//
//  Weather.h
//  UpdatedSim
//
//  Created by Joshua LaMoria on 8/20/26.
//

#include "Time.h"
#include <random>
#include "iostream"
using namespace std;
#pragma once

enum weatherState {
    
    RAIN,
    CLEAR,
    THUNDERSTORM,
    CLOUDY,
    PARTLY_CLOUDY,
    SNOW
    
};

struct Rain {
    
    double rainFactor = 0;
    double rainDepth;
    
    
    double calculateRainFactor(weatherState currentWeather) {
        
        if(rainFactor > 3.0) {
            
            rainFactor -= 0.05;
        }
        
        if(currentWeather == CLOUDY) {
            
            rainFactor += 0.03;
        }
        
        
        return rainFactor;
    }
    
    string debugRainFactor() {
        
        
        return "Rain Factor " + to_string(rainFactor);
    }
    
    
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
    weatherState currentWeather;
    
    static constexpr int MIN_WEATHER_CHANGE = 30; // half a minute
    static constexpr int MAX_WEATHER_CHANGE = 120; // 2 minutes
    std::uniform_int_distribution<int>dist;
    std::uniform_real_distribution<double>dist2;
    
    
    
public:
    
    // constructor for weather class
    Weather(Time& t);
    
    Time& t;
    Rain rain;
     
    
    
    /**
            getter and setter for weather change interval.
     */
    int getWeatherChangeInterval();
    int getLastChangeInterval();
    void setweatherChangeInterval(int newChangeInterval);
    
    
    // updates weather interval.
    void updateWeatherInterval(double deltaTime);
    void determineWeatherState();
    std::string displayWeatherState();
};



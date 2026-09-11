//
//  Weather.h
//  UpdatedSim
//
//  Created by Joshua LaMoria on 8/20/26.
//

#include "Time.h"
#include <random>
#include "iostream"
#include "math.h"
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

enum rainStates {
    
    LIGHT_RAIN,
    HEAVY_RAIN,
    MODERATE_RAIN,
    DRIZZLE,
    DOWN_POUR
};

struct Rain {
    
    
    // initalize the rain structs random distrubtion,
    std::uniform_int_distribution<int>dist_rain_struct;
    std::random_device rd;
    std::mt19937 gen;
    

    // variable rain factor will increase or decrerase the likelhood of rain
    double rainFactor = 0;
    
    // will measure rain depth amount in amount(units)
    double rainDepth = 0;
    
    // size of rain droplet
    double rainSphereRadius = 0;
    
    // how fast it is raining in amount(units) / per second
    double rainFallSpeed = 0;
    
    Rain():gen(rd()), dist_rain_struct(0, 100)
    {
    }
    
    // calculates rainfactor based on state of weather
    double calculateRainFactor(double deltaTime, weatherState stateOfWeather) {
        
        // rain factor is the percentange that increases the likelyhood of simulating rain
        
        // if the rain factor goes above 100 %
        if(rainFactor > 100.0) {
            
            rainFactor -= 0.4 * deltaTime;
        }
        
        switch(stateOfWeather) {
                
            case PARTLY_CLOUDY: {
                
                int roll = dist_rain_struct(gen);
                
                if(roll < 10) {
                    
                    rainFactor = max(rainFactor - 0.008 * deltaTime, 0.0);
                }
                rainFactor += 0.001 * deltaTime;
                break;
                
            }
                
            case CLOUDY: {
                
                int roll = dist_rain_struct(gen);
                
                // % 10 chance of no rain factor increase when it's cloudy.
                if(roll < 10) {
                    
                    rainFactor = max(rainFactor - 0.5 * deltaTime, 0.0);
                }
                
                rainFactor += 0.01 * deltaTime;
                break;
                
            }
                
            case RAIN: {
                
                int roll = dist_rain_struct(gen);
                
                if(roll < 50) {
                    
                    rainFactor = min(rainFactor + 0.9 * deltaTime, 100.0);
                }
                
                else if(roll < 100) {
                    
                    rainFactor = max(rainFactor - 0.7 * deltaTime, 0.0);
                }
                rainFactor += 1.1 * deltaTime;
                break;
                
            }
                
            case THUNDERSTORM:
                
                rainFactor += 88.1 * deltaTime;
                break;
                
            case SNOW:
                
                break;
                
            case CLEAR:
                
                break;
                
            default:
                
                rainFactor = 0;
                break;
        }
        
        
        return rainFactor;
    }
    
    double calculateRainSphereRadius(double deltaTime) {
        
        return -1;
    }
    
    void updateRainFactor(double deltaTime, weatherState currentWeather) {
        
        calculateRainFactor(deltaTime, currentWeather);
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
    weatherState previousWeather;
    
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
    weatherState getCurrentWeather();
    void setweatherChangeInterval(int newChangeInterval);
    void setWeatherState(weatherState newState);
    
    bool isRaining();
    
    
    // updates weather interval.
    void updateWeatherInterval(double deltaTime);
    void determineWeatherState();
    std::string displayWeatherState();
};



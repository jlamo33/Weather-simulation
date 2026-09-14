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
    
    // init the time object reference
    Time& t;
    
    
    // variable rain factor will increase or decrerase the likelhood of rain
    double rainFactor = 0;
    
    // likelhood of light rain
    double lightRainChance = 0;
    
    // likehood of heavy rain
    double heavyRainChance = 0;
    
    // will measure rain depth amount in amount(units)
    double rainDepth = 0;
    
    // size of rain droplet
    double rainSphereRadius = 0;
    
    // how fast it is raining in amount(units) / per second
    double rainFallSpeed = 0;
    
    rainStates rainIntensityState;
    
    
    
    
    Rain(Time& t)
    :dist_rain_struct(0, 100),
    gen(rd()),
    t(t)
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
                
            case THUNDERSTORM: {
                
                int roll = dist_rain_struct(gen);
                
                // 60 % chance that rain factor will decrease after thunderstorm
                if(roll < 60) {
                    
                    rainFactor = max(rainFactor - 20 * deltaTime, 0.0);
                }
                
                rainFactor += 10.1 * deltaTime;
                break;
                
            }
                
            case SNOW:
                
                rainFactor += 0.0001 * deltaTime;
                
                break;
                
            case CLEAR:
                
                break;
                
            default:
                
                rainFactor = 0;
                break;
        }
        
        
        return rainFactor;
    }
    
    double calculateHeavyRainFactor(double deltaTime, weatherState stateOfWeather) {
        
        
        switch(stateOfWeather) {
                
            case RAIN: {
                
                int roll = dist_rain_struct(gen);
                
                // 40 % chance rain wont lead to heavy rain
                if(roll < 40) {
                    heavyRainChance = max(heavyRainChance - 0.6 * deltaTime, 0.0);
                }
                
                // 60% chance rain wont lead to heavy rain
                else if(roll < 100) {
                    heavyRainChance += 0.001 * deltaTime;
                }
                
                // slight increase for heavy rain at night if raining
                if(t.isNight()) {
                    heavyRainChance += 1.1 * deltaTime;
                }
                
                else {
                    
                    // slight increase for heavy rain if it is raining
                    heavyRainChance += 0.5 * deltaTime;
                    
                }
            }
                
            case THUNDERSTORM: {
                
                int roll = dist_rain_struct(gen);
                
                // 70% chance thunder storm will increase to heavy rain
                if(roll < 70) {
                    heavyRainChance += 8 * deltaTime;
                }
                
                // 30% chance thunder storm will fade out
                else if(roll < 100) {
                    heavyRainChance = max(heavyRainChance - 10.5 * deltaTime, 0.0);
                }
                
                heavyRainChance += 1.21 * deltaTime;
            }
        }
        
        heavyRainChance = clamp(heavyRainChance, 0.0, 100.0);
        
        return heavyRainChance;
    }
    
    
    double calculateLightRainFactor(double deltaTime, weatherState stateOfWeather) {
        
        double lightRainChanceTimer = 0.0;
        
        switch(stateOfWeather) {
                
                
            case RAIN: {
                
                if(t.isDawn()) {
                    lightRainChance += 1.2 * deltaTime;
                }
                
                else if(t.isDusk()) {
                    
                    lightRainChance += 0.9 * deltaTime;
                }
                
                else {
                    
                    lightRainChance += 0.1 * deltaTime;
                }
                
            }
                
            case THUNDERSTORM: {
                
                lightRainChance += 0.2 * deltaTime;
            }
        }
        
        return lightRainChance;
    }
    
    void determineRainState(double deltaTime) {
        
        if(lightRainChance == heavyRainChance) {
            
            rainIntensityState = MODERATE_RAIN;
        }
        
        // must have atleast 20% chance for heavy rain
        if(hasHeavyRainChance(heavyRainChance,  20, deltaTime)) {
            
            rainIntensityState = HEAVY_RAIN;
        }
        
        
        // must have atleast 20% chance light rain
        else if(hasHeavyRainChance(lightRainChance, 20, deltaTime)) {
            
            rainIntensityState = LIGHT_RAIN;
        }
        
    }
    
    bool hasHeavyRainChance(double rainStateChance, double thresHold, double deltaTime) {
        
        return  rainStateChance >= (thresHold * deltaTime);
    }
    
    void updateRainFactor(double deltaTime, weatherState currentWeather) {
        
        calculateRainFactor(deltaTime, currentWeather);
    }
    
    void updateLightRainFactor(double deltaTime, weatherState currentWeather) {
        
        calculateLightRainFactor(deltaTime, currentWeather);
    }
    
    void updateHeavyRainFactor(double deltaTime, weatherState currentWeather) {
        
        calculateHeavyRainFactor(deltaTime, currentWeather);
    }
    
    string debugRainFactor() {
        
        return "Rain Factor " + to_string(rainFactor);
    }
    
    string debugHeavyRainFactor() {
        
        return "HEAVY_RAIN_CHANCE " + to_string(heavyRainChance);
    }
    
    string debugLightRainFactor() {
        
        return "LIGHT_RAIN_CHANCE " + to_string(lightRainChance);
    }
    
    string getRainState() {
        
        switch(rainIntensityState) {
                
            case HEAVY_RAIN:
                
                return "HEAVY RAIN";
                
            case LIGHT_RAIN:
                return "LIGHT_RAIN";
                
            case MODERATE_RAIN:
                return "MODERATE_RAIN";
        }
        
        return "EMPTY";
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
    Weather(Time& t, Rain& rain);
    
    Time& t;
    Rain& rain;
     
    
    
    /**
            getter and setter for weather change interval.
     */
    int getWeatherChangeInterval();
    int getLastChangeInterval();
    weatherState getCurrentWeather();
    void setweatherChangeInterval(int newChangeInterval);
    void setWeatherState(weatherState newState);
    weatherState updatePreviousWeather(weatherState weather);
    
    bool isRaining();
    bool isThunderStorming();
    
    bool wasRaining();
    
    bool hasRainCondintions();
    
    // updates weather interval.
    void updateWeatherInterval(double deltaTime);
    void determineWeatherState();
    std::string displayWeatherState();
};



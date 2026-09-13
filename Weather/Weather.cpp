//
//  Weather.cpp
//  UpdatedSim
//
//  Created by Joshua LaMoria on 8/21/26.
//

#include "Weather.h"
#include <random>
#include "iostream"


Weather::Weather(Time& t)
     
    :t(t),
    gen(rd())
{
    weatherChangeInterval = 0;
    dist = std::uniform_int_distribution<int>(MIN_WEATHER_CHANGE, MAX_WEATHER_CHANGE);
    dist2 = std::uniform_real_distribution<double>(0.0, 1.0);
    lastChangeInterval = dist(gen);
}

int Weather::getWeatherChangeInterval() {
    
    return weatherChangeInterval;
}

int Weather::getLastChangeInterval() {
    
    return lastChangeInterval;
}

void Weather::setWeatherState(weatherState newState) {
    
    currentWeather = newState;
}

weatherState Weather::getCurrentWeather() {
    
    return currentWeather;
}

bool Weather::isRaining() {
    
    return currentWeather == RAIN;
}

bool Weather::wasRaining() {
    
    return previousWeather == RAIN;
}

bool Weather::hasRainCondintions() {
    
    return previousWeather != CLEAR || previousWeather != PARTLY_CLOUDY;
}

void Weather::updateWeatherInterval(double deltaTime) {
    
    // add weather change interval to weather time
    weatherChangeInterval += deltaTime;
    
    // if last change interval exceeds 500, reset change interval to some random value
    if(lastChangeInterval > 500) {
        
        lastChangeInterval = dist(gen);
    }
    
    // if the random number is less than some threshold increase last change interval
    if(dist2(gen) < 0.03) {
        
        lastChangeInterval =  lastChangeInterval + dist(gen);
    }
    
    // when we pass last change interval , trigger a weather change
    if(weatherChangeInterval >= lastChangeInterval) {
        
        
        // reset weather change interval and pick new last change interval and weather d
        lastChangeInterval = dist(gen);
        weatherChangeInterval = 0;
        determineWeatherState();
        
    }
}

weatherState Weather::updatePreviousWeather(weatherState weather) {
    
    // get the currentWeather State
    weather = getCurrentWeather();
    
    // save it to previousWeather
    previousWeather = weather;
    
    // return that value in memory
    return previousWeather;
}

void Weather::determineWeatherState() {
    
    
    std::uniform_int_distribution<int>dist(0, MAX_WEATHER_CHANGE);
    int roll = dist(gen);
    
    if(roll < 20 && roll > 10 * rain.rainFactor && hasRainCondintions()) {
        
        currentWeather = weatherState::RAIN;
    }
    
    else if(roll < 25) {
        
        currentWeather = weatherState::THUNDERSTORM;
    }
    
    else if(roll < 60) {
        
        currentWeather = weatherState::CLEAR;
    }
    
    else if(roll < 90) {
        
        currentWeather = weatherState::PARTLY_CLOUDY;
    }
    
    else {
        
        currentWeather = weatherState::SNOW;
    }
}

string Weather::displayWeatherState() {
    
    switch(currentWeather) {
            
        case RAIN:
            
            return "🌧️";
            
        case CLEAR:
            
            return "☀️";
            
        case PARTLY_CLOUDY:
            
            return "🌤️";
            
        case THUNDERSTORM:
            
            return "⛈️";
            
        case SNOW:
            
            return "❄️";
            
        case CLOUDY:
            
            return "☁️";
            
        default:
            
            return "Unknown State";
            
    }
}

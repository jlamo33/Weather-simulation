//
//  Weather.cpp
//  UpdatedSim
//
//  Created by Joshua LaMoria on 8/21/26.
//

#include "Weather.h"
#include <random>


Weather::Weather(Time& t)
     
    :t(t),
    gen(rd())
{
    
}

int Weather::getWeatherChangeInterval() {
    
    return weatherChangeInterval;
}

void Weather::updateWeatherInterval(double deltaTime) {
    
    // add weather change interval to weather time
    weatherChangeInterval += deltaTime;
    
    // when we pass last change interval , trigger a weather change
    if(weatherChangeInterval > lastChangeInterval) {
        
        std::uniform_int_distribution<int>dist(MIN_WEATHER_CHANGE, MAX_WEATHER_CHANGE);
        
        lastChangeInterval = dist(gen);
        weatherChangeInterval = 0;
        
    }
}

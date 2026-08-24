//
//  Simulation.h
//  UpdatedSim
//
//  Created by Joshua LaMoria on 8/16/26.
//

#include "Time.h"
#include "Weather.h"


class Simulation {
    
    
private:
    
    double deltaTime;
    
    
    
public:
    
    Time& time;
    Weather& weather;
    Simulation(Time& time, Weather& weather);
    double getDeltaTime();
    void update(double timeOfDay, int currentDay);
    void initliaze(double timeOfDay, int currentDay, int sunrise, int sunset);
    
    void showSim();
    
};


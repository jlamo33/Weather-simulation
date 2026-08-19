//
//  Simulation.h
//  UpdatedSim
//
//  Created by Joshua LaMoria on 8/16/26.
//

#include "Time.h"


class Simulation {
    
    
private:
    
    double deltaTime;
    
    
    
public:
    
    Time& time;
    Simulation(Time& time);
    double getDeltaTime();
    void update(double timeOfDay, int currentDay);
    void initliaze(double timeOfDay, int currentDay, int sunrise, int sunset);
    
    void showSim();
    
};


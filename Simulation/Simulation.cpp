//
//  Simulation.cpp
//  UpdatedSim
//
//  Created by Joshua LaMoria on 8/16/26.
//

#include "Simulation.h"
#include "iostream"
#include <chrono>
#include "thread"
using sim_clock = std::chrono::steady_clock;
using namespace std;
/**
 Constructor,
 init time connection
 */
Simulation::Simulation(Time& time_ref)
    
    : time(time_ref)
    
    {
    }


/**
 returns deltatime
 */
double Simulation::getDeltaTime() {
    
    return deltaTime;
}


/**
 Init sim condintions like time of day,  current day,
 sunrise and sunset times
 */
void Simulation::initliaze(double timeOfDay, int currentDay, int sunrise, int sunset) {
    
    time.setTimeOfDay(timeOfDay);
    time.setDayCounter(currentDay);
    time.setSunRise(sunrise);
    time.setSunSet(sunset);
}


/**
 updates simulation, contains main loop
 and delta time calculation
 */
void Simulation::update(double timeOfDay, int currentDay) {
    
    // initliaze simulation
    initliaze(timeOfDay, currentDay, 7 * 3600, 17 * 3600);
    
    auto lastTime = sim_clock::now(); // it's exactly now again
    
    // main loop
    while(true) {
        
        
        const double factor = 72;
        auto currentTime = sim_clock::now();
        deltaTime = chrono::duration<double>(currentTime - lastTime).count();
        time.tick(deltaTime, factor, 86400);
        time.determineDayState();
        
        lastTime = currentTime;
        
        showSim();
        
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

/**
 
 show the simulation results
 */
void Simulation::showSim() {
    
    cout << time.displayClock()
         << " | "
         << time.displayDayState()
         << endl;
}





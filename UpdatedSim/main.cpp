//
//  main.cpp
//  UpdatedSim
//
//  Created by Joshua LaMoria on 7/20/26.
//

#include <iostream>
#include "Simulation.h"
#include "time.h"
#include "Weather.h"
int main(int argc, const char * argv[]) {
    
    /**
        run simulation
     */
    Time t;
    Rain r(t);
    Weather w(t, r);
    Simulation s(t, w);
    s.update(19 * 3600, 0);
    return EXIT_SUCCESS;
}

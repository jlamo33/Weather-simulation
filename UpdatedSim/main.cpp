//
//  main.cpp
//  UpdatedSim
//
//  Created by Joshua LaMoria on 7/20/26.
//

#include <iostream>
#include "Simulation.h"
#include "time.h"
int main(int argc, const char * argv[]) {
    
    /**
        run simulation
     */
    Time t;
    Simulation s(t);
    s.update(6 * 3600, 0);
    return EXIT_SUCCESS;
}

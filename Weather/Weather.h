//
//  Weather.h
//  UpdatedSim
//
//  Created by Joshua LaMoria on 8/20/26.
//

enum weatherState {
    
    RAIN,
    CLEAR,
    THUNDERSTORM,
    CLOUDY
    
};


struct Rain {
    
    

struct Snow {
    
    
}

struct Thunder {
    
    
}

struct Clouds {
    
    
}

struct Temperature {
    
    
}

struct ClearWeather {
    
    
}

struct wind {
    
    
    
}

struct naturalDiaster {
    
    
}

class Weather {
    
    
private:
    
    /**
            Two important variables in the weather simultion,
            weather change interval controls the length of a weather state,
            and last change interval is the previous weather state length
     */
    private int weatherChangeInterval;
    private int lastChangeInterval;
     
    
    
public:
    
    int getWeatherChangeInterval();
    void setweatherChangeInterval(int newChangeInterval);
};


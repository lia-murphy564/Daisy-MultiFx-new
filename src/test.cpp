#include "main.h"
#include <stdio.h>
#include <iostream>
#include <iostream>
#include <math.h>

#define M_PI           3.14159265358979323846  /* pi */

/*
    g++ -o test test.cpp -I/src
*/
 
void PARAMETER_CONFIG() {
    float paramVal = 0.0f;
    ParameterConfig conf;
    //ParameterMap map;

    param_config pconf[10];
    pconf[0].label = "Pot 1";
    pconf[0].type = param_type::kPot;
    pconf[0].min = 0;
    pconf[0].max = 100;
    pconf[0].scale = param_scale::kLin;

    conf.initParameters(&pconf[0]);

    //conf.setParameters();

    // param p;
    // p.label = "pot1";
    // p.val = 0.5f;
    // p.type = param_type::kPot;
    // map.insert(p);

    //std::cout << "init param value " << map.getValue(0) << std::endl;

    int i = 0;
    while (i < 20) {
        paramVal++;
        i++;
        conf.setParameterValue(paramVal, 0);
        std::cout << conf.getParameterValue(0) << std::endl;
        //std::cout << paramVal << std::endl; 
        //map.setValueAtIndex(paramVal, 0);
        //std::cout << map.getValue(0) << std::endl;
    }
}

    float processAudios(float xn) {
        int curr_state = stateManager.getState();
        Skeleton effect;

        float yn = 0.0f;

        switch (curr_state) {
            case 0:
                yn = effect.processAudioSample(xn);
        }

        return yn;    
    }

void AUDIO_PASSTHROUGH() {
    StateManager stateManager;



    float xn = 0.5f;
    float yn = processAudios(xn);
    std::cout << xn << " " << yn;
}

void RUN_ALL_TESTS() {
    //PARAMETER_CONFIG();
    AUDIO_PASSTHROUGH();
}

int main(void) {
    RUN_ALL_TESTS();
    return 0;
}
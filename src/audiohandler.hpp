// #ifndef _AUDIOHANDLER_H_
// #define _AUDIOHANDLER_H_

// #include "daisy.h"
// #include "daisysp.h"
// #include "daisy_seed.h"

#include "lmdsp.hpp"
#include "parameter_controller.h"
#include "statemanager.h"
#include "daisysp.h"

StateManager stateManager;

float processAudio(float xn, ParameterMap* params) {

    //float _fs = SaiHandle::Config::SampleRate::SAI_48KHZ;

    int curr_state = stateManager.getState();

    Passthrough passthrough;
    passthrough.setParameters(*params);
    GainStage gainstage;
    gainstage.setParameters(*params);

    // daisysp::Autowah _autowah;
    // _autowah.Init();

    //Skeleton skeleton;
    //stateManager.insertEffect(skeleton);

    float yn = 0.0f;

    //effect = stateManager.getEffect(curr_state);
    //return effect.processAudioSample(xn);

    switch(curr_state) {
        case 0:
            yn = passthrough.processAudioSample(xn);
        case 1:
            yn = gainstage.processAudioSample(xn);
    }
    
    return yn;
}

// #endif
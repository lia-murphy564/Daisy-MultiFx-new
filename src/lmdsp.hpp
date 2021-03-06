#ifndef _LMDSP_H_
#define _LMDSP_H_

#include <stdlib.h>
#include <stdint.h>

#include "parameter_controller.h"

class LMAudioSignalProcessor {
public:
    LMAudioSignalProcessor() {};
    virtual ~LMAudioSignalProcessor() {};
    //virtual bool reset(double _fs);
    //virtual bool canProcessAudioFrame();
    //virtual void setSampleRate(double _fs); 
    virtual float processAudioSample(float xn) {
        return xn;
    }
    virtual bool processAudioFrame(const float* inputFrame, 
                                    float* outputFrame, 
                                    uint32_t inputChannels,
                                    uint32_t outputChannels) {
        return false;
    }
};

class Passthrough : public LMAudioSignalProcessor {
private:
    ParameterMap params;
public:
    Passthrough() {};
    ~Passthrough() {};
    //bool reset(double _fs);
    //bool canProcessAudioFrame();
    //virtual void setSampleRate(double _fs); 
    float processAudioSample(float xn) {
        return xn;
    }
    bool processAudioFrame(const float* inputFrame, 
                                    float* outputFrame, 
                                    uint32_t inputChannels,
                                    uint32_t outputChannels) {
        return false;
    }
    void setParameters(ParameterMap p) {
        params = p;
    }
};

class GainStage : public LMAudioSignalProcessor {
private:
    ParameterMap params;
    int gain;
public:
    GainStage() {};
    ~GainStage() {};
    //bool reset(double _fs);
    //bool canProcessAudioFrame();
    //virtual void setSampleRate(double _fs); 
    float processAudioSample(float xn) {
        return xn * gain;
    }
    bool processAudioFrame(const float* inputFrame, 
                                    float* outputFrame, 
                                    uint32_t inputChannels,
                                    uint32_t outputChannels) {
        return false;
    }
    void setParameters(ParameterMap p) {
        params = p;
        gain = params.getValue(1);
    }
};

// class SkeletonParameters : public ParameterConfig {
//     SkeletonParameters() {}

//     SkeletonParameters& operator=(const SkeletonParameters& params) {
//         if (this == &params)
//             return *this;

//         // variable = params.variable;
//         return *this;
//     }

//     void setParameters() {
//         // pconf[1].label = "asudh";
//         // pconf[0].label = "Pot 1";
//         // pconf[0].type = param_type::kPot;
//         // pconf[0].min = 0;
//         // pconf[0].max = 1;
//         // pconf[0].scale = param_scale::kLin;

//         //setInitialParameterState();
//     }

//     // datatype variable = 0;
// };

// class Skeleton : public LMAudioSignalProcessor {
//     private:
//         SkeletonParameters parameters;
//         double sampleRate;

//     public:
//         Skeleton() {};
//         ~Skeleton() {};

//         virtual bool reset(double _fs) {
//             sampleRate = _fs;
//             return true;
//         }
//         // virtual void setSampleRate() { sampleRate = _fs;} 
//         virtual bool canProcessAudioFrame() { return false; } // or true

//         virtual bool processAudioFrame(const float* inputFrame, 
//                                     float* outputFrame, 
//                                     uint32_t inputChannels,
//                                     uint32_t outputChannels) {
//             return false;
//         }
//     //test
//         virtual float processAudioSample(float xn) {
//             float yn = xn;

//             // --- DSP goes here

//             return yn;
//         }
// };

// class Passthrough : public LMAudioSignalProcessor {

// };

// class Waveshaper : public LMAudioSignalProcessor {

// };



#endif
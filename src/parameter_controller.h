#ifndef _PARAMETER_CONTROLER_H_
#define _PARAMETER_CONTROLER_H_

#include <string>
#include <unordered_map>
#include <iterator>
#include <math.h>
#include <algorithm>

#include "daisy.h"
#include "daisysp.h"
#include "daisy_seed.h"

//#include "json.hpp"

//using json = nlohmann::json;

enum param_type {
    kPot,
    kSwitch,
    kStatus
};

enum param_scale {
    kLin,
    kLog,
    kRlog
};

struct param_config {
    std::string label;
    std::string type;
    std::string scale;
    float min, max;
};

struct param {
	std::string label;
	std::string type;
    std::string scale;
    int index;
	float val;
    float min, max;

    bool operator<(const param& p) const
    {
        if (index < p.index)
            return true;
        else return false;
    }
    bool operator==(const param& p) const
    {
        if (label == p.label && type == p.type && val == p.val)
            return true;
        else return false;
    }
};

// float normalize(uint16_t value, float min, float max)
//     {
//         int outputLimit = 256;

//         float range = (max - min);// - float.Epsilon; // Here we shorten the range slightly

//         // Then we build a range such that value >= 0 and value < 1
//         float rangedValue = (value - min) / range;

//         return min + (int)(outputLimit * rangedValue);
//     }

template<class T>
constexpr const T& clamp( const T& v, const T& lo, const T& hi )
{
    int outputLimit = 256;
    float range = (hi - lo);// - float.Epsilon;
    float rangedValue = (v - lo) / range;
    return lo + (int)(outputLimit * rangedValue);
}


template<class T>
constexpr const float clamp( const float v, const float lo, const float hi )
{
    int outputLimit = 256;
    float range = (hi - lo);// - float.Epsilon;
    float rangedValue = (v - lo) / range;
    return lo + (int)(outputLimit * rangedValue);
}

class ParameterMap {

private:
    std::unordered_map<int, param> map;
    std::unordered_map<int, param>::iterator map_iter;

public: 
    ParameterMap() {};
    ~ParameterMap() {};

    void insert(param p) {
        int index = p.index;

        map.insert(std::make_pair(index, p));
    }

    void updateMap(param p) {
        map[p.index] = p;
    }

    void setValueAtIndex(uint16_t val, uint16_t index) {
        param curr = map[index];
        curr.val = val;
        map[index] = curr;
    }

    float getValue(int index) {
        float val = map.at(index).val;//map[idx];//map.at(idx).val;
		return val;
    }  
};

class ParameterConfig : public ParameterMap {

    protected:
        param_config pconf[10];
        param params[10];
    public:

        virtual void setParameters() {

            pconf[0].label = "Pot 1";
            pconf[0].type = param_type::kPot;
            pconf[0].min = 0;
            pconf[0].max = 1;
            pconf[0].scale = param_scale::kLin;

            setInitialParameterState();
        }

        void setInitialParameterState() {
            for (int i = 0; i < 10; i++) {
                params[i].label = pconf[i].label;
                params[i].type = pconf[i].type;
                params[i].min = pconf[i].min;
                params[i].max = pconf[i].max;
                params[i].scale = pconf[i].scale;
                params[i].val = 0;
                params[i].index = i;
            }
        }

        void updateParameters() {
            // for (param p: params) {
            //     update(p);
            // }
            for (int i = 0; i < 10; i++) {
                updateMap(params[i]);
                params[i].val = clamp(params[i].val, params[i].min, params[i].max);
            }
        }
};

#endif

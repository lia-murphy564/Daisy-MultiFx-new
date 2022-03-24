#ifndef _STATEMANAGER_H_
#define _STATEMANAGER_H_

#include <unordered_map>
#include "lmdsp.hpp"

// struct stateId {
//     int state;
//     int prev_state;

//     // stateId() {};

//     bool operator==(stateId &other) { 
//         return (state == other.state
//             &&prev_state == other.prev_state);
//     }
//     // bool operator==(stateId &other) { 
//     //     return (state == other.state
//     //         &&prev_state == other.prev_state);
//     // }
// };

// struct stateId_hasher {
//     // stateId_hasher() {
        
//     // };

//   std::size_t operator()(stateId& s) {
//     using std::size_t;
//     using std::string;
//     using std::hash;

//     return ((hash<int>()(s.state)
//              ^ (hash<int>()(s.prev_state) << 1)) >> 1);
//   }
// };

class StateManager {
private:
    //stateId state_id;
    //std::unordered_map<int, LMAudioSignalProcessor*, stateId_hasher> effect_bank;
    int state;
    std::unordered_map<int, LMAudioSignalProcessor*> effect_bank;


public:
    StateManager() {};
    ~StateManager() {};
    
    void setState(int s) {
        // state_id.prev_state = state_id.state;
        // state_id.state = s;
        state = s;
    }

    int getState() {
        //return state_id.state;
        return state;
    }

    void insertEffect(LMAudioSignalProcessor effect) {
        effect_bank.insert(std::make_pair(state, &effect));
    }

    LMAudioSignalProcessor getEffect(int index) {
        setState(index);
        // stateId curr;
        // curr.state = index;
        // return effect_bank[curr];
        return *effect_bank[index];
    }
};

#endif
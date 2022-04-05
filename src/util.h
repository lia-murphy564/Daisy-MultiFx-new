#ifndef _UTIL_H_
#define _UTIL_H_

template<class T>
constexpr const T& clamp( const T& v, const T& lo, const T& hi )
{
    int outputLimit = 256;
    float range = (hi - lo);// - float.Epsilon;
    float rangedValue = (v - lo) / range;
    return lo + (int)(outputLimit * rangedValue);
}

// template<class T>
// class ParameterRamper {
// 	T clampLow, clampHigh;
//     T _goal;
//     T inverseSlope;
//     //AUAudioFrameCount samplesRemaining;
//     int samplesRemaining;

// public:
// 	ParameterRamper(float value) {
// 		set(value);
// 	}

//     void set(float value) {
//         _goal = value;
//         inverseSlope = 0.0;
//         samplesRemaining = 0;
//     }

//     //void startRamp(float newGoal, AUAudioFrameCount duration) {
//     void startRamp(float newGoal, int duration) {    
//         if (duration == 0) {
//             set(newGoal);
//         }
//         else {
//             /*
//             	Set a new ramp.
//             	Assigning to inverseSlope must come before assigning to goal.
//             */
//             inverseSlope = (get() - newGoal) / float(duration);
//             samplesRemaining = duration;
//             _goal = newGoal;
//         }
//     }

//     float get() const {
//         /*
// 			For long ramps, integrating a sum loses precision and does not reach 
//             the goal at the right time. So instead, a line equation is used. y = m * x + b.
// 		*/
//         return inverseSlope * float(samplesRemaining) + _goal;
//     }
	
// 	float goal() const { return _goal; }
	
//     void step() {
//         // Do this in each inner loop iteration after getting the value.
//         if (samplesRemaining != 0) {
// 			--samplesRemaining;
// 		}
//     }

//     float getStep() {
//         // Combines get and step. Saves a multiply-add when not ramping.
//         if (samplesRemaining != 0) {
//             float value = get();
//             --samplesRemaining;
//             return value;
//         }
// 		else {
//             return _goal;
//         }
//     }

//     //void stepBy(AUAudioFrameCount n) {
//     void setBy(int n) {
//         /*
//             When a parameter does not participate in the current inner loop, you 
//             will want to advance it after the end of the loop.
//         */
//         if (n >= samplesRemaining) {
// 			samplesRemaining = 0;
//         }
// 		else {
// 			samplesRemaining -= n;
// 		}
//     }
// };

template<class T>
class SmoothedValue {
private:
	T _target;
	T _delta;
	T _v;
	int _nsteps;
	const int _ksteps;
public:
	SmoothedValue(T v, int steps=64): _v(v), _target(v), _delta(0), _ksteps(steps), _nsteps(0)
	{
	}
	~SmoothedValue()
	{
	}
	
	void setValue(T v)
	{
		_nsteps=0;
		_target = v;
		_v = v;
		_delta = 0;
	}

	void setTargetValue(T target)
	{
		_nsteps = _ksteps;
		_target = target;
		_delta = (_target-_v)/(T)_nsteps;	
	}

	T getValue() const
	{
		return _v;
	}

	T getTargetValue() const
	{
		return _target;
	}
	
	void tick()
	{
		if (_nsteps) {
			_v = _target-_delta*(T)_nsteps; 
			_nsteps--;
		}
	}

	bool isStillSmoothing() const
	{
		return (_nsteps!=0);
	}

};


#endif
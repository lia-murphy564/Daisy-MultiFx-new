#include "main.h"

#include "daisy.h"
#include "daisy_seed.h"
#include "daisysp.h"

#include "util.h"

//#include "libDaisy/Drivers/CMSIS/RTOS/Template/cmsis_os.h"
//#include "CMSIS/RTOS2/Template/cmsis_os.h"

using namespace daisy;
using namespace daisy::seed;

#define PARAM_BUFFER_SIZE	10
#define AUDIO_BUFFER_SIZE	128
#define HTIM1_MS	100

daisy::DaisySeed hw;

daisy::UartHandler usart1;
daisy::TimerHandle htim1;
daisy::GPIO gpio;

//static uint32_t DSY_SDRAM_BSS audio_buffer[AUDIO_BUFFER_SIZE];
//static uint16_t DSY_SDRAM_BSS param_buffer[PARAM_BUFFER_SIZE];

//AudioHandler audio;

// void AudioCallback(daisy::AudioHandle::InputBuffer in, daisy::AudioHandle::OutputBuffer out, size_t size)
// {
// 	for (size_t i = 0; i < size; i++)
// 	{
// 		out[0][i] = in[0][i];
// 		out[1][i] = in[1][i];
// 	}
// }

// void TIM1_Init(daisy::TimerHandle& tim) {
// 	daisy::TimerHandle::Config conf;
// 	conf.periph = daisy::TimerHandle::Config::Peripheral::TIM_2;
// 	conf.dir = daisy::TimerHandle::Config::CounterDir::UP;
// 	tim.Init(conf);
// 	tim.DelayMs(HTIM1_MS);
// 	tim.Start();
// }


void UART_Init(daisy::UartHandler &uart) {
	daisy::UartHandler::Config usart1_conf;
	usart1_conf.periph = UartHandler::Config::Peripheral::USART_1;
	usart1_conf.mode = UartHandler::Config::Mode::TX_RX;
	usart1_conf.wordlength = UartHandler::Config::WordLength::BITS_8;
	usart1_conf.parity = UartHandler::Config::Parity::NONE;
	usart1_conf.stopbits = UartHandler::Config::StopBits::BITS_1;
	usart1_conf.baudrate = (uint32_t)9600;
	usart1_conf.pin_config.rx = Pin(PORTB, 7); // (USART_1 RX) Daisy pin 15
	usart1_conf.pin_config.tx = Pin(PORTB, 6); // (USART_1 TX) Daisy pin 14

	if (uart.Init(usart1_conf) == UartHandler::Result::ERR) {
		hw.PrintLine("Init error");
		//return daisy::UartHandler::CheckError	
	}

	if (uart.StartRx() == UartHandler::Result::ERR) {
		hw.PrintLine("StartRx error");
	}
}

float paramVal;

//osThreadId Task1Handle;

// void Task1(void *arg) {
// 	while (true) {
// 		hw.PrintLine("hello from task1");
// 		//hw.DelayMs(10);
// 		//osDelay(10);
// 	}
// }

// osThreadDef(Task1, osPriorityNormal, 0, 128);

// osThreadId thread1_id;

// void thread1(void const *args) {
//     while (true) {
//         hw.PrintLine("hello from thread1");
//     }
// }

// osThreadDef(thread1, osPriorityNormal, 1, 128);

//static ParameterMap DSY_QSPI_BSS params;

//stateId state;
ParameterConfig paramConf;


constexpr const float clamp( const float v, const float lo, const float hi )
{
    int outputLimit = 256;
    float range = (hi - lo);// - float.Epsilon;
    float rangedValue = (v - lo) / range;
    return lo + (int)(outputLimit * rangedValue);
}

daisysp::Phaser phaser;
//float gain = 0.0f;
//ParameterRamper paramRamper(gain);
//SmoothedValue<float> gain;
//std::vector<void*> effect_bank;
float params[10];
ParameterMap parameterMap;
static daisysp::Autowah _autowah;
static daisysp::Overdrive _overdrive;

void AudioCallback(daisy::AudioHandle::InputBuffer in, daisy::AudioHandle::OutputBuffer out, size_t size)
{ 
	// for (size_t i = 0; i < size; i++)
    // {
	//  		out[0][i] = in[0][i];
	// 		out[1][i] = in[1][i];
	// }
	//void* effect;
	int state = 1;
	float xnL, xnR, ynL, ynR;
	//float params[10];
	//params[0] = parameterMap.getValue(0);
	//params[1] = parameterMap.getValue(1);
	//params[2] = parameterMap.getValue(2);	


    for (size_t i = 0; i < size; i++)
    {
		xnL = xnR = in[1][i];
		switch(state) {
			case 0:
				_autowah.SetWah(params[0]);
				_autowah.SetLevel(params[1]);
				_autowah.SetDryWet(params[2]);
				ynL = ynR = _autowah.Process(xnL);
			case 1:
				ynL = ynR = xnL;
			case 2:
				_overdrive.SetDrive(params[1]/50);
				ynL = ynR = _overdrive.Process(xnL);

			//out[0][i] = ynL;//processAudio(in[0][i], &parameterMap);
			out[1][i] = ynR;//processAudio(in[1][i], &parameterMap);
		}
    }
} 



int main(void)
{
	hw.Init();
	hw.SetAudioBlockSize(4); // number of samples handled per callback
	hw.SetAudioSampleRate(SaiHandle::Config::SampleRate::SAI_48KHZ);
	hw.StartAudio(AudioCallback); // callback in AudioHandler.h
	//hw.StartLog(true);
	UART_Init(usart1);

	float fs = hw.AudioSampleRate();

    //daisysp::Autowah* _autowah = new daisysp::Autowah;
	//daisysp::Overdrive* _overdrive = new daisysp::Overdrive;

    _autowah.Init(fs);
	_overdrive.Init();
	//_overdrive->Init();


	// param p[10];
	// p[0].label = "Pot1";
	// p[0].val = 1.0f;
	// p[0].type = param_type::kPot;
	// p[0].index = 1;
	// parameterMap.insert(p[0]);
	// parameterMap.setValueAtIndex(0.4f, p[0].index);
	// float test = 1.2f;
	//hw.PrintLine("%f", test);
	//hw.PrintLine("INIT %u %u", p[0].index, parameterMap.getValue(p[0].index));	

	// parameterMap.insert(p[4]);
	// for (int i = 0; i < 10; i++) {
	// 	parameterMap.insert(p[i]);
	// 	hw.PrintLine("INIT %u %u", i, parameterMap.getValue(i));
	// }


		

	//TIM1_Init(htim1);
	//std::vector<uint32_t> paramBuf;
	//ParameterTree pt;
	//osThreadDef(Task3, Task1_Init, osPriorityBelowNormal, 128);

	//osKernelInitialize();
	//thread1_id = osThreadCreate(osThread(thread1), NULL);
	//osThreadNew(Task1, NULL, &threadAttr_thread1);
	//osKernelStart();


	std::vector<uint32_t> param_buffer;

	while (true) {

		// POLL BLE
		 while (usart1.Readable()) {
			
			uint32_t curr_val = usart1.PopRx();
			param_buffer.push_back(curr_val);
	
			if (!usart1.Readable()) {
				usart1.FlushRx();

				uint16_t val;
				uint16_t index;
				for (int i = 0; i < param_buffer.size(); i++) {
			 		//hw.PrintLine("%x", param_buffer[i]);
					if (i % 2 == 0)
						val = param_buffer[i];
					else if (i % 2 == 1)
						index = param_buffer[i];

					param curr;
					curr.val = val;
					if (curr.index == index) {
						curr.index = index;
					}
					params[index] = (float)val;
					//hw.PrintLine("%u", params[index]);
					//hw.PrintLine("SET: %u %u", val, index);
					//parameterMap.setValueAtIndex(val, index);
					//hw.PrintLine("%f", parameterMap.getValue(0));	
					//gain = parameterMap.getValue(1) / 100;
					//paramRamper.set(gain);
					//paramRamper.startRamp(gain, 1);
					//gain = paramRamper.getStep();
					//gain.setTargetValue(parameterMap.getValue(1) / 100);
					//hw.PrintLine("%u", gain);
					//hw.PrintLine("GET: %f %u", parameterMap.getValue(index), index);
	
			 	}
			}

		 }
		 

		//  for (int i = 0; i < param_buffer_size; i++) {
		// 	 hw.Print("%c", param_buffer[i]);
		// 	 if (i == param_buffer_size) {
		// 	 	param_buffer_size = 0;
		// 	 }
		//  }

		// while (!paramBuf.empty()) {
		// 	uint32_t curr = paramBuf.back();
		// 	paramBuf.pop_back();
		// }

	}
}


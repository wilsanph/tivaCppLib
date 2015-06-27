/*
 * MapAdc.hpp
 *
 *  Created on: 27/06/2015
 *      Author: Gabriela
 */

#pragma once

#include "../memorymap/MapAdc.hpp"


namespace Adc
{

	namespace converter
	{
		enum _converter
		{
			ADC0 = 0x40038000,
			ADC1 = 0x40039000
		};
	}
	namespace sequencer
	{
		enum _sequencer
		{
			sequencer0 = 1,
			sequencer1 = 2,
			sequencer2 = 4,
			sequencer3 = 8
		};

	}
	namespace configOptions
	{
		namespace trigger
		{
			enum _trigger
			{
				SOFTWARE 	= 0x00,
				ANALOGCOMP0 = 0x01,
				ANALOGCOMP1 = 0x02,
				EXTGPIO     = 0x04,
				TIMER	    = 0x05,
				CONTINUOUS  = 0x0f
			};
		}

		namespace sample
		{
			enum _sample
			{
				SAMPLE_1ST = 0,
				SAMPLE_2ND = 4,
				SAMPLE_3RD = 8,
				SAMPLE_4TH = 12,
				SAMPLE_5TH = 16,
				SAMPLE_6TH = 20,
				SAMPLE_7TH = 24,
				SAMPLE_8TH = 28
			};
		}


		namespace inputpin
		{
			enum _inputpin
			{
				AIN0  = 0,
				AIN1  = 1,
				AIN2  = 2,
				AIN3  = 3,
				AIN4  = 4,
				AIN5  = 5,
				AIN6  = 6,
				AIN7  = 7,
				AIN8  = 8,
				AIN9  = 9,
				AIN10 = 10,
				AIN11 = 11
			};
		}
		namespace tempsensor
		{
			enum _tempsensor
			{
				SELECT_TEMPSENSOR  = 8,
				OMMIT_TEMPSENSOR   = 0
			};
		}
		namespace interruptEnable
		{
			enum _interruptEnable
			{
				SAMPLE_INT_ENABLED   = 4,
				SAMPLE_INT_DISABLED	 = 0
			};
		}
		namespace endOfSequence
		{
			enum _endOfSequence
			{
				ISENDOFSAMPLE   = 2,
				ISNTENDOFSAMPLE = 0
			};
		}
		namespace differentialMode
		{
			enum _differentialMode
			{
				SELECTDIFFMODE = 1,
				OMMITDIFFMODE  = 0
			};
		}

		namespace sampleRate
		{
			enum _sampleRate
			{
				SAMPLE_125KSPS 	= 0x1,
				SAMPLE_250KSPS  = 0x3,
				SAMPLE_500KSPS  = 0x5,
				SAMPLE_1MSPS	= 0x7
			};
		}
	}


	inline void setSampleRate(converter::_converter converter_,configOptions::sampleRate::_sampleRate sampleRate_);
	inline void enableClock(converter::_converter converter_);

	template<adc::converter::_converter converter_,adc::sequencer::_sequencer sequencer_>
	class Adc
	{

		public:

			static inline void disableSequencer();
			static inline void enableSequencer();
			static inline void selectTrigger(configOptions::trigger::_trigger trigger_);
			static inline void sampleConfigure(configOptions::sample::_sample sample_,
											   configOptions::inputpin::_inputpin inputpin_,
											   configOptions::tempsensor::_tempsensor tempsensor_,
											   configOptions::interruptEnable::_interruptEnable intEnable_,
											   configOptions::endOfSequence::_endOfSequence endOfSequence_,
											   configOptions::differentialMode::_differentialMode diffMode_);
			static inline void softBeginSampling();
			static inline bool finishedSampling();
			static inline void clearInterrupt();
			static inline void takeData(unsigned short *buff);
	};


}

typedef adc::adcMod<adc::converter::adc0,adc::sequencer::sequencer0> adc0seq0;
typedef adc::adcMod<adc::converter::adc0,adc::sequencer::sequencer1> adc0seq1;
typedef adc::adcMod<adc::converter::adc0,adc::sequencer::sequencer2> adc0seq2;
typedef adc::adcMod<adc::converter::adc0,adc::sequencer::sequencer3> adc0seq3;

typedef adc::adcMod<adc::converter::adc1,adc::sequencer::sequencer0> adc1seq0;
typedef adc::adcMod<adc::converter::adc1,adc::sequencer::sequencer1> adc1seq1;
typedef adc::adcMod<adc::converter::adc1,adc::sequencer::sequencer2> adc1seq2;
typedef adc::adcMod<adc::converter::adc1,adc::sequencer::sequencer3> adc1seq3;

#include "../src/ADCimplement.hpp"

/*
 * Timer.hpp
 *
 *  Created on: 29/12/2014
 *      Author: wilbert
 */

#ifndef TIMER_HPP_
#define TIMER_HPP_

#pragma once

#include "../GProjectCore/GObject.hpp"

namespace GpTimer
{
	
	namespace timerModule
	{
		enum _timerModule 
		{  
			TIMER0_SIMPLE = 0x40030000,
			TIMER1_SIMPLE = 0x40031000,
			TIMER2_SIMPLE = 0x40032000,
			TIMER3_SIMPLE = 0x40033000,
			TIMER4_SIMPLE = 0x40034000,
			TIMER5_SIMPLE = 0x40035000,
			TIMER0_WIDE  = 0x40036000,
			TIMER1_WIDE  = 0x40037000,
			TIMER2_WIDE  = 0x4004c000,
			TIMER3_WIDE  = 0x4004d000,
			TIMER4_WIDE  = 0x4004e000,
			TIMER5_WIDE  = 0x4004f000			
		};
	}

	namespace subtimer
	{
		enum _subtimer 
		{  
			SUBTIMER_A = 0,
			SUBTIMER_B = 1
		};
	}

	namespace config
	{
		
		namespace timerConfig
		{
			namespace statusCode
			{
				enum _statusCode
				{
					NONE = 0,
					MAX_PERIOD_REACHED = 1,
					CONFIG_WRONG_SUBTIMER = 2				
				};
			}

			namespace joiningMode
			{
				enum _joiningMode 
				{  
					joint = 0x00,
					disjoint = 0x04
				};
			}

			namespace countDirection
			{
				enum _countDirection 
				{  
					down = 0x00,
					up = 0x10
				};
			}

			namespace timerMode
			{
				enum _timerMode
				{
					oneShot = 0x01,
					periodic = 0x02
				};
			}

			namespace timerAlternateModeSelect
			{
				enum _timerAlternateModeSelect
				{
					capOrCompEnabled = 0x00,
					pwmEnabled = 0x08
				};
			}

			namespace timerInterrupts
			{
				enum _timerInterrupts
				{
					/*
					none 		= 0x00000000,
					matchSubA   = 0x00000010,
					timeoutSubA = 0x00000001,
					matchSubB   = 0x00000800,
					timeoutSubB = 0x00000100					
					*/
					none = 0,					
					timeout = 1,
					match = 2
				};
			}

			namespace interruptFlag
			{
				enum _interruptFlag 
				{
					matchSubA   = 0x00000010,
					timeoutSubA = 0x00000001,
					matchSubB   = 0x00000800,
					timeoutSubB = 0x00000100						
				};
			}
		}

		namespace pwmConfig
		{
			namespace outputLevel
			{
				enum _outputLevel 
				{  
					normal = 0x40,
					inverted = 0
				};
			}
		}

	}

	class Timer : public gObject::GObject
	{

	public:
		Timer();
		Timer( timerModule::_timerModule tTimerMod,
			   subtimer::_subtimer tSubtimer );

		void init();

		config::timerConfig::statusCode::_statusCode config ( u32 period_us,
															  float tick_resolution_us,
												 			  config::timerConfig::joiningMode::_joiningMode tJoiningMode = config::timerConfig::joiningMode::disjoint,
												 			  config::timerConfig::countDirection::_countDirection tCountDirection = config::timerConfig::countDirection::down,
												 			  config::timerConfig::timerMode::_timerMode tTimerMode = config::timerConfig::timerMode::periodic,
												 			  config::timerConfig::timerInterrupts::_timerInterrupts tInterrupt = config::timerConfig::timerInterrupts::timeout );
		void disableTimer();
		void enableTimer();
		void clearInterrupt( config::timerConfig::interruptFlag::_interruptFlag tInterruptFlag );

	protected:
		timerModule::_timerModule m_timerMod;
		subtimer::_subtimer m_subTimer;

		////void setMatchRegister( u32 value );
		
	};

	class Pwm : public Timer
	{

	public:

		Pwm();
		Pwm( timerModule::_timerModule tTimerMod,
			 subtimer::_subtimer tSubtimer );

		void init();

		void configPWM( u32 period_us,
					 float duty,
					 config::pwmConfig::outputLevel::_outputLevel pwmOutputLevel );

		void setDuty( float duty );

	private:
		u32 m_period_us;
		float m_duty;
	};

	/*************************************************************
	* Template implementations of the Timer and Pwm classes
	*************************************************************/

	template<timerModule::_timerModule tTimerModule,
			 subtimer::_subtimer tSubtimer>
	class tTimer
	{
	public:
		static inline config::timerConfig::statusCode::_statusCode config ( u32 period_us,
															  				float tick_resolution_us,
												 			  				config::timerConfig::joiningMode::_joiningMode tJoiningMode = config::timerConfig::joiningMode::disjoint,
												 			  				config::timerConfig::countDirection::_countDirection tCountDirection = config::timerConfig::countDirection::down,
												 			  				config::timerConfig::timerMode::_timerMode tTimerMode = config::timerConfig::timerMode::periodic,
												 			  				config::timerConfig::timerInterrupts::_timerInterrupts tInterrupt = config::timerConfig::timerInterrupts::timeout );
		static inline void enable();
		static inline void disable();
		static inline void clearInterrupt( config::timerConfig::interruptFlag::_interruptFlag tInterruptFlag );
	};

	template<timerModule::_timerModule tTimerModule,
			 subtimer::_subtimer tSubtimer>
	class tPwm : public tTimer<tTimerModule,tSubtimer>
	{
	public:
		static u32 period_us;
		static float duty;

		inline void configPWM( u32 tPeriod_us,
							   float tDuty,
							   config::pwmConfig::outputLevel::_outputLevel tPwmOutputLevel = config::pwmConfig::outputLevel::normal );
		inline void setDuty( float tDuty );
	};

}

#include "../src/TimerImplement.hpp"
#include "../src/TTimerImplement.hpp"


#endif /* TIMER_HPP_ */

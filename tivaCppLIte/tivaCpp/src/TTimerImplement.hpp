/*
 * TTimerImplement.hpp
 *
 *  Created on: 27/05/2015
 *      Author: Wilsan
 */

#ifndef TTIMERIMPLEMENT_HPP_
#define TTIMERIMPLEMENT_HPP_

#pragma once

#include "../memorymap/MapTimer.hpp"
#include "../include/Timer.hpp"

#include "../include/Clock.hpp"

namespace GpTimer
{

	/*************************************************************
	* Template implementations of the Timer and Pwm classes
	*************************************************************/

	template<GpTimer::timerModule::_timerModule tTimerModule,
			 GpTimer::subtimer::_subtimer tSubtimer>
	GpTimer::config::timerConfig::statusCode::_statusCode GpTimer::tTimer<tTimerModule,tSubtimer>::config( 
																		  u32 tPeriod_us,
												 			  			  float tTick_resolution_us,
												 			  			  GpTimer::config::timerConfig::joiningMode::_joiningMode tJoiningMode,
												 			  			  GpTimer::config::timerConfig::countDirection::_countDirection tCountDirection,
												 			  			  GpTimer::config::timerConfig::timerMode::_timerMode tTimerMode,
												 			  			  GpTimer::config::timerConfig::timerInterrupts::_timerInterrupts tInterrupt )
	{
		volatile GpTimer::config::timerConfig::statusCode::_statusCode stCode = GpTimer::config::timerConfig::statusCode::NONE;

		// Disable the corresponding subtimer
		reinterpret_cast<MapTimer::GPTimerRegs*>
			( tTimerModule )->GPTMCTL &= 0xffffffff - ( 1 << ( tSubtimer * 8 ) );

		// Configure the joining mode, weather or not the subtimers are joint
		reinterpret_cast<MapTimer::GPTimerRegs*>
			( tTimerModule )->GPTMCFG = tJoiningMode;

		// Configure the corresponding subtimer ( see that x4 inside the cast?-> it's ...
		// ...just an offset depending of the subtimer )
		reinterpret_cast<MapTimer::GPTimerRegs*>
			( tTimerModule + 4 * tSubtimer )->GPTMTAMR = tTimerMode | tCountDirection;

		// Calculate the prescaler and the number of timer ticks according to the desired tick resolution
		volatile u32 preescaler = ( u32 )( clock::Clock::CLOCK_RATE_MHZ * tTick_resolution_us );
		volatile u32 numTimerTicks = ( u32 )( clock::Clock::CLOCK_RATE_MHZ * tPeriod_us / preescaler );

		// Load the calculated prescaler value in the prescaler register
		reinterpret_cast<MapTimer::GPTimerRegs*>
			( tTimerModule + 4 * tSubtimer )->GPTMTAPR = preescaler;

		// Load the calculated number of ticks in the periodLoadRegister
		reinterpret_cast<MapTimer::GPTimerRegs*>
			( tTimerModule + 4 * tSubtimer )->GPTMTAILR = numTimerTicks;

		// Enable interrupts if needed
		if ( tSubtimer == GpTimer::subtimer::SUBTIMER_A )
		{
			// Clear previous configuration for subtimer A
			reinterpret_cast<MapTimer::GPTimerRegs*>
				( tTimerModule )->GPTMIMR &= 0xffffffe0;
			if ( tInterrupt == GpTimer::config::timerConfig::timerInterrupts::timeout )
			{
				reinterpret_cast<MapTimer::GPTimerRegs*>
					( tTimerModule )->GPTMIMR |= 0x0001;
			}
			else if ( tInterrupt == GpTimer::config::timerConfig::timerInterrupts::match )
			{
				reinterpret_cast<MapTimer::GPTimerRegs*>
					( tTimerModule )->GPTMIMR |= 0x0010;
			}
		}
		else {
			// Clear previous configuration for subtimer B
			reinterpret_cast<MapTimer::GPTimerRegs*>
				( tTimerModule )->GPTMIMR &= 0xfffff0ff;
			if ( tInterrupt == GpTimer::config::timerConfig::timerInterrupts::timeout )
			{
				reinterpret_cast<MapTimer::GPTimerRegs*>
					( tTimerModule )->GPTMIMR |= 0x0100;
			}
			else if ( tInterrupt == GpTimer::config::timerConfig::timerInterrupts::match )
			{
				reinterpret_cast<MapTimer::GPTimerRegs*>
					( tTimerModule )->GPTMIMR |= 0x0800;
			}
		}

		// Enable the subtimer
		reinterpret_cast<MapTimer::GPTimerRegs*>
			( tTimerModule )->GPTMCTL |= ( 1 << 8 * tSubtimer );

		#ifdef DEBUG
		// Check if the current configuration is posible, if not, set a status code.
		if ( tTimerModule < GpTimer::timerModule::TIMER0_WIDE &&
			 numTimerTicks > 0x0000ffff &&
			 tJoiningMode == GpTimer::config::timerConfig::joiningMode::disjoint )
		{			
			// For this configuration... you would get a max. period of 209 ms
			stCode = GpTimer::config::timerConfig::statusCode::MAX_PERIOD_REACHED;
		}
		if ( tJoiningMode == GpTimer::config::timerConfig::joiningMode::joint &&
			 tSubtimer == GpTimer::subtimer::SUBTIMER_B )
		{	
			// For this configuration... the subtimerB should be in use
			stCode = GpTimer::config::timerConfig::statusCode::CONFIG_WRONG_SUBTIMER;
		}
		#endif
		
		return stCode;
	}

	template<GpTimer::timerModule::_timerModule tTimerModule,
			 GpTimer::subtimer::_subtimer tSubtimer>
	void GpTimer::tTimer<tTimerModule,tSubtimer>::enable()
	{
		// Enable the subtimer
		reinterpret_cast<MapTimer::GPTimerRegs*>
			( tTimerModule )->GPTMCTL |= ( 1 << 8 * tSubtimer );
	}

	template<GpTimer::timerModule::_timerModule tTimerModule,
			 GpTimer::subtimer::_subtimer tSubtimer>
	void GpTimer::tTimer<tTimerModule,tSubtimer>::disable()
	{
		// Enable the subtimer
		reinterpret_cast<MapTimer::GPTimerRegs*>
			( tTimerModule )->GPTMCTL &= 0xffffffff - ( 1 << 8 * tSubtimer );
	}

	template<GpTimer::timerModule::_timerModule tTimerModule,
			 GpTimer::subtimer::_subtimer tSubtimer>
	void GpTimer::tTimer<tTimerModule,tSubtimer>::clearInterrupt( GpTimer::config::timerConfig::interruptFlag::_interruptFlag tInterruptFlag )
	{
		// Clear the given flag
		reinterpret_cast<MapTimer::GPTimerRegs*>
			( tTimerModule )->GPTMICR |= tInterruptFlag;
	}
	
	/**
	 * PWM template library implementation
	 *
	 */

	template<GpTimer::timerModule::_timerModule tTimerModule,
			 GpTimer::subtimer::_subtimer tSubtimer>
	u32 GpTimer::tPwm<tTimerModule,tSubtimer>::period_us = 50;

	template<GpTimer::timerModule::_timerModule tTimerModule,
			 GpTimer::subtimer::_subtimer tSubtimer>
	float GpTimer::tPwm<tTimerModule,tSubtimer>::duty = 0.2;

	template<GpTimer::timerModule::_timerModule tTimerModule,
			 GpTimer::subtimer::_subtimer tSubtimer>
	void GpTimer::tPwm<tTimerModule,tSubtimer>::configPWM( 
								  u32 tPeriod_us,
		 					   	  float tDuty,
		 					   	  GpTimer::config::pwmConfig::outputLevel::_outputLevel tPwmOutputLevel )
	{
		tPwm<tTimerModule,tSubtimer>::period_us = tPeriod_us;
		tPwm<tTimerModule,tSubtimer>::duty = tDuty;

		// Disable the corresponding subtimer
		reinterpret_cast<MapTimer::GPTimerRegs*>
			( tTimerModule )->GPTMCTL &= 0xffffffff - ( 1 << ( tSubtimer * 8 ) );

		// Configure the joining mode to disjoint
		reinterpret_cast<MapTimer::GPTimerRegs*>
			( tTimerModule )->GPTMCFG = GpTimer::config::timerConfig::joiningMode::disjoint;

		// Configure the corresponding subtimer ( see that x4 inside the cast?-> it's ...
		// ...just an offset depending of the subtimer )
		reinterpret_cast<MapTimer::GPTimerRegs*>
			( tTimerModule + 4 * tSubtimer )->GPTMTAMR = GpTimer::config::timerConfig::timerMode::periodic |
																	GpTimer::config::timerConfig::countDirection::down |
																	GpTimer::config::timerConfig::timerAlternateModeSelect::pwmEnabled;

		// The tick resolution in us is the tick resolution of the clock itself in pwm mode ...
		// ... because there is no preescaler :D, just a extended timer
		volatile u64 totalTimer = clock::Clock::CLOCK_RATE_MHZ * tPeriod_us;
		volatile u64 dutyTimer = ( u64 )( clock::Clock::CLOCK_RATE_MHZ * tPeriod_us * tDuty );
		volatile u32 preescaler = 0;
		volatile u32 intervalLoad = 0;
		volatile u32 dutyPreescaler = 0;
		volatile u32 dutyIntervalLoad = 0;
		if ( tTimerModule < GpTimer::timerModule::TIMER0_WIDE )
		{
			// If working with a 16 bit simple timer
			intervalLoad = totalTimer & 0x000000000000ffff;
			preescaler = ( totalTimer & 0x0000000000ff0000 ) >> 16;

			dutyIntervalLoad = dutyTimer & 0x000000000000ffff;
			dutyPreescaler = ( dutyTimer & 0x0000000000ff0000 ) >> 16;

		}
		else {
			// If working with a 32 bit wide timer
			intervalLoad = totalTimer & 0x00000000ffffffff;
			preescaler = ( totalTimer & 0x0000ffff00000000 ) >> 32;

			dutyIntervalLoad = dutyTimer & 0x00000000ffffffff;
			dutyPreescaler = ( dutyTimer & 0x0000ffff00000000 ) >> 32;
		}


		// Load the calculated prescaler value in the prescaler register
		reinterpret_cast<MapTimer::GPTimerRegs*>
			( tTimerModule + 4 * tSubtimer )->GPTMTAPR = preescaler;

		reinterpret_cast<MapTimer::GPTimerRegs*>
			( tTimerModule + 4 * tSubtimer )->GPTMTAPMR = dutyPreescaler;

		// Load the calculated number of ticks in the periodLoadRegister
		reinterpret_cast<MapTimer::GPTimerRegs*>
			( tTimerModule + 4 * tSubtimer )->GPTMTAILR = intervalLoad;

		// Load the value of the period * duty in the match register
		reinterpret_cast<MapTimer::GPTimerRegs*>
			( tTimerModule + 4 * tSubtimer )->GPTMTAMATCHR = dutyIntervalLoad;

		// Set the output mode
		reinterpret_cast<MapTimer::GPTimerRegs *>
			( tTimerModule )->GPTMCTL |= pwmOutputLevel;

		// Enable the subtimer
		reinterpret_cast<MapTimer::GPTimerRegs*>
			( tTimerModule )->GPTMCTL |= ( 1 << 8 * tSubtimer );
	}

	template<GpTimer::timerModule::_timerModule tTimerModule,
			 GpTimer::subtimer::_subtimer tSubtimer>
	void GpTimer::tPwm<tTimerModule,tSubtimer>::setDuty( float tDuty )
	{
		tPwm<tTimerModule,tSubtimer>::duty = tDuty;
		
		tDuty = ( tDuty > 0.99 ) ? 0.99 : tDuty;
		tDuty = ( tDuty < 0.01 ) ? 0.01 : tDuty;
		volatile u64 dutyTimer = ( u64 )( clock::Clock::CLOCK_RATE_MHZ * 
											tTimer<tTimerModule,tSubtimer>::period_us * 
											tDuty );
		volatile u32 dutyPreescaler = 0;
		volatile u32 dutyIntervalLoad = 0;
		if ( tTimerModule < GpTimer::timerModule::TIMER0_WIDE )
		{
			dutyIntervalLoad = dutyTimer & 0x000000000000ffff;
			dutyPreescaler = ( dutyTimer & 0x0000000000ff0000 ) >> 16;
		}
		else {
			dutyIntervalLoad = dutyTimer & 0x00000000ffffffff;
			dutyPreescaler = ( dutyTimer & 0x0000ffff00000000 ) >> 32;
		}

		reinterpret_cast<MapTimer::GPTimerRegs*>
			( tTimerModule + 4 * tSubtimer )->GPTMTAPMR = dutyPreescaler;

		reinterpret_cast<MapTimer::GPTimerRegs*>
			( tTimerModule + 4 * tSubtimer )->GPTMTAMATCHR = dutyIntervalLoad;
	}

}

#endif /* TTIMERIMPLEMENT_HPP_ */

/*
 * TSpiImplement.hpp
 *
 *  Created on: 07/04/2015
 *      Author: Gabriela
 */

#ifndef TSPIIMPLEMENT_HPP_
#define TSPIIMPLEMENT_HPP_

#pragma once

#include "../memorymap/MapSpi.hpp"
#include "../include/Spi.hpp"

#include "../include/Clock"

namespace Spi
{
	template<Spi::spiModule::_spiModule sSpiModule>
	void Spi::tSpi<sSpiModule>::enable()
	{
		reinterpret_cast<MapSpi::SpiRegs*>
			( sSpiModule )->SSICR1 |= 1 << 1;
	}

	template<Spi::spiModule::_spiModule sSpiModule>
	void Spi::tSpi<sSpiModule>::disable()
	{
		reinterpret_cast<MapSpi::SpiRegs*>
			( sSpiModule )->SSICR1 &= ( 0xff - 1 << 1 );
	}

	template<Spi::spiModule::_spiModule sSpiModule>
	void Spi::tSpi<sSpiModule>::configSpi( u8 sClockRateMHz,
								   	  	   Spi::config::mode::_mode sMode,
								   	       Spi::config::clockSource::_clockSource sClockSource,
								   	       Spi::config::clockPolarity::_clockPolarity sClockPolarity,
								   	       Spi::config::clockPhase::_clockPhase sClockPhase,
								   	       Spi::config::frameFormat::_frameFormat sFrameFormat,
								   	       Spi::config::dataSize::_dataSize sDataSize,
								   	       u8 sPreescaler )
	{
		tSpi<sSpiModule>::disable();

		// Set the operation mode
		reinterpret_cast<MapSpi::SpiRegs*>
			( sSpiModule )->SSICR1 = sMode;
		// Select the clock source
		reinterpret_cast<MapSpi::SpiRegs*>
			( sSpiModule )->SSICC = sClockSource;
		// Set the predivider
		reinterpret_cast<MapSpi::SpiRegs*>
			( sSpiModule )->SSICPSR = sPreescaler;
		// Calculate the clock rate
		volatile u32 scrClockRate = ( clock::Clock::CLOCK_RATE_MHZ / ( sPreescaler * sClockRateMHz ) ) - 1;
		reinterpret_cast<MapSpi::SpiRegs*>
			( sSpiModule )->SSICR0 = ( scrClockRate << 8 ) | ( sClockPolarity ) |
									 ( sClockPhase ) | ( sFrameFormat ) |
									 ( sDataSize );
									 
		tSpi<sSpiModule>::enable();
	}

	template<Spi::spiModule::_spiModule sSpiModule>
	void Spi::tSpi<sSpiModule>::sendByte( u8 sByte )
	{
		// Wait until there is at least one space available in the ...
		// ... transmit FIFO
		while( !( ( reinterpret_cast<MapSpi::SpiRegs*>
						( sSpiModule )->SSISR & 0x2 ) == 0x2 ) );

		reinterpret_cast<MapSpi::SpiRegs*>
			( sSpiModule )->SSIDR = u8 sByte;
	}

	template<Spi::spiModule::_spiModule sSpiModule>
	u8 Spi::tSpi<sSpiModule>::readByte()
	{
		// Wait until the receive FIFO has at least one byte of data
		while( !( ( reinterpret_cast<MapSpi::SpiRegs*>
							( sSpiModule )->SSISR & 0x4 ) == 0x4 ) );
		return reinterpret_cast<MapSpi::SpiRegs*>
				( sSpiModule )->SSIDR;
	}

	template<Spi::spiModule::_spiModule sSpiModule>
	bool Spi::tSpi<sSpiModule>::isBusy()
	{
		return ( reinterpret_cast<MapSpi::SpiRegs*>
				( sSpiModule )->SSISR & 0x10 ) == 0x10;
	}

	template<Spi::spiModule::_spiModule sSpiModule>
	bool Spi::tSpi<sSpiModule>::isReceiveFIFOempty()
	{
		return !( ( reinterpret_cast<MapSpi::SpiRegs*>
				( sSpiModule )->SSISR & 0x4 ) == 0x4 );
	}

	template<Spi::spiModule::_spiModule sSpiModule>
	bool Spi::tSpi<sSpiModule>::isReceiveFIFOnotEmpty()
	{
		return ( reinterpret_cast<MapSpi::SpiRegs*>
				( sSpiModule )->SSISR & 0x4 ) == 0x4;
	}

	template<Spi::spiModule::_spiModule sSpiModule>
	bool Spi::tSpi<sSpiModule>::isReceiveFIFOfull()
	{
		return ( reinterpret_cast<MapSpi::SpiRegs*>
				( sSpiModule )->SSISR & 0x8 ) == 0x8;
	}

	template<Spi::spiModule::_spiModule sSpiModule>
	bool Spi::tSpi<sSpiModule>::isTransmitFIFOempty()
	{
		return ( reinterpret_cast<MapSpi::SpiRegs*>
				( sSpiModule )->SSISR & 0x1 ) == 0x1;
	}

	template<Spi::spiModule::_spiModule sSpiModule>
	bool Spi::tSpi<sSpiModule>::isTransmitFIFOfull()
	{
		return !( ( reinterpret_cast<MapSpi::SpiRegs*>
				( sSpiModule )->SSISR & 0x2 ) == 0x2 );
	}

	template<Spi::spiModule::_spiModule sSpiModule>
	void Spi::tSpi<sSpiModule>::enableInterrupt( Spi::options::interrupts::_interrupts sInterrupt )
	{
		reinterpret_cast<MapSpi::SpiRegs*>
			( sSpiModule )->SSIIM |= 1 << sInterrupt;
	}

	template<Spi::spiModule::_spiModule sSpiModule>
	void Spi::tSpi<sSpiModule>::disableInterrupt( Spi::options::interrupts::_interrupts sInterrupt )
	{
		reinterpret_cast<MapSpi::SpiRegs*>
			( sSpiModule )->SSIIM &= ( 0xff - ( 1 << sInterrupt ) );
	}

	template<Spi::spiModule::_spiModule sSpiModule>
	void Spi::tSpi<sSpiModule>::clearInterrupt( Spi::options::interrupts::_interrupts sInterrupt )
	{
		// Be aware that, only the timeout and overflow interrupts are cleared by the user ...
		// ... using this register. The other 2 interrupts are cleared when the FIFOs are ...
		// ... written or read accordingly.
		reinterpret_cast<MapSpi::SpiRegs*>
			( sSpiModule )->SSIICR |= 1 << sInterrupt;
	}

	template<Spi::spiModule::_spiModule sSpiModule>
	bool Spi::tSpi<sSpiModule>::isInterruptAsserted( Spi::options::interrupts::_interrupts sInterrupt )
	{
		volatile u32 sMask = reinterpret_cast<MapSpi::SpiRegs*>
									( sSpiModule )->SSIMIS & ( 1 << sInterrupt );
		return ( sMask == ( 1 << sInterrupt ) );
	}
}

#endif /* TSPIIMPLEMENT_HPP_ */

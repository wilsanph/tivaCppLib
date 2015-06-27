/*
 * Spi.hpp
 *
 *  Created on: 07/04/2015
 *      Author: USER01
 * @brief: SPI module
 *
 *  ->The rx and tx paths are buffered, with ...
 *    ... up to 8 buffs of 16-bit values
 */

#ifndef SPI_HPP_
#define SPI_HPP_

#pragma once

#include "../GProjectCore/GObject.hpp"


namespace Spi
{
	namespace spiModule
	{
		enum _spiModule 
		{  
			SPI0 = 0x40008000,
			SPI1 = 0x40009000,
			SPI2 = 0x4000A000,
			SPI3 = 0x4000B000
		};
	}


	namespace config
	{
		namespace mode
		{
			enum _mode 
			{
				MASTER_MODE = 0x0,
				SLAVE_OUT_ENABLED = 0x4,
				SLAVE_OUT_DISABLED = 0xc
			};
		}

		namespace clockSource
		{
			enum _clockSource 
			{
				SYSTEM_CLOCK = 0x0,
				PIOSC_CLOCK	 = 0x5
			};
		}

		namespace clockPolarity
		{
			enum _clockPolarity 
			{
				IDLE_LOW	= 0x00,
				IDLE_HIGH 	= 0x40
			};
		}

		namespace clockPhase
		{
			enum _clockPhase 
			{
				CAPTURE_FIRST_EDGE 	= 0x00,
				CAPTURE_SECOND_EDGE = 0x80
			};
		}

		namespace frameFormat
		{
			enum _frameFormat 
			{
				FREESCALE_SPI_FORMAT 		= 0x00,
				TEXAS_INSTRUMENTS_FORMAT	= 0x10,
				MICROWIRE_FORMAT			= 0x20
			};
		}

		namespace dataSize
		{
			enum _dataSize 
			{
				BITS_4 = 0x03,
				BITS_5 = 0x04,
				BITS_6 = 0x05,
				BITS_7 = 0x06,
				BITS_8 = 0x07,
				BITS_9 = 0x08,
				BITS_10 = 0x09,
				BITS_11 = 0x0a,
				BITS_12 = 0x0b,
				BITS_13 = 0x0c,
				BITS_14 = 0x0d,
				BITS_15 = 0x0e,
				BITS_16 = 0x0f
			};
		}
	}

	namespace options
	{
		namespace interrupts
		{
			enum _interrupts
			{
				RECEIVE_OVERRUN_INTERRUPT = 0,
				RECEIVE_TIMEOUT_INTERRUPT = 1,
				RECEIVE_FIFO_INTERRUPT = 2,
				TRANSMIT_FIFO_INTERRUPT = 3
			};
		}
	}

	template<Spi::spiModule::_spiModule sSpiModule>
	class tSpi
	{
	public:
		inline static void enable();
		inline static void disable();

		inline static void configSpi( u8 sClockRateMHz,
								   	  config::mode::_mode sMode,
								   	  config::clockSource::_clockSource sClockSource,
								   	  config::clockPolarity::_clockPolarity sClockPolarity,
								   	  config::clockPhase::_clockPhase sClockPhase,
								   	  config::frameFormat::_frameFormat sFrameFormat,
								   	  config::dataSize::_dataSize sDataSize,
								   	  u8 sPreescaler );

		inline static void sendByte( u8 sByte );
		inline static u8 readByte();

		inline static bool isBusy();
		inline static bool isReceiveFIFOempty();
		inline static bool isReceiveFIFOnotEmpty();
		inline static bool isReceiveFIFOfull();
		inline static bool isTransmitFIFOempty();
		inline static bool isTransmitFIFOfull();

		inline static void enableInterrupt( options::interrupts::_interrupts sInterrupt );
		inline static void disableInterrupt( options::interrupts::_interrupts sInterrupt );
		inline static void clearInterrupt( options::interrupts::_interrupts sInterrupt );
		inline static bool isInterruptAsserted( options::interrupts::_interrupts sInterrupt );
	};

}

typedef Spi::tSpi<Spi::spiModule::SPI0> Spi0;
typedef Spi::tSpi<Spi::spiModule::SPI1> Spi1;
typedef Spi::tSpi<Spi::spiModule::SPI2> Spi2;
typedef Spi::tSpi<Spi::spiModule::SPI3> Spi3;


#include "../src/TSpiImplement.hpp"

#endif /* SPI_HPP_ */

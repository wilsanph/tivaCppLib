/*
 * Uart.hpp
 *
 *  Created on: 16/03/2015
 *      Author: USER01
 */

#ifndef UART_HPP_
#define UART_HPP_

#pragma once

#include "../GProjectCore/GObject.hpp"

namespace uart
{

	namespace uartModule
	{
		enum _uartModule {  
			UART0 = 0x4000c000,
			UART1 = 0x4000d000,
			UART2 = 0x4000e000,
			UART3 = 0x4000f000,
			UART4 = 0x40010000,
			UART5 = 0x40011000,
			UART6 = 0x40012000,
			UART7 = 0x40013000
		};
	}

	namespace config
	{
		namespace clockSource
		{
			enum _clockSource 
			{
				SYSTEM_CLOCK = 0x0,
				P_INTERNAL_CLOCK = 0x5
			};
		}

		namespace baudrate
		{
			enum _baudrate 
			{  
				BAUDS_9600   	= 9600,
				BAUDS_19200  	= 19200,
				BAUDS_38400  	= 38400,
				BAUDS_57600  	= 57600,
				BAUDS_115200 	= 115200,
				BAUDS_100000 	= 100000,
				BAUDS_230400 	= 230400,
				BAUDS_921600 	= 921600,
				BAUDS_1000000	= 1000000,
				BAUDS_3000000	= 3000000
			};
		}

		namespace nBits
		{
			enum _nBits 
			{  
				BITS_8 = 0x03,
				BITS_7 = 0x02,
				BITS_6 = 0x01,
				BITS_5 = 0x00
			};
		}

		namespace parity
		{
			enum _parity
			{
				NONE = 0,
				ODD  = 1,
				EVEN = 3
			};
		}
		namespace stopbits
		{
			enum _stopbits
			{
				STOPBITS_ONE = 0,
				STOPBITS_TWO = 1
			};
		}

		namespace interrupts
		{
			enum _interrupts
			{
				NONE				= 0,
				RECEIVE_INT 		= 16,
				TRANSMIT_INT		= 32,
				RECEIVE_TIMEOUT		= 64
			};
		}

		namespace fifo
		{
			enum _fifo {  
				FIFO_ENABLED  = 1,
				FIFO_DISABLED = 0
			};
		}

		namespace dma
		{
			enum _dma
			{
				DMA_TX_ENABLED = 2,
				DMA_RX_ENABLED = 1
			};
		}
	}

	class Uart : public gObject::GObject
	{
	public:
		Uart();
		Uart( uartModule::_uartModule uUARTModule );

		static u32 UART_CLOCK;

		void init();

		/**
		* @brief Enabled the UART module
		*/
		void enableUart();

		/**
		* @brief Disables the UART module
		*/
		void disableUart();

		void configUart( config::baudrate::_baudrate uBaudRate = config::baudrate::BAUDS_115200,
			  			 config::nBits::_nBits uNBits = config::nBits::BITS_8,
			  			 config::parity::_parity uParity = config::parity::NONE ,
			  			 config::stopbits::_stopbits uStopbits = config::stopbits::STOPBITS_ONE,
			  			 u32 uInterrupts = config::interrupts::RECEIVE_INT,
			  			 config::fifo::_fifo uFifo = config::fifo::FIFO_DISABLED,
			  			 config::clockSource::_clockSource uClockSource = config::clockSource::SYSTEM_CLOCK );

		/**
		* @param {u32} uDMAOptions : the udma options joint in a u32 var.
		*/
		void enableDMA( u32 uDMAOptions );

		/**
		* @param {u8} byte : a single byte to be sent
		*/
		void send( u8 byte );

		/**
		* @param {const char*} uString : a const pointer to the string
		* @return {u16} characters in the string
		*/
		u16 sendString( const char* uString );

		/**
		* @return {u8} byte : a single byte read from the UART RX buffer
		*/
		u8 read();

		/**
		* @brief Clears the interrupts given in the joint var. uInterrupts
		* @param {u32} uInterrupts : joint var. that contains the interrupts to be cleared
		*/
		void clearInterrupts( u32 uInterrupts );

		/**
		* @brief Returns true if the given interrupt has been asserted
		* @param {config::interrupts::_interrupts} uInterrupt
		* @return {bool}
		*/		
		bool isInterruptAsserted( config::interrupts::_interrupts uInterrupt );

	protected:
		uartModule::_uartModule m_uartMod;
	};

	template<uart::uartModule::_uartModule tUartModule>
	class tUart
	{
		static u32 UART_CLOCK;

		static inline void enable();
		static inline void disable();

		static inline void config( config::baudrate::_baudrate uBaudRate = config::baudrate::BAUDS_115200,
			  			 		   config::nBits::_nBits uNBits = config::nBits::BITS_8,
			  			 		   config::parity::_parity uParity = config::parity::NONE ,
			  			 		   config::stopbits::_stopbits uStopbits = config::stopbits::STOPBITS_ONE,
			  			 		   u32 uInterrupts = config::interrupts::RECEIVE_INT,
			  			 		   config::fifo::_fifo uFifo = config::fifo::FIFO_DISABLED,
			  			 		   config::clockSource::_clockSource uClockSource = config::clockSource::SYSTEM_CLOCK );

		static inline void enableDMA( u32 uDMAOptions );

		static inline void send( u8 uByte );
		static inline u16 sendString( const char* uString );
		static inline u8 read();
		static inline void clearInterrupts( u32 uInterrupts );
		static inline bool isInterruptAsserted( config::interrupts::_interrupts uInterrupt );

	};

}

typedef uart::tUart<uart::uartModule::UART0> tUART0;
typedef uart::tUart<uart::uartModule::UART1> tUART1;
typedef uart::tUart<uart::uartModule::UART2> tUART2;
typedef uart::tUart<uart::uartModule::UART3> tUART3;
typedef uart::tUart<uart::uartModule::UART4> tUART4;
typedef uart::tUart<uart::uartModule::UART5> tUART5;
typedef uart::tUart<uart::uartModule::UART6> tUART6;
typedef uart::tUart<uart::uartModule::UART7> tUART7;


#include "../src/UartImplement.hpp"

#endif /* UART_HPP_ */

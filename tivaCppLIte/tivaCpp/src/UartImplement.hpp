/*
 * UartImplement.hpp
 *
 *  Created on: 16/03/2015
 *      Author: USER01
 */

#ifndef UARTIMPLEMENT_HPP_
#define UARTIMPLEMENT_HPP_

#pragma once

#include "../memorymap/MapUart.hpp"
#include "../include/Uart.hpp"
#include "../include/Clock.hpp"
#include <string>

namespace uart
{

	u32 uart::Uart::UART_CLOCK = 80000000;

	uart::Uart::Uart()
	{
		this->objID = gObject::ObjectIDs::OBJ_ID_UART;
		this->m_uartMod  = uart::uartModule::UART0;
	}

	uart::Uart::Uart( uartModule::_uartModule uUARTModule )
	{
		this->objID = gObject::ObjectIDs::OBJ_ID_UART;
		this->m_uartMod  = uUARTModule;
	}

	void uart::Uart::init()
	{
		// TODO: Add extra code here
	}

	
	void uart::Uart::disableUart()
	{
		reinterpret_cast<MapUart::UartRegs *>
			( this->m_uartMod )->UARTCTL &= 0xfffe;
	}
	
	void uart::Uart::enableUart()
	{
		reinterpret_cast<MapUart::UartRegs *>
			( this->m_uartMod )->UARTCTL |= 0x0001;
	}

	void uart::Uart::configUart( config::baudrate::_baudrate uBaudRate,
			  					 config::nBits::_nBits uNBits ,
			  					 config::parity::_parity uParity ,
			  					 config::stopbits::_stopbits uStopbits ,
			  					 u32 uInterrupts ,
			  					 config::fifo::_fifo uFifo ,
			  					 config::clockSource::_clockSource uClockSource )
	{
		volatile u32 brdInt,brdFrc;
		volatile float uTemp;
		uTemp = ( ( float )( uart::Uart::UART_CLOCK ) ) / ( 16 * uBaudRate );
		brdInt = ( u32 ) uTemp;
		brdFrc = ( u32 ) ( ( uTemp - brdInt ) * 64 + 0.5 );
		reinterpret_cast<MapUart::UartRegs *>
			( this->m_uartMod )->UARTCTL &= 0xfffe;
		reinterpret_cast<MapUart::UartRegs *>
			( this->m_uartMod )->UARTIBRD = brdInt;
		reinterpret_cast<MapUart::UartRegs *>
			( this->m_uartMod )->UARTFBRD = brdFrc;
		reinterpret_cast<MapUart::UartRegs *>
			( this->m_uartMod )->UARTLCRH = ( uNBits << 5 ) | ( uFifo << 4 ) |
											( uStopbits << 3 ) | ( uParity << 1 );
		reinterpret_cast<MapUart::UartRegs *>
			( this->m_uartMod )->UARTCC = uClockSource;
		reinterpret_cast<MapUart::UartRegs *>
			( this->m_uartMod )->UARTIM = uInterrupts;
		reinterpret_cast<MapUart::UartRegs *>
			( this->m_uartMod )->UARTIFLS = ( 0x1 << 0 ) | ( 0x0 << 3 );
		reinterpret_cast<MapUart::UartRegs *>
			( this->m_uartMod )->UARTCTL |= 1;
	}
	
	void uart::Uart::enableDMA( u32 uDMAOptions )
	{
		reinterpret_cast<MapUart::UartRegs *>
			( this->m_uartMod )->UARTDMACTL = uDMAOptions;
	}
	
	void uart::Uart::send( u8 byte )
	{
		// Use pooling to check if there is no pending send
		// TODO: Can change this part by using interrupts, and a IsReady flag
		volatile u32 uartFlReg = 0;

		while( true )
		{
			uartFlReg = reinterpret_cast< MapUart::UartRegs * >
							( this->m_uartMod )->UARTFR;
			if ( ( uartFlReg & 0x20 ) != 0x20 )
			{
				break;//THIS WORKS!!!
			}
		}
		reinterpret_cast<MapUart::UartRegs *>
			( this->m_uartMod )->UARTDR = byte;
	}
	
	u16 uart::Uart::sendString( const char* uString )
	{
		volatile u16 i = 0;
		volatile u16 size = std::strlen( uString );
		for( i = 0 ; i < size ; i++ )
		{
			this->send( *uString );
			uString++;
		}
		return size;
	}
	
	u8 uart::Uart::read()
	{
		return reinterpret_cast< MapUart::UartRegs * >( this->m_uartMod )->UARTDR;
	}
	
	void uart::Uart::clearInterrupts( u32 uInterrupts )
	{
		reinterpret_cast<MapUart::UartRegs *>
			( this->m_uartMod )->UARTICR |= uInterrupts;
	}
	
	bool uart::Uart::isInterruptAsserted( config::interrupts::_interrupts uInterrupt )
	{
		//check masked interrupt status...
		return ( (reinterpret_cast<MapUart::UartRegs *>
					( this->m_uartMod )->UARTMIS ) & uInterrupt == uInterrupt );
	}


	/**
	* Template implementation
	*/
	template<uart::uartModule::_uartModule tUartModule>
	u32 uart::tUart<tUartModule>::UART_CLOCK = 80000000;

	template<uart::uartModule::_uartModule tUartModule>
	void uart::tUart<tUartModule>::disable()
	{
		reinterpret_cast<MapUart::UartRegs *>
			( tUartModule )->UARTCTL &= 0xfffe;
	}

	template<uart::uartModule::_uartModule tUartModule>
	void uart::tUart<tUartModule>::enable()
	{
		reinterpret_cast<MapUart::UartRegs *>
			( tUartModule )->UARTCTL |= 0x0001;
	}

	template<uart::uartModule::_uartModule tUartModule>
	void uart::tUart<tUartModule>::config( config::baudrate::_baudrate uBaudRate,
			  				 config::nBits::_nBits uNBits ,
			  				 config::parity::_parity uParity ,
			  				 config::stopbits::_stopbits uStopbits ,
			  				 u32 uInterrupts ,
			  				 config::fifo::_fifo uFifo ,
			  				 config::clockSource::_clockSource uClockSource )
	{
		volatile u32 brdInt,brdFrc;
		volatile float uTemp;
		uTemp = ( ( float )( uart::tUart::UART_CLOCK ) ) / ( 16 * uBaudRate );
		brdInt = ( u32 ) uTemp;
		brdFrc = ( u32 ) ( ( uTemp - brdInt ) * 64 + 0.5 );
		reinterpret_cast<MapUart::UartRegs *>
			( tUartModule )->UARTCTL &= 0xfffe;
		reinterpret_cast<MapUart::UartRegs *>
			( tUartModule )->UARTIBRD = brdInt;
		reinterpret_cast<MapUart::UartRegs *>
			( tUartModule )->UARTFBRD = brdFrc;
		reinterpret_cast<MapUart::UartRegs *>
			( tUartModule )->UARTLCRH = ( uNBits << 5 ) | ( uFifo << 4 ) |
											( uStopbits << 3 ) | ( uParity << 1 );
		reinterpret_cast<MapUart::UartRegs *>
			( tUartModule )->UARTCC = uClockSource;
		reinterpret_cast<MapUart::UartRegs *>
			( tUartModule )->UARTIM = uInterrupts;
		reinterpret_cast<MapUart::UartRegs *>
			( tUartModule )->UARTIFLS = ( 0x1 << 0 ) | ( 0x0 << 3 );
		reinterpret_cast<MapUart::UartRegs *>
			( tUartModule )->UARTCTL |= 1;
	}

	template<uart::uartModule::_uartModule tUartModule>
	void uart::tUart<tUartModule>::enableDMA( u32 uDMAOptions )
	{
		reinterpret_cast<MapUart::UartRegs *>
			( tUartModule )->UARTDMACTL = uDMAOptions;
	}

	template<uart::uartModule::_uartModule tUartModule>
	void uart::tUart<tUartModule>::send( u8 byte )
	{
		// Use pooling to check if there is no pending send
		// TODO: Can change this part by using interrupts, and a IsReady flag
		volatile u32 uartFlReg = 0;

		while( true )
		{
			uartFlReg = reinterpret_cast< MapUart::UartRegs * >
							( tUartModule )->UARTFR;
			if ( ( uartFlReg & 0x20 ) != 0x20 )
			{
				break;//THIS WORKS!!!
			}
		}
		reinterpret_cast<MapUart::UartRegs *>
			( tUartModule )->UARTDR = byte;
	}
	template<uart::uartModule::_uartModule tUartModule>
	u16 uart::tUart<tUartModule>::sendString( const char* uString )
	{
		volatile u16 i = 0;
		volatile u16 size = std::strlen( uString );
		for( i = 0 ; i < size ; i++ )
		{
			tUart<tUartModule>::send( *uString );
			uString++;
		}
		return size;
	}
	template<uart::uartModule::_uartModule tUartModule>
	u8 uart::tUart<tUartModule>::read()
	{
		return reinterpret_cast< MapUart::UartRegs * >( tUartModule )->UARTDR;
	}
	template<uart::uartModule::_uartModule tUartModule>
	void uart::tUart<tUartModule>::clearInterrupts( u32 uInterrupts )
	{
		reinterpret_cast<MapUart::UartRegs *>
			( tUartModule )->UARTICR |= uInterrupts;
	}
	template<uart::uartModule::_uartModule tUartModule>
	bool uart::tUart<tUartModule>::isInterruptAsserted( config::interrupts::_interrupts uInterrupt )
	{
		//check masked interrupt status...
		return ( (reinterpret_cast<MapUart::UartRegs *>
					( tUartModule )->UARTMIS ) & uInterrupt == uInterrupt );
	}
}

#endif /* UARTIMPLEMENT_HPP_ */

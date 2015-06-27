#include "tivaCpp/include/Clock.hpp"
#include "tivaCpp/include/Gpio.hpp"
#include "tivaCpp/include/Timer.hpp"

#include "tivaCppLibrary/delays.hpp"

clock::Clock systemClock;

Gpio::Pin blueLed( Gpio::port::GPIOPortF_APB, Gpio::pin::pin2 );

int main()
{
	systemClock.config( clock::config::clockSource::mainOscilator,
						clock::config::clockRate::clock_80Mhz );

	// Enable GPIOF-APB clock
	systemClock.enableGpioClock( clock::peripheral::gpio::GPIOF,
								 clock::config::gpioBusType::APBbus );

	blueLed.enableDigitalFunc();
	blueLed.setMode( Gpio::config::mode::gpio );
	blueLed.setIOMode( Gpio::config::ioMode::output );

	while( 1 )
	{
		blueLed.toggle();

		delays::delay_ms( 100 );
	}
}

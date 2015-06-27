/*
 * I2c.hpp
 *
 *  Created on: 12/04/2015
 *      Author: USER01
 */

#ifndef I2C_HPP_
#define I2C_HPP_

#pragma once

#include "../GProjectCore/GObject.hpp"

namespace i2c
{
	namespace module
	{
		enum _module 
		{
			I2C0 = 0x40020000,
			I2C1 = 0x40021000,
			I2C2 = 0x40022000,
			I2C3 = 0x40023000
		};
	}

	namespace options
	{
		namespace rw
		{
			enum _rw 
			{
				READ = 1,
				WRITE = 0
			};
		}
	}

	namespace config
	{
		namespace mode
		{
			enum _mode
			{
				MASTER = 1,
				SLAVE = 2
			};
		}

		namespace loopback
		{
			enum _loopback
			{
				DISABLED = 0,
				ENABLED = 1
			};
		}

		namespace speed
		{
			enum _speed
			{
				MODE_STANDARD = 100000,
				MODE_FAST = 400000,
				MODE_FASTPLUS = 1000000
			};
		}

		namespace operation
		{
			enum _operation
			{
				RUN_MASTER_ENABLE = 0x01,
				START_CONDITION = 0x02,
				STOP_CONDITION = 0x04,
				GENERATE_ACK = 0x08
			};
		}
	}

	template<i2c::module::_module iI2cModule>
	class tI2c
	{
	public:

		static inline void writeSlaveAddress( u8 iAddress,
											  i2c::options::rw::_rw iRw );
		static inline void configSpeed();
	};
}



#endif /* I2C_HPP_ */

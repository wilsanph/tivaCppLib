/*
 * MapI2c.hpp
 *
 *  Created on: 12/04/2015
 *      Author: USER01
 */

#ifndef MAPI2C_HPP_
#define MAPI2C_HPP_

#include "../common.hpp"

namespace MapI2c
{
	struct I2cRegs
	{
		u32 I2CMSA;//0x0000
		u32 I2CMCS;//0x0004
		u32 I2CMDR;//0x0008
		u32 I2CMTPR;//0x000c
		u32 I2CMIMR;//0x0010
		u32 I2CMRIS;//0x0014
		u32 I2CMMIS;//0x0018
		u32 I2CMICR;//0x001c
		u32 I2CMCR;//0x0020
		u32 I2CMCLKOCNT;//0x0024
		u32 reserved1[1];
		u32 I2CMBMON;//0x002c
	};
}



#endif /* MAPI2C_HPP_ */

/*
 * MapQei.hpp
 *
 *  Created on: 18/03/2015
 *      Author: USER01
 */

#ifndef MAPQEI_HPP_
#define MAPQEI_HPP_

#include "../common.hpp"

namespace MapQei
{
	struct QeiRegs
	{
		u32 QEICTL;
		u32 QEISTAT;
		u32 QEIPOS;
		u32 QEIMAXPOS;
		u32 QEILOAD;
		u32 QEITIME;
		u32 QEICOUNT;
		u32 QEISPEED;
		u32 QEIINTEN;
		u32 QEIRIS;
		u32 QEIISC;
	};
}


#endif /* MAPQEI_HPP_ */

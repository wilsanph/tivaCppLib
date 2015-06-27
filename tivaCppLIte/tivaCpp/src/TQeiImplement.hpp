/*
 * TQeiImplement.hpp
 *
 *  Created on: 06/06/2015
 *      Author: WilSan
 */

#ifndef TQEIIMPLEMENT_HPP_
#define TQEIIMPLEMENT_HPP_

#pragma once

#include "../memorymap/MapQei.hpp"
#include "../include/Qei.hpp"

namespace qei
{
	template<qeiModule::_qeiModule tQeiModule>
	void qei::Qei<tQeiModule>::configQei( 
							  qei::config::stallOnDebugger::_stallOnDebugger qStall,
							  qei::config::velocityPredivider::_velocityPredivider qVeldiv,
							  qei::config::capVelocity::_capVelocity qCapVel,
							  qei::config::captureMode::_captureMode qCapmode )
	{
		reinterpret_cast<MapQei::QeiRegs*>
			( tQeiModule )->QEICTL = ( qStall << 12 ) |
											( qVeldiv << 6 ) | 
											( qCapVel << 5 ) |
											( qCapmode << 3 );
		reinterpret_cast<MapQei::QeiRegs*>
			( tQeiModule )->QEIMAXPOS = 0xffffffff;
	}

	template<qeiModule::_qeiModule tQeiModule>
	void qei::Qei<tQeiModule>::setTimer( u32 qTimerValue )
	{
		reinterpret_cast<MapQei::QeiRegs*>
			( tQeiModule )->QEILOAD = qTimerValue;
	}

	template<qeiModule::_qeiModule tQeiModule>
	void qei::Qei<tQeiModule>::enableQei()
	{
		reinterpret_cast<MapQei::QeiRegs*>
			( tQeiModule )->QEICTL |= 1;
	}

	template<qeiModule::_qeiModule tQeiModule>
	u32 qei::Qei<tQeiModule>::getCountReg()
	{
		return reinterpret_cast<MapQei::QeiRegs*>
					( tQeiModule )->QEIPOS;
	}

	template<qeiModule::_qeiModule tQeiModule>
	u32 qei::Qei<tQeiModule>::getSpeedReg()
	{
		return reinterpret_cast<MapQei::QeiRegs*>
					( tQeiModule )->QEISPEED;
	}

}

#endif /* TQEIIMPLEMENT_HPP_ */

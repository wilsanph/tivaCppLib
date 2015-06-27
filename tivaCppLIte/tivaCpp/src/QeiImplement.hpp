/*
 * QeiImplement.hpp
 *
 *  Created on: 18/03/2015
 *      Author: USER01
 */

#ifndef QEIIMPLEMENT_HPP_
#define QEIIMPLEMENT_HPP_

#pragma once

#include "../memorymap/MapQei.hpp"
#include "../include/Qei.hpp"

namespace qei
{
	
	qei::Qei::Qei()
	{
		this->m_qeiModule = qei::qeiModule::QEI0;
	}

	qei::Qei::Qei( qei::qeiModule::_qeiModule qQeiModule )
	{
		this->m_qeiModule = qQeiModule;
	}

	void qei::Qei::init()
	{
		// TODO: Add extra code here
	}

	void qei::Qei::configQei( qei::config::stallOnDebugger::_stallOnDebugger qStall,
							  qei::config::velocityPredivider::_velocityPredivider qVeldiv,
							  qei::config::capVelocity::_capVelocity qCapVel,
							  qei::config::captureMode::_captureMode qCapmode )
	{
		reinterpret_cast<MapQei::QeiRegs*>
			( this->m_qeiModule )->QEICTL = ( qStall << 12 ) |
											( qVeldiv << 6 ) | 
											( qCapVel << 5 ) |
											( qCapmode << 3 );
		reinterpret_cast<MapQei::QeiRegs*>
			( this->m_qeiModule )->QEIMAXPOS = 0xffffffff;
	}

	void qei::Qei::setTimer( u32 qTimerValue )
	{
		reinterpret_cast<MapQei::QeiRegs*>
			( this->m_qeiModule )->QEILOAD = qTimerValue;
	}

	void qei::Qei::enableQei()
	{
		reinterpret_cast<MapQei::QeiRegs*>
			( this->m_qeiModule )->QEICTL |= 1;
	}

	u32 qei::Qei::getCount()
	{
		return reinterpret_cast<MapQei::QeiRegs*>
					( this->m_qeiModule )->QEIPOS;
	}

	u32 qei::Qei::getSpeedReg()
	{
		return reinterpret_cast<MapQei::QeiRegs*>
					( this->m_qeiModule )->QEISPEED;
	}

}

#endif /* QEIIMPLEMENT_HPP_ */

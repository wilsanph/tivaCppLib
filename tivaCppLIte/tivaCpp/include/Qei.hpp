/*
 * Qei.hpp
 *
 *  Created on: 18/03/2015
 *      Author: USER01
 */

#ifndef QEI_HPP_
#define QEI_HPP_

#pragma once

#include "../GProjectCore/GObject.hpp"

namespace qei
{
	
	namespace qeiModule
	{
		enum _qeiModule
		{
			QEI0 = 0x4002c000,
			QEI1 = 0x4002d000
		};
	}


	namespace config
	{
		namespace velocityPredivider
		{
			enum _velocityPredivider
			{
				DIV_1	= 0,
				DIV_2	= 1,
				DIV_4	= 2,
				DIV_8	= 3,
				DIV_16	= 4,
				DIV_32	= 5,
				DIV_64	= 6,
				DIV_128	= 7
			};
		}

		namespace stallOnDebugger
		{
			enum _stallOnDebugger
			{
				DONT_STALL 	= 0,
				STALL 		= 1
			};
		}

		namespace capVelocity
		{
			enum _capVelocity
			{
				CAPTURE_VEL 		= 1,
				DONT_CAPTURE_VEL	= 0
			};
		}

		namespace captureMode
		{
			enum _captureMode
			{
				MODE1 = 0,
				MODE2 = 1
			};
		}
	}

	class Qei : public gObject::GObject
	{

	public:
		Qei();
		Qei( qeiModule::_qeiModule qQeiModule );

		void init();

		void configQei( config::stallOnDebugger::_stallOnDebugger qStall,
						config::velocityPredivider::_velocityPredivider qVeldiv,
						config::capVelocity::_capVelocity qCapVel,
						config::captureMode::_captureMode qCapmode );

		void setTimer( u32 qTimerValue );
		void enableQei();
		u32 getCount();
		u32 getSpeedReg();

	private:
		qeiModule::_qeiModule m_qeiModule;
	};


	template<qeiModule::_qeiModule tQeiModule>
	class tQei
	{
		inline void configQei( config::stallOnDebugger::_stallOnDebugger qStall,
							   config::velocityPredivider::_velocityPredivider qVeldiv,
							   config::capVelocity::_capVelocity qCapVel,
							   config::captureMode::_captureMode qCapmode );
		inline void setTimer( u32 tTimerValue );
		inline void enableQei();
		inline u32 getCountReg();
		inline u32 getSpeedReg();
	};
}

#include "../src/QeiImplement.hpp"
#include "../src/TQeiImplement.hpp"

#endif /* QEI_HPP_ */

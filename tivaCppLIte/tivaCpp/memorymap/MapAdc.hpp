/*
 * MapAdc.hpp
 *
 *  Created on: 27/06/2015
 *      Author: Gabriela
 */

#ifndef MAPADC_HPP_
#define MAPADC_HPP_

#include "../common.hpp"

namespace MapAdc
{

	struct AdcRegs{
		u32 ADCACTSS;//0x0000
		u32 ADCRIS;//0x0004
		u32 ADCIM;//0x0008
		u32 ADCISC;//0x000c
		u32 ADCOSTAT;//0x0010
		u32 ADCEMUX;//0x0014
		u32 ADCUSTAT;//0x0018
		u32 reserved1[1];//[0x001c]
		u32 ADCSSPRI;//0x0020
		u32 ADCSPC;//0x0024
		u32 ADCPSSI;//0x0028
		u32 reserved2[1];//[0x002c]
		u32 ADCSAC;//0x0030
		u32 ADCDCISC;//0x0034
		u32 ADCCTL;//0x0038
		u32 reserved3[1];//0x003c
		u32 ADCSSMUX0;//0x0040
		u32 ADCSSCTL0;//0x0044
		u32 ADCSSFIFO0;//0x0048
		u32 ADCSSFSTAT0;//0x004c
		u32 ADCSSOP0;//0x0050
		u32 ADCSSDC0;//0x0054
		u32 reserved4[2];//[0x0058-0x005c]
		u32 ADCSSMUX1;//0x0060
		u32 ADCSSCTL1;//0x0064
		u32 ADCSSFIFO1;//0x0068
		u32 ADCSSFSTAT1;//0x006c
		u32 ADCSSOP1;//0x0070
		u32 ADCSSDC1;//0x0074
		u32 reserved5[2];//[0x0078-0x007c]
		u32 ADCSSMUX2;//0x0080
		u32 ADCSSCTL2;//0x0084
		u32 ADCSSFIFO2;//0x0088
		u32 ADCSSFSTAT2;//0x008c
		u32 ADCSSOP2;//0x0090
		u32 ADCSSDC2;//0x0094
		u32 reserved6[2];//[0x0098-0x009c]
		u32 ADCSSMUX3;//0x00a0
		u32 ADCSSCTL3;//0x00a4
		u32 ADCSSFIFO3;//0x00a8
		u32 ADCSSFSTAT3;//0x00ac
		u32 ADCSSOP3;//0x00b0
		u32 ADCSSDC3;//0x00b4
		u32 reserved7[786];//[0x00b8-0x0cfc]
		u32 ADCDCRIC;//0x0d00
		u32 reserved8[63];//[0x0d04-0x0dfc]
		u32 ADCDCCTL0;//0x0e00
		u32 ADCDCCTL1;//0x0e04
		u32 ADCDCCTL2;//0x0e08
		u32 ADCDCCTL3;//0x0e0c
		u32 ADCDCCTL4;//0x0e10
		u32 ADCDCCTL5;//0x0e14
		u32 ADCDCCTL6;//0x0e18
		u32 ADCDCCTL7;//0x0e1c
		u32 reserved9[8];//[0x0e20-0x0e3c]
		u32 ADCDCCMP0;//0x0e40
		u32 ADCDCCMP1;//0x0e44
		u32 ADCDCCMP2;//0x0e48
		u32 ADCDCCMP3;//0x0e4c
		u32 ADCDCCMP4;//0x0e50
		u32 ADCDCCMP5;//0x0e54
		u32 ADCDCCMP6;//0x0e58
		u32 ADCDCCMP7;//0x0e5c
		u32 reserved10[87];//[0x0e60-0x0fbc]
		u32 ADCPP;//0x0fc0
		u32 ADCPC;//0x0fc4
		u32 ADCCC;//0x0fc8
	};

}


#endif /* MAPADC_HPP_ */
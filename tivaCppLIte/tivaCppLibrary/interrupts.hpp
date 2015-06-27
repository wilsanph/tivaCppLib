/*
 * interrupts.h
 *
 *  Created on: 01/07/2013
 *      Author: wilbert
 */


#define mpuLib


namespace interruptFuncs{
	extern "C"{
		void stackTop();
		void reset_isr();
		void nmi_isr();
		void fault_isr();
		void mpuFault_isr();
		void busFault_isr();
		void usageFault_isr();
		void reserved_1_1();
		void reserved_1_2();
		void reserved_1_3();
		void reserved_1_4();
		void svCall_isr();
		void debugMonitor_isr();
		void reserved_2_1();
		void pendSV_isr();
		void sysTick_isr();
		void gpioA_isr();
		void gpioB_isr();
		void gpioC_isr();
		void gpioD_isr();
		void gpioE_isr();
		void uart0rxtx_isr();
		void uart1rxtx_isr();
		void ssi0rxtx_isr();
		void i2c0masterSlave_isr();
		void pwmFault_isr();
		void pwm0_isr();
		void pwm1_isr();
		void pwm2_isr();
		void quadEnc0_isr();
		void adcSeq0_isr();
		void adcSeq1_isr();
		void adcSeq2_isr();
		void adcSeq3_isr();
		void watchdogTimer_isr();
		void timer0SubA_isr();
		void timer0SubB_isr();
		void timer1SubA_isr();
		void timer1SubB_isr();
		void timer2SubA_isr();
		void timer2SubB_isr();
		void analogComparator0_isr();
		void analogComparator1_isr();
		void analogComparator2_isr();
		void sysCtrl_isr();
		void flashCtrl_isr();
		void gpioF_isr();
		void gpioG_isr();
		void gpioH_isr();
		void uart2rxtx_isr();
		void ssi1rxtx_isr();
		void timer3SubA_isr();
		void timer3SubB_isr();
		void i2c1masterSlave_isr();
		void quadEnc1_isr();
		void can0_isr();
		void can1_isr();
		void can2_isr();
		void ethernet_isr();
		void hibernate_isr();
		void usb0_isr();
		void pwm3_isr();
		void uDMAsofTransfer_isr();
		void uDMAerror_isr();
		void adc_1_Seq0_isr();
		void adc_1_Seq1_isr();
		void adc_1_Seq2_isr();
		void adc_1_Seq3_isr();
		void i2s0_isr();
		void extBusInterface_isr();
		void gpioJ_isr();
		void gpioK_isr();
		void gpioL_isr();
		void ssi2rxtx_isr();
		void ssi3rxtx_isr();
		void uart3rxtx_isr();
		void uart4rxtx_isr();
		void uart5rxtx_isr();
		void uart6rxtx_isr();
		void uart7rxtx_isr();
		void reserver_3_1();
		void reserver_3_2();
		void reserver_3_3();
		void reserver_3_4();
		void i2c2masterSlave_isr();
		void i2c3masterSlave_isr();
		void timer4SubA_isr();
		void timer4SubB_isr();
		void reserver_4_1();
		void reserver_4_2();
		void reserver_4_3();
		void reserver_4_4();
		void reserver_4_5();
		void reserver_4_6();
		void reserver_4_7();
		void reserver_4_8();
		void reserver_4_9();
		void reserver_4_10();
		void reserver_4_11();
		void reserver_4_12();
		void reserver_4_13();
		void reserver_4_14();
		void reserver_4_15();
		void reserver_4_16();
		void reserver_4_17();
		void reserver_4_18();
		void reserver_4_19();
		void reserver_4_20();
		void timer5SubA_isr();
		void timer5SubB_isr();
		void timer0WideA_isr();
		void timer0WideB_isr();
		void timer1WideA_isr();
		void timer1WideB_isr();
		void timer2WideA_isr();
		void timer2WideB_isr();
		void timer3WideA_isr();
		void timer3WideB_isr();
		void timer4WideA_isr();
		void timer4WideB_isr();
		void timer5WideA_isr();
		void timer5WideB_isr();
		void fpu_isr();
		void peci0_isr();
		void lpc0_isr();
		void i2c4masterSlave_isr();
		void i2c5masterSlave_isr();
		void gpioM_isr();
		void gpioN_isr();
		void quadEnc2_isr();
		void fan0_isr();
		void reserved_5_1();
		void gpioP_isr();
		void gpioP1_isr();
		void gpioP2_isr();
		void gpioP3_isr();
		void gpioP4_isr();
		void gpioP5_isr();
		void gpioP6_isr();
		void gpioP7_isr();
		void gpioQ_isr();
		void gpioQ1_isr();
		void gpioQ2_isr();
		void gpioQ3_isr();
		void gpioQ4_isr();
		void gpioQ5_isr();
		void gpioQ6_isr();
		void gpioQ7_isr();
		void gpioR_isr();
		void gpioS_isr();
		void pwm_1_0_isr();
		void pwm_1_1_isr();
		void pwm_1_2_isr();
		void pwm_1_3_isr();
		void pwm_1_Fault_isr();
	}
}





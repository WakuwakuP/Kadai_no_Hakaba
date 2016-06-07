/***********************************************************************/
/*                                                                     */
/*  FILE        :intprg.c                                              */
/*  DATE        :Tue, May 31, 2016                                     */
/*  DESCRIPTION :Interrupt Program                                     */
/*  CPU TYPE    :H8/3687                                               */
/*                                                                     */
/***********************************************************************/
                  


#include <machine.h>
#pragma section IntPRG
//  vector 1 Reserved

//  vector 2 Reserved

//  vector 3 Reserved

//  vector 4 Reserved

//  vector 5 Reserved

//  vector 6 Reserved

//  vector 7 NMI
__interrupt(vect=7) void INT_NMI(void) {/* sleep(); */}
//  vector 8 TRAP #0
__interrupt(vect=8) void INT_TRAP0(void) {/* sleep(); */}
//  vector 9 TRAP #1
__interrupt(vect=9) void INT_TRAP1(void) {/* sleep(); */}
//  vector 10 TRAP #2
__interrupt(vect=10) void INT_TRAP2(void) {/* sleep(); */}
//  vector 11 TRAP #3
__interrupt(vect=11) void INT_TRAP3(void) {/* sleep(); */}
//  vector 12 Address break
__interrupt(vect=12) void INT_ABRK(void) {/* sleep(); */}
//  vector 13 SLEEP
__interrupt(vect=13) void INT_SLEEP(void) {/* sleep(); */}
//  vector 14 IRQ0
__interrupt(vect=14) void INT_IRQ0(void) {
	IRQ0();
}
//  vector 15 IRQ1
__interrupt(vect=15) void INT_IRQ1(void) {
	IRQ1();
}
//  vector 16 IRQ2
__interrupt(vect=16) void INT_IRQ2(void) {
	IRQ2();
}
//  vector 17 IRQ3
__interrupt(vect=17) void INT_IRQ3(void) {
	IRQ3();
}
//  vector 18 WKP
__interrupt(vect=18) void INT_WKP(void) {/* sleep(); */}
//  vector 19 RTC
__interrupt(vect=19) void INT_RTC(void) {/* sleep(); */}
//  vector 20 Reserved

//  vector 21 Reserved

//  vector 22 Timer V
__interrupt(vect=22) void INT_TimerV(void) {/* sleep(); */}
//  vector 23 SCI3
__interrupt(vect=23) void INT_SCI3(void) {/* sleep(); */}
//  vector 24 IIC2
__interrupt(vect=24) void INT_IIC2(void) {/* sleep(); */}
//  vector 25 ADI
__interrupt(vect=25) void INT_ADI(void) {/* sleep(); */}
//  vector 26 Timer Z0
__interrupt(vect=26) void INT_TimerZ0(void) {/* sleep(); */}
//  vector 27 Timer Z1
__interrupt(vect=27) void INT_TimerZ1(void) {/* sleep(); */}
//  vector 28 Reserved

//  vector 29 Timer B1
__interrupt(vect=29) void INT_TimerB1(void) {/* sleep(); */}
//  vector 30 Reserved

//  vector 31 Reserved

//  vector 32 SCI3_2
__interrupt(vect=32) void INT_SCI3_2(void) {/* sleep(); */}

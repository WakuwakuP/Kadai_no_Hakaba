/***********************************************************************/
/*                                                                     */
/*  FILE        :TZ02.c                                                */
/*  DATE        :Tue, May 31, 2016                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :H8/3687                                               */
/*                                                                     */
/***********************************************************************/

#include "iodefine.h"
#include <machine.h>

char mode = 0;

void main(void);
#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

void IRQ0(void);
void IRQ1(void);
void IRQ2(void);
void IRQ3(void);

void main(void){
	set_imask_ccr(1);

	IO.PMR1.BYTE = 0xF0;				// SWを割り込みモードに
	IEGR1.BYTE = 0x70;					// 立ち上がりエッジに設定
	IENR1.BYTE = 0x1F;					// 割り込み許可
	IRR1.BYTE = 0x30;					// 割り込みフラグクリア

		// 1/(Φ/8)*

	TZ0.TCR.BYTE = 0x23;				// GRAと一致でクリア&立ち上がりでカウント&プリスケーラ/8に
	TZ0.POCR.BYTE = 0xF8;				// アクティブ設定
	TZ.TPMR.BYTE = 0x8E;				// PWMモードに
	TZ.TOCR.BYTE = 0x0C;				// 初期出力設定
	TZ0.GRA = 25000;					// MAX=25000
	TZ0.GRC = 0;
	TZ0.GRD = 0;

	set_imask_ccr(0);

	for(;;);
}

void IRQ0(void){
	IENR1.BYTE = 0x1F;					// SW全許可
	TZ.TOER.BIT.EC0 = 1;
	TZ.TOER.BIT.ED0 = 1;
	TZ0.GRC = 0;
	TZ0.GRD = 0;
	TZ.TSTR.BIT.STR0 = 0;
	IRR1.BIT.IRRI0 = 0;
}

void IRQ1(void){
	if(0 == mode){
		mode = 1;
	}else{
		mode = 0;
	}
	IRR1.BIT.IRRI1 = 0;
}

void IRQ2(void){
	IENR1.BYTE = 0x1D;
	if(0 == mode){
		TZ0.GRC = 6250;
		TZ.TOER.BIT.EC0 = 0;
	}else{
		TZ0.GRD = 6250;
		TZ.TOER.BIT.ED0 = 0;
	}
	TZ0.TCNT = 0;
	TZ.TSTR.BIT.STR0 = 1;

	IRR1.BIT.IRRI2 = 0;
}

void IRQ3(void){
	IENR1.BYTE = 0x1D;
	if(0 == mode){
		TZ0.GRC = 18750;
		TZ.TOER.BIT.EC0 = 0;
	}else{
		TZ0.GRD = 18750;
		TZ.TOER.BIT.ED0 = 0;
	}
	TZ0.TCNT = 0;
	TZ.TSTR.BIT.STR0 = 1;

	IRR1.BIT.IRRI3 = 0;
}

#ifdef __cplusplus
void abort(void)
{

}
#endif

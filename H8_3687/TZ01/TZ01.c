/***********************************************************************/
/*                                                                     */
/*  FILE        :TZ01.c                                                */
/*  DATE        :Tue, May 31, 2016                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :H8/3687                                               */
/*                                                                     */
/***********************************************************************/

#include "iodefine.h"
#include <machine.h>

void main(void);
#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif


void main(void){
	set_imask_ccr(1);

	IO.PMR1.BYTE = 0xF0;				// SWを割り込みモードに
	IEGR1.BYTE = 0x70;					// 立ち上がりエッジに設定
	IENR1.BYTE = 0x17;					// 割り込み許可
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



#ifdef __cplusplus
void abort(void)
{

}
#endif

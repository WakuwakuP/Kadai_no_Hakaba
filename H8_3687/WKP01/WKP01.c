/***********************************************************************/
/*                                                                     */
/*  FILE        :WKP01.c                                               */
/*  DATE        :Tue, Jun 14, 2016                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :H8/3687                                               */
/*                                                                     */
/***********************************************************************/

#include <machine.h>
#include "iodefine.h"

#define MSK_WKP0 0x01
#define MSK_WKP1 0x02
#define MSK_WKP2 0x04
#define MSK_WKP3 0x08
#define MSK_WKP4 0x10
#define MSK_WKP5 0x20

void WKP_func(void);

void main(void);
#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

void main(void){
	IO.PCR3 = 0xFF;
	IO.PUCR5.BYTE = 0x3F;

	set_imask_ccr(1);

	IO.PMR5.BYTE = 0x3F;				// ポート機能設定
	IEGR2.BYTE = 0x00;					// 立下りエッジに設定
	IENR1.BIT.IENWP = 1;				// 割り込み許可
	IWPR.BYTE = 0x00;					// 割り込みフラグクリア

	set_imask_ccr(0);

	while(1);
}

void WKP_func(void){
	if((IWPR.BYTE & MSK_WKP0) == MSK_WKP0){
		IO.PDR3.BIT.B0 = ~IO.PDR3.BIT.B0;
		IWPR.BIT.IWPF0 = 0;
		return;
	}
	if((IWPR.BYTE & MSK_WKP1) == MSK_WKP1){
		IO.PDR3.BIT.B1 = ~IO.PDR3.BIT.B1;
		IWPR.BIT.IWPF1 = 0;
		return;
	}
	if((IWPR.BYTE & MSK_WKP2) == MSK_WKP2){
		IO.PDR3.BIT.B2 = ~IO.PDR3.BIT.B2;
		IWPR.BIT.IWPF2 = 0;
		return;
	}
	if((IWPR.BYTE & MSK_WKP3) == MSK_WKP3){
		IO.PDR3.BIT.B3 = ~IO.PDR3.BIT.B3;
		IWPR.BIT.IWPF3 = 0;
		return;
	}
	if((IWPR.BYTE & MSK_WKP4) == MSK_WKP4){
		IO.PDR3.BIT.B4 = ~IO.PDR3.BIT.B4;
		IWPR.BIT.IWPF4 = 0;
		return;
	}
	if((IWPR.BYTE & MSK_WKP5) == MSK_WKP5){
		IO.PDR3.BIT.B5 = ~IO.PDR3.BIT.B5;
		IWPR.BIT.IWPF5 = 0;
		return;
	}
}

#ifdef __cplusplus
void abort(void)
{

}
#endif

/***********************************************************************/
/*                                                                     */
/*  FILE        :MOTOR.c                                               */
/*  DATE        :Tue, May 31, 2016                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :H8/3687                                               */
/*                                                                     */
/***********************************************************************/

#include "iodefine.h"
#include "lcd_func.h"
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
void wait(void);						// チャタリング防止用空ループ

void main(void){

	unsigned int vr1;

	AD.ADCSR.BYTE =0x1E;

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

	lcd_init();
	lcd_xy(1, 1);
	lcd_puts("VR1:");

	while(1){
		AD.ADCSR.BIT.ADST = 1;
		while(!AD.ADCSR.BIT.ADF);
		vr1 = (AD.ADDRB >> 6) * 0.098;
		if(0 < vr1){
			TZ0.GRC = vr1 * 222 + 2700;
		}else{
			TZ0.GRC = 0;
		}
		TZ0.GRD = TZ0.GRC;
		lcd_xy(5, 1);
		if(1 == mode){
			lcd_puts("-");
		}
		lcd_dataout(vr1);
		lcd_puts("[%]   ");
		AD.ADCSR.BIT.ADF = 0;
	}
}

void IRQ0(void){
	static char n = 0;

	if(0 == n){
		n = 1;
		IENR1.BYTE = 0x11;
		if(0 == mode){
			TZ.TOER.BIT.EC0 = 0;
		}else{
			TZ.TOER.BIT.ED0 = 0;
		}
		TZ0.TCNT = 0;
		TZ.TSTR.BIT.STR0 = 1;
	}else{
		n = 0;
		IENR1.BYTE = 0x13;					// SW全許可
		TZ.TOER.BIT.EC0 = 1;
		TZ.TOER.BIT.ED0 = 1;
		TZ.TSTR.BIT.STR0 = 0;
	}
	wait();
	IRR1.BIT.IRRI0 = 0;
}

void IRQ1(void){
	if(0 == mode){
		mode = 1;
	}else{
		mode = 0;
	}
	wait();
	IRR1.BIT.IRRI1 = 0;
}

void wait(){
	unsigned int i;
	for(i = 0; i < 50000; i++){
		;
	}
}

#ifdef __cplusplus
void abort(void)
{

}
#endif

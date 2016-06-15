/***********************************************************************/
/*                                                                     */
/*  FILE        :TIMER.c                                               */
/*  DATE        :Tue, May 24, 2016                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :H8/3687                                               */
/*                                                                     */
/***********************************************************************/

#include "iodefine.h"
#include <machine.h>
#include "lcd_func.h"					// LCD用ライブラリ

unsigned short int t = 0;				// タイマ用時間関数
float max_t;
char t_flag = 0;

void main(void);
#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

void init_TB1(char flag);				// TB1初期化用関数
void times_reset(void);					// 時間リセット用関数
void times(char n);						// 時間変更用関数
void timer_B1(void);					// タイマー割り込み用の関数
void SW03(void);						// SW03を押したとき用の関数(1分増やす)
void SW04(void);						// SW04を押したとき用の関数(10秒増やす)
void wait(void);						// チャタリング防止用空ループ
void time_pauce(void);					// タイマの一時停止処理
void LED_Visualizer(void);				// LED0.7までのビジュアライザ

void main(void)
{
	IO.PCR2 = 0x01;						// ブザー設定
	IO.PCR3 = 0xFF;						// LED設定

	set_imask_ccr(1);					// 割り込み不可

	init_TB1(0);						// 割り込み不可でTB1を初期化

	IO.PMR1.BYTE = 0xF0;				// SWを割り込みモードに
	IEGR1.BYTE = 0x70;					// 立ち上がりエッジに設定
	IENR1.BYTE = 0x1F;					// 割り込み許可
	IRR1.BYTE = 0x30;					// 割り込みフラグクリア

	set_imask_ccr(0);

	lcd_init();							// LCD初期化

	while(1){
		lcd_xy(1,1);
		if(t / 60 < 10){
			lcd_puts(" ");
		}
		lcd_dataout(t / 60);
		lcd_puts(":");
		if(t % 60 < 10){
			lcd_puts("0");
		}
		lcd_dataout(t % 60);
		if(0 == t && 1 == IENR2.BIT.IENTB1){
			IO.PDR2.BIT.B0 = 1;
			IENR2.BIT.IENTB1 = 0;
		}
		lcd_puts("   ");
		LED_Visualizer();
	}
}

void init_TB1(char flag){
	TB1.TMB1.BIT.RLD = 1;				// オートロードタイマに設定
	TB1.TMB1.BIT.CKS = 3;				// /256クロックに設定

	IRR2.BIT.IRRTB1 = 0;				// flagクリア
	IENR2.BIT.IENTB1 = flag;			// 割り込み許可
	TB1.TLB1 = 27;						// ロードレジスタ設定
}

void times_reset(void){
	t = 0;								// 時間初期化
	t_flag = 0;							// タイマ起動フラグリセット
}
void times(char n){
	t += n;								// 指定分時間追加(マイナス値で減らすことができる)
}

void timer_B1(void){
	static short int count = 0;
	count++;
	if(341 == count){
		count = 0;						// カウントクリア(1秒分)
		t--;							// 1秒マイナス
		if(0 == IO.PDR3.BIT.B7){
			IO.PDR3.BIT.B7 = 1;			// LED点灯
		}else{
			IO.PDR3.BIT.B7 = 0;			// LED消灯
		}
	}
	IRR2.BIT.IRRTB1 = 0;
}

void SW03(void){
	short int tmp;
	if(t / 60 >= 59){
		tmp = t % 60;
		times_reset();
		times(tmp);						// 59分を超える場合0分にする
	}else{
		times(60);						// 1分増やす
	}
}

void SW04(void){
	if(t % 60 >= 50){
		times(-50);						// 分上がりを防止して0秒にする。
	}else{
		times(10);						// 10秒増やす
	}
}

void wait(){
	unsigned int i;
	for(i = 0; i < 50000; i++){
		;
	}
}

void time_pauce(void){
	if(t_flag == 0){
		init_TB1(1);
		t_flag = 1;
		max_t = t;
		IO.PDR3.BYTE = 0x7F;			// LED0.6を点灯
	}else if(t_flag == 1){
		if(IENR2.BIT.IENTB1 == 1){
			IENR2.BIT.IENTB1 = 0;
		}else if(IENR2.BIT.IENTB1 == 0){
			IENR2.BIT.IENTB1 = 1;
		}
	}
}

void LED_Visualizer(void){
	if(1 >= t){
		IO.PDR3.BIT.B0 = 0;
	}
	if(max_t / 7 >= t){
		IO.PDR3.BIT.B1 = 0;
	}
	if(max_t / 7 * 2 >= t){
		IO.PDR3.BIT.B2 = 0;
	}
	if(max_t / 7 * 3 >= t){
		IO.PDR3.BIT.B3 = 0;
	}
	if(max_t / 7 * 4 >= t){
		IO.PDR3.BIT.B4 = 0;
	}
	if(max_t / 7 * 5 >= t){
		IO.PDR3.BIT.B5 = 0;
	}
	if(max_t / 7 * 6 >= t){
		IO.PDR3.BIT.B6 = 0;
	}
}

#ifdef __cplusplus
void abort(void)
{

}
#endif

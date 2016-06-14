/***********************************************************************/
/*                                                                     */
/*  FILE        :ENC01.c                                               */
/*  DATE        :Tue, Jun 14, 2016                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :H8/3687                                               */
/*                                                                     */
/***********************************************************************/

#include "iodefine.h"
#include "lcd_func.h"

unsigned char count = 0;

void WKP_func(void);

void main(void);
#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

void main(void){

	lcd_init();

	IO.PCR5 = 0xF0;
	IO.PUCR5.BYTE = 0xFF;

	IO.PMR5.BYTE = 0x01;						// �|�[�g�@�\�ݒ�
	IEGR2.BYTE = 0x00;							// ��������G�b�W�ɐݒ�
	IWPR.BYTE = 0x00;							// ���荞�݃t���O�N���A
	IENR1.BIT.IENWP = 1;						// ���荞�݋���

	while(1){
		lcd_xy(1,1);
		lcd_dataout(count);
	}
}

void WKP_func(void){
	if(0 == IO.PDR5.BIT.B1){
		count++;
		IWPR.BYTE = 0x00;
		return;
	}
	if(1 == IO.PDR5.BIT.B1){
		count--;
		IWPR.BYTE = 0x00;
		return;
	}
}

#ifdef __cplusplus
void abort(void)
{

}
#endif

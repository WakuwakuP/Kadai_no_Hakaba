/***********************************************************************/
/*                                                                     */
/*  FILE        :serial02.c                                            */
/*  DATE        :Tue, Jun 21, 2016                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :H8/3687                                               */
/*                                                                     */
/***********************************************************************/

#include "iodefine.h"

void wait(int);
void IRQ0(void);
void IRQ1(void);

int flag = 0;

void main(void);
#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

void main(void){
	IO.PCR3 = 0xFF;
	IO.PMR1.BYTE = 0x38;				// �X�C�b�`���荞��,�ʐM�|�[�g����
	IEGR1.BYTE = 0x70;
	IENR1.BYTE = 0x13;
	IRR1.BYTE = 0x30;

	SCI3_2.SCR3.BIT.TE = 0;				// ���M�s��
	SCI3_2.SMR.BYTE = 0x00;				// �f�[�^8BIT,�p���e�B�`�F�b�NNone,�X�g�b�v�r�b�g1BIT
	SCI3_2.BRR = 64;					// �r�b�g���[�g64[Bit/s]
	SCI3_2.TDR = 0x00;					// ���M�p�o�b�t�@������

	wait(2);

	SCI3_2.SCR3.BIT.TE = 1;				// ���M����

	while(1){
		if(flag != 0 && SCI3_2.SSR.BIT.TDRE == 1){
			switch(flag){
				case 1:
					SCI3_2.TDR = 0x01;
					break;
				case 2:
					SCI3_2.TDR = 0x02;
			}
			flag = 0;
		}
	}
}

void wait(int n){
	int i, j;
	for(i = 0; i < n;i++){
		for(j = 0; j < 1000;j++){
			;
		}
	}
}

void IRQ0(void){
	IO.PDR3.BIT.B0 = ~IO.PDR3.BIT.B0;
	IRR1.BIT.IRRI0 = 0;
	flag = 1;
}

void IRQ1(void){
	IO.PDR3.BIT.B1 = ~IO.PDR3.BIT.B1;
	IRR1.BIT.IRRI1 = 0;
	flag = 2;
}

#ifdef __cplusplus
void abort(void)
{

}
#endif

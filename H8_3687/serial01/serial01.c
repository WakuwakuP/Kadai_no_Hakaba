/***********************************************************************/
/*                                                                     */
/*  FILE        :serial01.c                                            */
/*  DATE        :Tue, Jun 21, 2016                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :H8/3687                                               */
/*                                                                     */
/***********************************************************************/
#include "iodefine.h"

void wait(int);
void func_sci(void);

void main(void);
#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

void main(void){
	IO.PCR3 = 0xFF;
	SCI3.SCR3.BIT.RE = 0;			// ��M�s��
	SCI3.SMR.BYTE = 0x00;			// ����������, �N���b�N�ݒ�0
	SCI3.BRR = 64;					// �r�b�g���[�g64[bit/s]

	wait(2);

	SCI3.SCR3.BIT.RE = 1;			// ��M����
	SCI3.SCR3.BIT.RIE = 1;			// ���荞�ݐݒ�
	while(1);
}

void wait(int n){
	int i, j;
	for (i = 0; i < n; i++){
		for (j = 0; j < 1000; j++){
			;
		}
	}
}

void func_sci(void){
	IO.PDR3.BYTE = SCI3.RDR;
}

#ifdef __cplusplus
void abort(void)
{

}
#endif

/***********************************************************************/
/*                                                                     */
/*  FILE        :SW03.c                                                */
/*  DATE        :Tue, May 17, 2016                                     */
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

void LED01(void){
	if(0 == IO.PDR3.BIT.B1){
		IO.PDR3.BIT.B1 = 1;
	}else{
		IO.PDR3.BIT.B1 = 0;
	}
	IRR1.BIT.IRRI0 = 0;
}

void LED02(void){
	if(0 == IO.PDR3.BIT.B2){
		IO.PDR3.BIT.B2 = 1;
	}else{
		IO.PDR3.BIT.B2 = 0;
	}
	IRR1.BIT.IRRI1 = 0;
}

void LED03(void){
	if(0 == IO.PDR3.BIT.B3){
		IO.PDR3.BIT.B3 = 1;
	}else{
		IO.PDR3.BIT.B3 = 0;
	}
	IRR1.BIT.IRRI2 = 0;
}

void LED04(void){
	if(0 == IO.PDR3.BIT.B4){
		IO.PDR3.BIT.B4 = 1;
	}else{
		IO.PDR3.BIT.B4 = 0;
	}
	IRR1.BIT.IRRI3 = 0;
}

void main(void){

	unsigned int i, j;

	IO.PCR3 = 0x9E;

	set_imask_ccr(1);

	IO.PMR1.BYTE = 0xF0;
	IEGR1.BYTE = 0x70;
	IENR1.BYTE = 0x1F;
	IRR1.BYTE = 0x30;

	set_imask_ccr(0);

	while(1){
		if(0 == IO.PDR3.BIT.B7){
			IO.PDR3.BIT.B7 = 1;
		}else{
			IO.PDR3.BIT.B7 = 0;
		}
		for(i = 0; i <= 20; i++){
			for(j = 0; j <= 50000; j++){
				;
			}
		}
	}
}

#ifdef __cplusplus
void abort(void)
{

}
#endif

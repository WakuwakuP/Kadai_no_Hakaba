/***********************************************************************/
/*                                                                     */
/*  FILE        :SW01.c                                                */
/*  DATE        :Tue, Apr 19, 2016                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :H8/3687                                               */
/*                                                                     */
/***********************************************************************/


#include "iodefine.h"

void main(void);
#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

void main(void)
{
	IO.PCR3 = 0xFF;
	IO.PCR2 = 0x01;
	for(;;){
		IO.PDR3.BIT.B1 = NOT(IO.PDR1.BIT.B4);
		IO.PDR3.BIT.B2 = NOT(IO.PDR1.BIT.B5);
		IO.PDR2.BIT.B0 = NOT(IO.PDR1.BIT.B6);
	}
}

int NOT(unsigned int a){
	if(a == 0){
		return 1;
	}
	return 0;
}

#ifdef __cplusplus
void abort(void)
{

}
#endif

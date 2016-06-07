/***********************************************************************/
/*                                                                     */
/*  FILE        :S37_LED03.c                                           */
/*  DATE        :Tue, Apr 19, 2016                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :H8/3687                                               */
/*                                                                     */
/***********************************************************************/


#include "iodefine.h"
void main(void);
void wait(unsigned int count);
#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

void main(void)
{
	unsigned int n, i;
	n = 0;
	IO.PCR3 = 0xFF;

	for(;;){
		IO.PDR3.BYTE = 0x01;
		wait(50);
		for(i =0;i <7; i++){
			IO.PDR3.BYTE = IO.PDR3.BYTE << 1;
			wait(50);
		}
	}
}

void wait(unsigned int count){
	unsigned int i, j;

	for(i = 0; i <= count; i++){
		for(j = 0; j <= 50000; j++){
			;
		}
	}
}

#ifdef __cplusplus
void abort(void)
{

}
#endif

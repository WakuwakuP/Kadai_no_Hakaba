/***********************************************************************/
/*                                                                     */
/*  FILE        :7SEG01.c                                              */
/*  DATE        :Tue, Apr 26, 2016                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :H8/3687                                               */
/*                                                                     */
/*  This file is generated by WakuwakuP.                               */
/*                                                                     */
/*  github URL: https://github.com/WakuwakuP/Kadai_no_Hakaba           */
/*                                                                     */
/***********************************************************************/

#include "iodefine.h"

void main(void);
void wait(void);
#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

void main(void)
{
	unsigned char count = 0, flag = 0;
	
	IO.PCR5 = 0x0F;

	for(;;){
		if(flag == 0){
			if(IO.PDR1.BIT.B4 == 0){
				flag = 1;
				count += 1;
				wait();
			}
			if(IO.PDR1.BIT.B5 == 0){
				flag = 2;
				count -= 1;
				wait();
			}
			if(IO.PDR1.BIT.B7 == 0){
				flag = 3;
				count = 0;
				wait();
			}
		}else{
			if(IO.PDR1.BIT.B4 == 1 && IO.PDR1.BIT.B5 == 1 && IO.PDR1.BIT.B7 == 1){
				flag = 0;
				wait();
			}
		}
		IO.PDR5.BYTE = count;
	}
}

void wait(){
	unsigned int i;
	for(i = 0; i < 40000; i++){
		;
	}
}

#ifdef __cplusplus
void abort(void)
{

}
#endif

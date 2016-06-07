/***********************************************************************/
/*                                                                     */
/*  FILE        :THERMO.c                                              */
/*  DATE        :Tue, May 10, 2016                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :H8/3687                                               */
/*                                                                     */
/***********************************************************************/

#include "iodefine.h"
#include "lcd_func.h"

void main(void);
#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

void main(void)
{
	float n = 0;

	AD.ADCSR.BYTE = 0x04;

	lcd_init();

	while(1){
		AD.ADCSR.BIT.ADST = 1;

		while(!AD.ADCSR.BIT.ADF);
		AD.ADCSR.BIT.ADF = 0

		n = (AD.ADDRA >> 6) * 0.5 - 50;
		lcd_xy(1, 1);
		lcd_dataout(n);
		lcd_puts("[ßC]  ");
		lcd_xy(1, 2);
		lcd_dataout(n * 1.8 + 32);
		lcd_puts("[ßF]  ");
	}
}

#ifdef __cplusplus
void abort(void)
{

}
#endif

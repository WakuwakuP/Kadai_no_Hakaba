/***********************************************************************/
/*                                                                     */
/*  FILE        :AD02.c                                                */
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
	unsigned int vr1 = 0, vr2 = 0;

	AD.ADCSR.BYTE =0x1E;

	lcd_init();
	lcd_xy(1, 1);
	lcd_puts("VR1:");
	lcd_xy(1, 2);
	lcd_puts("VR2:");
	while(1){
		AD.ADCSR.BIT.ADST = 1;

		while(!AD.ADCSR.BIT.ADF);

		vr1 = (AD.ADDRB >> 6) * 0.098;
		vr2 = (AD.ADDRC >> 6) * 0.098;
		lcd_xy(5, 1);
		lcd_dataout(vr1);
		lcd_puts("[%]  ");
		lcd_xy(5, 2);
		lcd_dataout(vr2);
		lcd_puts("[%]  ");
		AD.ADCSR.BIT.ADF = 0;
	}
}

#ifdef __cplusplus
void abort(void)
{

}
#endif

/***********************************************************************/
/*                                                                     */
/*  FILE        :LCD02.c                                               */
/*  DATE        :Tue, Apr 26, 2016                                     */
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

void main(void){
	lcd_init();
	IO.PCR5 = 0xF0;
	for(;;){
		lcd_xy(1, 1);
		lcd_puts("SW1=");
		if(IO.PDR1.BIT.B4 == 0){
			lcd_puts("ON  ");
		}else{
			lcd_puts("OFF ");
		}
		lcd_puts("SW2=");
		if(IO.PDR1.BIT.B5 == 0){
			lcd_puts("ON ");
		}else{
			lcd_puts("OFF");
		}
		lcd_xy(1, 2);
		lcd_puts("SW3=");
		if(IO.PDR1.BIT.B6 == 0){
			lcd_puts("ON  ");
		}else{
			lcd_puts("OFF ");
		}
		lcd_puts("SW4=");
		if(IO.PDR1.BIT.B7 == 0){
			lcd_puts("ON ");
		}else{
			lcd_puts("OFF");
		}
	}
}

#ifdef __cplusplus
void abort(void)
{

}
#endif

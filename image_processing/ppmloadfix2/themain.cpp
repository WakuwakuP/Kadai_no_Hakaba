#include "ppmload.h"

void main(void){
	struct ppmimg *image1=NULL,*image2=NULL,*image3=NULL;

	image1 = makeimagestruct(image1);
	image2 = makeimagestruct(image2);
	image3 = makeimagestruct(image3);
	loadppmimage("ColorReverse.ppm",image1);
	cloneppmimage(image1,image2);
	image3 = createppmimage(image3,image1->iwidth,image1->iheight,image1->cmode);
	for(int j=0;j<image1->iheight;j++){
		for(int i=0;i<image1->iwidth;i++){
			struct RGBColor trgb = getPnmPixel(image1,i,j);
			if(image1->cmode == 1){
				trgb.dens = 255 - trgb.dens;
			}else{
				trgb.R = 255 - trgb.R;
				trgb.G = 255 - trgb.G;
				trgb.B = 255 - trgb.B;
			}
			setPnmPixel(image3,i,j,trgb);
		}
	}
	saveppmimage(image3,"ColorReverse1.ppm");
	deleteppmimg(image1);
	deleteppmimg(image2);
	deleteppmimg(image3);
}
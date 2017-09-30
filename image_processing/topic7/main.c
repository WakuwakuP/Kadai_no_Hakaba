#include <ppmload/ppmload.h>

struct RGBColor NTSCWeightedAverage(struct RGBColor *rgb) {
	struct RGBColor set;
	double ntsc = 0.298912 * rgb->R + 0.586611 * rgb->G + 0.114478 * rgb->B;
	set.R = set.G = set.B = (unsigned char)ntsc;

	return set;
}

void AlphaBrending(struct ppmimg *base, struct ppmimg *brend struct ppmimg *alpha) {
	struct ppmimg *save = NULL;
	save = makeimagestruct(save);
	save = createppmimage(save, (int)((double)brend->iwidth), (int)((double)brend->iheight), brend->cmode);

	for (int x = 0; x < brend->iwidth; x++) {
		for (int y = 0; y < brend->iheight; y++) {
			struct RGBColor baseColor = getPnmPixel(base, x, y);
			struct RGBColor brendColor = getPnmPixel(brend, x, y);
			struct RGBColor alphaColor = getPnmPixel(alpha, x, y);
			struct RGBColor setColor;


			setColor.R = (unsigned char)((double)(255 - alphaColor.dens) / 255.0 * (double)baseColor.R + (double)alphaColor.dens / 255.0 * (double)brendColor.R);
			setColor.G = (unsigned char)((double)(255 - alphaColor.dens) / 255.0 * (double)baseColor.G + (double)alphaColor.dens / 255.0 * (double)brendColor.G);
			setColor.B = (unsigned char)((double)(255 - alphaColor.dens) / 255.0 * (double)baseColor.B + (double)alphaColor.dens / 255.0 * (double)brendColor.B);

			setPnmPixel(save, x, y, setColor);

		}
	}

	saveppmimage(save, "alphaBrending.ppm");

	deleteppmimg(save);

}

void main(void) {
	//アルファブレンディング
	struct ppmimg *base = NULL, *brend = NULL , *alpha;
	base = makeimagestruct(base);
	brend = makeimagestruct(brend);
  alpha = makeimagestruct(alpha);

	loadppmimage("base.ppm", base);
	loadppmimage("brend.ppm", brend);
  loadppmimage("alpha.pgm", alpha)

	AlphaBrending(base, brend);

	deleteppmimg(base);
	deleteppmimg(brend);
}

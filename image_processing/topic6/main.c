#include <ppmload/ppmload.h>
#include <stdlib.h>

int getMedian(int cnt[],int w,int h);
int getMode(int cnt[]);
void frattening(struct ppmimg *image, int cnt[]);
void LinedensConv(struct ppmimg *base, int cnt[]);

int main(void) {
	// データ格納部を用意
	struct ppmimg *image = NULL;
	int dens[256] = { 0 };
	int median, mode;
	FILE *hist;
	FILE *other;

	int w,h,a;

	image = makeimagestruct(image);
	loadppmimage("Default.pgm", image);
	hist = fopen("hist.csv", "w");
	other = fopen("mode_and_median.txt", "w");

	struct RGBColor getPixel = getPnmPixel(image,1,1);
	for (w = 0; w < image->iwidth; w++) {
		for (h = 0; h < image->iheight; h++) {
			getPixel = getPnmPixel(image, w, h);
			dens[getPixel.dens]++;
		}
	}

	median = getMedian(dens, image->iwidth, image->iheight);
	mode = getMode(dens);
	LinedensConv(image, dens);
	frattening(image, dens);

	for(a = 0; a < 256; a++) {
		fprintf(hist,"%d\n",dens[a]);
	}
	fprintf(other, "Median : %d\n", median);
	fprintf(other, "Mode : %d", mode);

	fclose(hist);
	fclose(other);
	deleteppmimg(image);
}

int getMedian(int cnt[], int w, int h) {
	int dataNum = w * h / 2;
	int target=0;
	while (dataNum > 0) {
		dataNum -= cnt[target];
		target++;
	}
	return( target-1 );
}

int getMode(int cnt[]) {
	int max = 0;
	int maxKosa = 0;
	int a;
	for (a = 0; a < 256; a++) {
		if (max < cnt[a]) {
			max = cnt[a];
			maxKosa = a;
		}
	}
	return(maxKosa);
}

//線形濃度変換
void LinedensConv(struct ppmimg *base, int cnt[]) {

	int dens[256] = {0};
	FILE *noudo;

	noudo = fopen("Noudo.csv", "w");
	struct ppmimg *image = NULL;
	image = makeimagestruct(image);
	image = createppmimage(image, base->iwidth, base->iheight, base->cmode);



	// min, max 取得
		int min = -1, max = -1;
		//min
		for (int i = 0; i < 256; i++) {
				if (cnt[i] != 0) {  // 0 でなければ
						min = i;            // 記憶して
						break;              // 抜ける
				}
		}
		//max
		for (int i = 255; 0 <= i; i--) {
				if (cnt[i] != 0) {
						max = i;
						break;
				}
		}

		int z_m = 255;
		int a = min;
		int b = max;

		// 線形濃度変換
		for (int y = 0; y < base->iheight; y++) {
				for (int x = 0; x < base->iwidth; x++) {
					struct RGBColor getPixel = getPnmPixel(base, x, y);
					struct RGBColor setPixel;
					int z = getPixel.dens;

					if (0 <= z && z < a) {
							setPixel.dens = 0;
					}else if (a <= z && z <= b) {
							setPixel.dens = (int)(((double)(z - a) / (b - a)) * z_m + 0.5);
					}
					else if (b < z && z <= z_m) {
							setPixel.dens = z_m;
					}

					setPnmPixel(image, x, y, setPixel);
					dens[setPixel.dens]++;
				}
		}

	for (a = 0; a < 256; a++) {
		fprintf(noudo, "%d\n", dens[a]);
	}

	saveppmimage(image, "senkeiNoudo.pgm");
	deleteppmimg(image);
	fclose(noudo);
}

void frattening(struct ppmimg *image,int cnt[]) {

	int x, y, i, a;
	int ans[256] = { 0 };
	struct ppmimg *out = NULL;
	FILE *fratt;


	fratt = fopen("fratt.csv", "w");

	out = makeimagestruct(out);
	out = createppmimage(out, image->iwidth, image->iheight, image->cmode);

	for (x = 0; x < image->iwidth; x++) {
		for (y = 0; y < image->iheight; y++) {
			struct RGBColor getColor = getPnmPixel(image, x, y);
			struct RGBColor setColor;
			int sumFreq = 0;

			for (i = 0; i <= getColor.dens; i++) {
				sumFreq += cnt[i];
			}

			setColor.dens = (255 * sumFreq) / (image->iheight * image->iwidth);
			ans[setColor.dens]++;
			setPnmPixel(image, x, y, setColor);
		}
	}


	for (a = 0; a < 256; a++) {
		fprintf(fratt, "%d\n", ans[a]);
	}

	saveppmimage(image, "Frattening.pgm");
	fclose(fratt);
}

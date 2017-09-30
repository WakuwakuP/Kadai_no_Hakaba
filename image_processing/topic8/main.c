#include <ppmload/ppmload.h>
#include <time.h>

void copyImage(struct ppmimg *base, struct ppmimg *copy);
void Pixelize(struct ppmimg *image, int n, int x1, int y1, int x2, int y2);
void FixedThreshold(struct ppmimg *image, char *Imagename, int threshold);
struct RGBColor cvGray(struct RGBColor *rgb);
void FourFourDither(struct ppmimg *image, int matrix[], char *imagename);
void ErrorDiffusion(struct ppmimg *Image, char *imagename);
void setppmGrayDens(struct RGBColor *set, unsigned char dens);
void RandomDither(struct ppmimg *image, char *imagename);
void makeAsciiArt(struct ppmimg *image, char *aaname, int threshold);

//画像を複製する関数
void copyImage(struct ppmimg *base, struct ppmimg *copy) {

	copy = cloneppmimage(base, copy);

	for (int x = 0; x < base->iwidth; x++) {
		for (int y = 0; y < base->iheight; y++) {
			setPnmPixel(copy, x, y, getPnmPixel(base, x, y));
		}
	}
}

//座標を指定し、n*nのブロックによるモザイク処理を行う関数
void Pixelize(struct ppmimg *image, int n, int x1, int y1, int x2, int y2) {

	char imagename[16];

	struct ppmimg *save = NULL;
	save = makeimagestruct(save);
	copyImage(image, save);

	//指定した範囲内をモザイク処理
	for (int x = x1; x < x2; x += n) {
		for (int y = y1; y < y2; y += n) {
			struct RGBColor setColor;
			int sum_color[3] = { 0 };

			for (int dx = 0; dx < n; dx++) {
				for (int dy = 0; dy < n; dy++) {
					struct RGBColor getColor = getPnmPixel(image, x + dx, y + dy);

					sum_color[0] += getColor.R;
					sum_color[1] += getColor.G;
					sum_color[2] += getColor.B;
				}
			}

			for (int dx = 0; dx < n; dx++) {
				for (int dy = 0; dy < n; dy++) {
					setColor.R = sum_color[0] / (n * n);
					setColor.G = sum_color[1] / (n * n);
					setColor.B = sum_color[2] / (n * n);

					setPnmPixel(save, x + dx, y + dy, setColor);
				}
			}
		}

	}

	sprintf(imagename, "pixelize%d.ppm", n);
	saveppmimage(save, imagename);
	deleteppmimg(save);
}

//固定閾値法
void FixedThreshold(struct ppmimg *image, char *imagename, int threshold) {

	struct ppmimg *save = NULL;
	save = makeimagestruct(save);
	save = cloneppmimage(image, save);

	if (threshold > 255) threshold = 255;
	else if (threshold < 0) threshold = 0;

	for (int x = 0; x < image->iwidth; x++) {
		for (int y = 0; y < image->iheight; y++) {
      struct RGBColor tmp = getPnmPixel(image, x, y);
			struct RGBColor trgb = cvGray(&tmp);

			if (trgb.R > threshold)
				trgb.R = trgb.G = trgb.B = 255;
			else
				trgb.R = trgb.G = trgb.B = 0;

			setPnmPixel(save, x, y, trgb);
		}
	}

	saveppmimage(save, imagename);
	deleteppmimg(save);
}

//画像データをグレイスケールに変換
struct RGBColor cvGray(struct RGBColor *rgb) {
	struct RGBColor set;

	double ntsc = 0.298912 * rgb->R + 0.586611 * rgb->G + 0.114478 * rgb->B;
	set.R = set.G = set.B = (unsigned char)ntsc;

	return set;
}

//4*4ディザ法
void FourFourDither(struct ppmimg *image, int matrix[], char *imagename) {

	struct ppmimg *save = NULL;
	save = makeimagestruct(save);
	save = cloneppmimage(image, save);

	for (int x = 0; x < save->iwidth; x++) {
		for (int y = 0; y < save->iheight; y++) {
			int bayer = matrix[(x % 4) + (y % 4) * 4] * 16 + 8;
			struct RGBColor getColor = getPnmPixel(image, x, y);
			struct RGBColor setColor;

			if (bayer <= getColor.R) {
				setColor.R = setColor.G = setColor.B = 255;
			}
			else {
				setColor.R = setColor.G = setColor.B = 0;
			}

			setPnmPixel(save, x, y, setColor);
		}
	}

	saveppmimage(save, imagename);
	deleteppmimg(save);

}

//誤差拡散法
void ErrorDiffusion(struct ppmimg *image, char *imagename) {
	struct ppmimg *save = NULL;
	save = makeimagestruct(save);
	save = cloneppmimage(image, save);

	//読み込んだRGB画像をグレイスケール画像に変換
	for (int x = 0; x < image->iwidth; x++) {
		for (int y = 0; y < image->iheight; y++) {
      struct RGBColor tmp = getPnmPixel(image, x, y);
			setPnmPixel(save, x, y, cvGray(&tmp));
		}
	}

	const double diff[4] = { 7.0 / 16.0, 3.0 / 16.0, 5.0 / 16.0, 1.0 / 16.0 };	//誤差拡散法のパラメータ定数

	for(int y = 1; y < save->iheight - 1; y++){
		for (int x = 1; x < save->iwidth - 1; x++) {

			//誤差拡散法に関わる5つの画素データを取得
			struct RGBColor getColor[5] = {
				getPnmPixel(save, x, y),			//現在位置(これが基準)
				getPnmPixel(save, x + 1, y),		//右
				getPnmPixel(save, x - 1, y + 1),	//左下
				getPnmPixel(save, x, y + 1),		//下
				getPnmPixel(save, x + 1, y + 1)		//右下
			};

			struct RGBColor setColor[5];

			//注目画素を2値化
			setppmGrayDens(&setColor[0], (getColor[0].R > 128) ? 255 : 0);

			//誤差の大きさを計算して結果を格納
			double quantError = (double)getColor[0].R - (double)setColor[0].R;

			for (int i = 1; i < 5; i++) {

				//セットする濃度値を計算
				double setDens = (double)getColor[i].R + diff[i - 1] * quantError;

				if (setDens < 0) setDens = 0.0;
				else if (setDens > 255) setDens = 255.0;

				setppmGrayDens(&setColor[i], (unsigned char)(setDens));
			}

			setPnmPixel(save, x, y, setColor[0]);			//現在位置(これが基準)
			setPnmPixel(save, x + 1, y, setColor[1]);		//右
			setPnmPixel(save, x - 1, y + 1, setColor[2]);	//左下
			setPnmPixel(save, x, y + 1, setColor[3]);		//下
			setPnmPixel(save, x + 1, y + 1, setColor[4]);	//右下
		}
	}


	saveppmimage(save, imagename);
	deleteppmimg(save);
}

void setppmGrayDens(struct RGBColor *set, unsigned char dens) {
	set->R = set->G = set->B = dens;
}

//ランダムディザ
void RandomDither(struct ppmimg *image, char *imagename) {
	struct ppmimg *save = NULL;
	save = makeimagestruct(save);
	save = cloneppmimage(image, save);

	srand((unsigned int)time(NULL));

	int threshold = (int)(rand() * 256.0 / (RAND_MAX + 1.0));

	printf("thr = %d\n", threshold);

	for (int y = 0; y < image->iheight; y++) {
		for (int x = 0; x < image->iwidth; x++) {
      struct RGBColor tmp = getPnmPixel(image, x, y);
			struct RGBColor getColor = cvGray(&tmp);
			struct RGBColor setColor;

			if (getColor.R < threshold)
				setppmGrayDens(&setColor, 0);
			else
				setppmGrayDens(&setColor, 255);

			setPnmPixel(save, x, y, setColor);
		}
	}

	saveppmimage(save, imagename);
	deleteppmimg(save);
}

//文字画像を2値化しつつアスキーアートに変換
void makeAsciiArt(struct ppmimg *image, char *aaname, int threshold) {

	FILE *aa;

	aa = fopen(aaname, "w");

	if (aa == NULL) {
		puts("ファイルが開けませんでした");
		return;
	}

	struct ppmimg *binary = NULL;
	binary = makeimagestruct(binary);
	cloneppmimage(image, binary);

	if (threshold > 255) threshold = 255;
	else if (threshold < 0) threshold = 0;

	for (int y = 0; y < image->iheight; y++) {
		for (int x = 0; x < image->iwidth; x++) {
      struct RGBColor tmp = getPnmPixel(image, x, y);
			struct RGBColor trgb = cvGray(&tmp);

			if (trgb.R > threshold)
				fprintf(aa, " ");
			else
				fprintf(aa, "@");
		}
		fprintf(aa, "\n");
	}

	fclose(aa);
}

int main(void) {

	int bayer[16] =
	{
		0, 8, 2,10,
		12, 4,14, 6,
		3,11, 1, 9,
		15, 7,13, 5
	};

	int halftone[16] = {
		10, 4, 6, 8,
		12, 0, 2,14,
		7, 9,11, 5,
		3,15,13, 1
	};

	int screw[16] = {
		13, 7, 6,12,
		8, 1, 0, 5,
		9, 2 ,3, 4,
		14,10,11,15

	};

	int screwDefor[16] = {
		15, 4, 8, 2,
		11, 0, 1, 5,
		7, 3, 2, 9,
		14,10, 6,13
	};

	int mediumEmp[16] = {
		12, 4, 8, 14,
		11, 0, 2,  6,
		7, 3, 1, 10,
		15, 9, 5, 13
	};

	int dotConcent[16] = {
		13, 4, 8, 14,
		10, 0, 1,  7,
		6, 3, 2, 11,
		15, 9 ,5, 13
	};

	struct ppmimg *image = NULL;

	image = makeimagestruct(image);
	loadppmimage("Default.ppm", image);

	Pixelize(image, 8, 200, 60, 400, 333);
	Pixelize(image, 16, 200, 60, 400, 333);
	FixedThreshold(image, "FixedThreshold.ppm", 128);
	FourFourDither(image, bayer, "bayer.ppm");
	FourFourDither(image, halftone, "halftone.ppm");
	FourFourDither(image, screw, "screw.ppm");
	FourFourDither(image, screwDefor, "screwDefor.ppm");
	FourFourDither(image, mediumEmp, "mediumEmp.ppm");
	FourFourDither(image, dotConcent, "dotConcent.ppm");
	ErrorDiffusion(image, "ErrorDiffusion.ppm");
	RandomDither(image, "RandomDither.ppm");

	deleteppmimg(image);

	return 0;
}

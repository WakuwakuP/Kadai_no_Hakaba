#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ppmload/ppmload.h>

void LankvalFilter(struct ppmimg *image, char *imagename, int lank);
void MedianFilter(struct ppmimg *image, char *imagename);
void ModeFilter(struct ppmimg *image, char *imagename);
void LinearFilter(struct ppmimg *image, char *imagename, double filter[3][3], int bias);
void GaussianFilter(struct ppmimg *image, char *imagename, int bias);
void SharpFilter(struct ppmimg *image, char *imagename, int bias);
void BilateralFilter(struct ppmimg *image, char *imagename, double sigma, double brightdiff, int bias);
void LaplacianFilter(struct ppmimg *image, char *imagename, int bias);
void MaxMinFilter(struct ppmimg *image, char *imagename);

// ソート用関数
int cmp( const void *p, const void *q );

int cmp( const void *p, const void *q ) {
    return *(int*)p - *(int*)q;
}

//ランク値フィルタ
void LankvalFilter(struct ppmimg *image, char *imagename, int lank)
{
	//1 <= lank <= 9 となるように調整
	if (lank > 9) lank = 9;
	else if (lank < 1) lank = 1;

	struct ppmimg *save = NULL;
	save = makeimagestruct(save);
	save = cloneppmimage(image, save);

	for (int y = 1; y < save->iheight - 1; y++){
		for (int x = 1; x < save->iwidth - 1; x++){

			unsigned char sortDens[9];	//ソート用配列

			//周囲の画素データを取得し、ソート用配列に格納していく
			for (int dx = 0; dx < 3; dx++){
				for (int dy = 0; dy < 3; dy++){
					struct RGBColor getColor = getPnmPixel(image, x - 1 + dx, y - 1 + dy);
					sortDens[dx + dy * 3] = getColor.dens;
				}
			}

			qsort(sortDens, sizeof( sortDens )/sizeof( int ), sizeof(int), cmp);

			struct RGBColor setColor;
			setColor.dens = sortDens[lank - 1];	//配列sortDensのlank番目に来る値を代表値として利用
			setPnmPixel(save, x, y, setColor);
		}
	}

	saveppmimage(save, imagename);
	deleteppmimg(save);

}

//メディアンフィルタ
void MedianFilter(struct ppmimg *image, char *imagename)
{
	LankvalFilter(image, imagename, 5);
}

//最頻値フィルタ
void ModeFilter(struct ppmimg *image, char *imagename)
{
	struct ppmimg *save = NULL;
	save = makeimagestruct(save);
	save = cloneppmimage(image, save);

	for (int y = 1; y < save->iheight - 1; y++) {
		for (int x = 1; x < save->iwidth - 1; x++) {

			unsigned char modeDens[9];	//最頻値を求めるための配列
			unsigned char countDens[256] = { 0 };


			//周囲の画素データを取得し、配列modeDensに格納していく
			for (int dx = 0; dx < 3; dx++) {
				for (int dy = 0; dy < 3; dy++) {
					struct RGBColor getColor = getPnmPixel(image, x - 1 + dx, y - 1 + dy);
					modeDens[dx + dy * 3] = getColor.dens;
				}
			}

			//最頻値を求める処理
			int maxcount = 0;
			for (int i = 0; i < 9; i++) {
				countDens[modeDens[i]]++;

				if (maxcount < countDens[modeDens[i]])
					maxcount = countDens[modeDens[i]];
			}

			unsigned char mode = 0;

			for (int i = 0; i < 9; i++) {
				if (maxcount == countDens[modeDens[i]])
					mode = modeDens[i];
			}

			struct RGBColor setColor;
			setColor.dens = mode;
			setPnmPixel(save, x, y, setColor);
		}
	}

	saveppmimage(save, imagename);
	deleteppmimg(save);


}

//線形フィルタ
void LinearFilter(struct ppmimg *image, char *imagename, double filter[3][3], int bias) {
	struct ppmimg *save = NULL;
	save = makeimagestruct(save);
	save = cloneppmimage(image, save);

	for (int y = 1; y < save->iheight - 1; y++) {
		for (int x = 1; x < save->iwidth; x++) {

			struct RGBColor getColor[3][3];	//周囲の画素データを格納するための2次元配列

			for (int dx = 0; dx < 3; dx++) {
				for (int dy = 0; dy < 3; dy++) {
					 getColor[dx][dy] = getPnmPixel(image, x - 1 + dx, y - 1 + dy);
				}
			}

			//座標(x, y)に対するフィルタ処理を行う
			double afterFiltering = 0;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					afterFiltering += (double)getColor[i][j].dens * filter[i][j];
				}
			}

			//補正をかける
			int correctPixel = (int)afterFiltering + bias;
			if (correctPixel < 0) correctPixel = 0;
			if (correctPixel > 255) correctPixel = 255;

			struct RGBColor setColor;
			setColor.dens = (unsigned char)correctPixel;
			setPnmPixel(save, x, y, setColor);
		}
	}

	saveppmimage(save, imagename);
	deleteppmimg(save);
}

//ガウシアンフィルタ
void GaussianFilter(struct ppmimg *image, char *imagename, int bias) {

	double filter[3][3] = {
		{ 1.0 / 16.0, 2.0 / 16.0 , 1.0 / 16.0 },
		{ 2.0 / 16.0, 4.0 / 16.0 , 2.0 / 16.0 },
		{ 1.0 / 16.0, 2.0 / 16.0 , 1.0 / 16.0 }
	};

	LinearFilter(image, imagename, filter, bias);
}

//鮮鋭化フィルタ
void SharpFilter(struct ppmimg *image, char *imagename, int bias) {

	double filter[3][3] = {
		{ -0.11, -0.11, -0.11 },
		{ -0.11, 1.88, -0.11 },
		{ -0.11, -0.11, -0.11 }
	};

	LinearFilter(image, imagename, filter, bias);

}

//バイリテラルフィルタ
void BilateralFilter(struct ppmimg *image, char *imagename, double sigma, double brightdiff, int bias) {
	struct ppmimg *save = NULL;
	save = makeimagestruct(save);
	save = cloneppmimage(image, save);


	for (int y = 1; y < save->iheight - 1; y++) {
		for (int x = 1; x < save->iwidth; x++) {

			struct RGBColor getColor[3][3];	//周囲の画素データを格納するための2次元配列

			for (int dx = 0; dx < 3; dx++) {
				for (int dy = 0; dy < 3; dy++) {
					getColor[dx][dy] = getPnmPixel(image, x - 1 + dx, y - 1 + dy);
				}
			}

			//バイリテラルフィルタの公式にあてはめる
			double numerator = 0, denominator = 0;

			for (int n = -1; n <= 1; n++) {
				for (int m = -1; m <= 1; m++) {
					double expnum = exp(-1 * (m * m + n * n) / (2 * sigma * sigma));
					double w = exp(-1 * pow(getColor[1][1].dens - getColor[m + 1][n + 1].dens, 2) / 2 * brightdiff * brightdiff);
					numerator += (double)getColor[m + 1][n + 1].dens * expnum * w;
					denominator += expnum * w;
				}
			}

			//補正をかける
			int correctPixel = (int)(numerator / denominator) + bias;
			if (correctPixel < 0) correctPixel = 0;
			if (correctPixel > 255) correctPixel = 255;

			struct RGBColor setColor;
			setColor.dens = (unsigned char)correctPixel;
			setPnmPixel(save, x, y, setColor);
		}
	}

	saveppmimage(save, imagename);
	deleteppmimg(save);
}

//ラプラシアンフィルタ
void LaplacianFilter(struct ppmimg *image, char *imagename, int bias) {
	double filter[3][3] = {
		{ 1,  1, 1 },
		{ 1, -8, 1 },
		{ 1,  1, 1 }
	};

	LinearFilter(image, imagename, filter, bias);
}

//Max-Minフィルタ
void MaxMinFilter(struct ppmimg *image, char *imagename) {
	struct ppmimg *save = NULL;
	save = makeimagestruct(save);
	save = cloneppmimage(image, save);


	for (int y = 1; y < save->iheight - 1; y++) {
		for (int x = 1; x < save->iwidth; x++) {

			unsigned char sortDens[9];	//ソート用配列

			//周囲の画素データを取得し、ソート用配列に格納していく
			for (int dx = 0; dx < 3; dx++) {
				for (int dy = 0; dy < 3; dy++) {
					struct RGBColor getColor = getPnmPixel(image, x - 1 + dx, y - 1 + dy);
					sortDens[dx + dy * 3] = getColor.dens;
				}
			}

			//配列sortDensに対して昇順ソートを行う。実装を楽にするためにc++の標準ライブラリを使用
			qsort(sortDens, sizeof( sortDens )/sizeof( int ), sizeof(int), cmp);

			struct RGBColor setColor;
			setColor.dens = sortDens[8] - sortDens[0];	//最大値と最小値の差を新しい濃度値とする
			setPnmPixel(save, x, y, setColor);
		}
	}

	saveppmimage(save, imagename);
	deleteppmimg(save);
}

int main(void) {

	struct ppmimg *test = NULL, *mediantest = NULL;

	test = makeimagestruct(test);
	mediantest = makeimagestruct(mediantest);

	loadppmimage("filtertest.pgm", test);
	loadppmimage("medianfiltertest.pgm", mediantest);

	for (int i = 1; i <= 9; i++) {
		char imagename[20] = "Lank";
		imagename[4] = '\0';
		char number[2] = "0";
		number[0] += i;
		char *tmp = "_Filter.pgm";
		strcat(imagename, number);
		strcat(imagename, tmp);
		LankvalFilter(test, imagename , i);
	}

	MedianFilter(mediantest, "MedianFilter.pgm");
	ModeFilter(test, "ModeFilter.pgm");
	GaussianFilter(test, "GaussianFilter.pgm", 0);
	SharpFilter(test, "SharpFilter.pgm", 0);
	BilateralFilter(test, "BiliateralFilter.pgm", 1.0, 1.0, 0);
	LaplacianFilter(test, "LaplacianFilter.pgm", 0);
	MaxMinFilter(test, "MaxMinFilter.pgm");

	deleteppmimg(test);
	deleteppmimg(mediantest);
}

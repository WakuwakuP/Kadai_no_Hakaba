#include <ppmload/ppmload.h>

struct RGBColor cvGray(struct RGBColor *rgb);
void Convert2BitmapByHB(struct ppmimg *image, char *imagename);
int isRGBColorEquals(struct RGBColor str1, struct RGBColor str2);
void Expansion(struct ppmimg *image, char *imagename, int n);
void Contraction(struct ppmimg *image, char *imagename, int n);
void Closing(struct ppmimg *image, char *imagename, int n);
void Opening(struct ppmimg *image, char *imagename, int n);
void Labeling(char *baseImagename, char *saveImagename);

//画像データをグレイスケールに変換
struct RGBColor cvGray(struct RGBColor *rgb) {
	struct RGBColor set;

	double ntsc = 0.298912 * rgb->R + 0.586611 * rgb->G + 0.114478 * rgb->B;
	set.R = set.G = set.B = (unsigned char)ntsc;

	return set;
}

//RGB画像→グレイスケール画像→2値画像
void Convert2BitmapByHB(struct ppmimg *image, char *imagename) {

	struct ppmimg *save = NULL;
	save = makeimagestruct(save);
	cloneppmimage(image, save);

	//グレイスケール画像生成
	for (int i = 0; i < image->iwidth; i++) {
		for (int j = 0; j < image->iheight; j++) {
      struct RGBColor tmp = getPnmPixel(image, i, j);
			setPnmPixel(save, i, j, cvGray(&tmp));
		}
	}

	struct RGBColor getColor, setColor;
	unsigned char level;
	unsigned int hist[256] = {0};
	int t, max_t, t_limit;
	int i, j, n1, n2, count, sum;
	unsigned long tmp;
	double ave;
	double ave1, ave2, var1, var2, max;
	double var_w, var_b, r;

	max_t = 0;
	t_limit = 255;	//	[0,255]の256階調

	//グレイスケール画像の濃度とかの統計データを取得したり、、
	sum = 0, count = 0, ave = 0;
	for (j = 0; j < save->iheight; j++) {
		for (i = 0; i < save->iwidth; i++) {
			getColor = getPnmPixel(save, i, j);
			level = getColor.R;
			hist[level] ++;
			sum = sum + getColor.R;
			count++;
		}
	}

	ave = sum / count;
	printf("ave=%.0lf\n", ave);

	max = -1.0;
	for (t = 0; t < t_limit; t++) {
		n1 = n2 = 0;
		ave1 = ave2 = 0;
		var1 = var2 = 0;
		tmp = 0;
		for (i = 0; i < t; i++) {
			n1 = n1 + hist[i];
			tmp = tmp + hist[i] * i;
		}
		//	クラス1について平均を求める
		if (n1 != 0) {
			ave1 = (double)tmp / (double)n1;
		}

		for (i = 0; i < t; i++) {
			var1 = var1 + (i - ave1)*(i - ave1)*hist[i];
		}
		//	クラス1について分散を求める
		if (n1 != 0) {
			var1 = var1 / (double)n1;
		}

		tmp = 0;
		for (i = t; i < t_limit; i++) {
			n2 = n2 + hist[i];
			tmp = tmp + hist[i] * i;
		}
		//	クラス2について平均を求める
		if (n2 != 0) {
			ave2 = (double)tmp / (double)n2;
		}

		for (i = t; i < t_limit; i++) {
			var2 = var2 + (i - ave2)*(i - ave2)*hist[i];
		}
		//	クラス2について分散を求める
		if (n2 != 0) {
			var2 = var2 / (double)n2;
		}

		var_w = (n1*var1 + n2*var2);	//	分母(n1+n2)は省略
		var_b = n1*(ave1 - ave)*(ave1 - ave) + n2*(ave2 - ave)*(ave2 - ave);
		r = var_b / var_w;
		if (r > max) {
			max = r;
			max_t = t;
		}
	}

	printf("max_t = %d\n", max_t);

	//	二値化
	for (j = 0; j < save->iheight; j++) {
		for (i = 0; i <save->iwidth; i++){

			if (getPnmPixel(save, i, j).R >= max_t) {
				setColor.R = setColor.G = setColor.B = 255;
			} else {
				setColor.R = setColor.G = setColor.B = 0;
			}

			setPnmPixel(save, i, j, setColor);
		}
	}

	saveppmimage(save, imagename);
	deleteppmimg(save);
}

//膨張処理
void Expansion(struct ppmimg *image, char *imagename, int n){

	struct ppmimg *dst = NULL;
	dst = makeimagestruct(dst);
	cloneppmimage(image, dst);

	for (int y = 1; y < dst->iheight - 1; y++) {
		for (int x = 1; x < dst->iwidth - 1; x++) {

			struct RGBColor getColor = getPnmPixel(image, x, y);
			struct RGBColor setColor;

			setColor.R = setColor.G = setColor.B = 0;

			for (int dy = 0; dy < 3; dy++) {
				for (int dx = 0; dx < 3; dx++) {
					if (!(dx == 1 && dy == 1) && getPnmPixel(image, x - 1 + dx, y - 1 + dy).R == 255) {
						setColor.R = setColor.G = setColor.B = 255;
						break;
					}
				}
			}

			setPnmPixel(dst, x, y, setColor);
		}
	}

	if (n <= 1) {
		saveppmimage(dst, imagename);
	}
	else {
		//printf("Expansion %d\n", n);
		Expansion(dst, imagename, n - 1);
	}

	deleteppmimg(dst);

}

//収縮処理
void Contraction(struct ppmimg *image, char *imagename, int n){
	struct ppmimg *dst = NULL;
	dst = makeimagestruct(dst);
	cloneppmimage(image, dst);

	for (int y = 1; y < dst->iheight - 1; y++) {
		for (int x = 1; x < dst->iwidth - 1; x++) {

			struct RGBColor getColor = getPnmPixel(image, x, y);
			struct RGBColor setColor;

			setColor.R = setColor.G = setColor.B = 255;

			for (int dy = 0; dy < 3; dy++) {
				for (int dx = 0; dx < 3; dx++) {
					if (!(dx == 1 && dy == 1) && getPnmPixel(image, x - 1 + dx, y - 1 + dy).R == 0) {
						setColor.R = setColor.G = setColor.B = 0;
						break;
					}
				}
			}

			setPnmPixel(dst, x, y, setColor);
		}
	}

	if (n <= 1) {
		saveppmimage(dst, imagename);
	}
	else {
		//printf("Contraction %d\n", n);
		Contraction(dst, imagename, n - 1);
	}
	deleteppmimg(dst);

}

//クロージング処理
void Closing(struct ppmimg *image, char *imagename, int n) {
	Expansion(image, imagename, n);

	//膨張処理関数は最終的に画像名が保存される仕様であるため、収縮処理を行うために保存した画像を再び読み込むようにする。
	struct ppmimg *tmp = NULL;
	tmp = makeimagestruct(tmp);
	loadppmimage(imagename, tmp);

	Contraction(tmp, imagename, n);
	deleteppmimg(tmp);
}

//オープニング処理
void Opening(struct ppmimg *image, char *imagename, int n) {
	Contraction(image, imagename, n);

	//収縮処理関数は最終的に画像名が保存される仕様であるため、膨張処理を行うために保存した画像を再び読み込むようにする。
	struct ppmimg *tmp = NULL;
	tmp = makeimagestruct(tmp);
	loadppmimage(imagename, tmp);

	Expansion(tmp, imagename, n);
	deleteppmimg(tmp);
}

//ラベリング
void Labeling(char *baseImagename, char *saveImagename) {
	struct ppmimg *base = NULL, *save = NULL;
	base = makeimagestruct(base);
	save = makeimagestruct(save);
	loadppmimage(baseImagename, base);
	cloneppmimage(base, save);

	struct RGBColor colorLUT[256] = {0};

	//セーフカラー216色コード表より。
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			for (int k = 0; k < 6; k++) {
				colorLUT[i * 36 + j * 6 + k].R = 255 - 51 * i;
				colorLUT[i * 36 + j * 6 + k].G = 255 - 51 * j;
				colorLUT[i * 36 + j * 6 + k].B = 255 - 51 * k;
				//printf("colorLUT[%d] = %3d %3d %3d\n", i * 36 + j * 6 + k, colorLUT[i * 36 + j * 6 + k].R, colorLUT[i * 36 + j * 6 + k].G, colorLUT[i * 36 + j * 6 + k].B);
			}
		}
	}

	int cntLabel = -1;
	int **pixelLabel = NULL;
	int *labelLUT = NULL;

	//メモリ動的確保
	pixelLabel = (int **)malloc(sizeof(int *) * base->iwidth);
	labelLUT = (int *)malloc(sizeof(int) * base->iwidth * base->iheight);

	for (int i = 0; i < base->iwidth; i++) {
		pixelLabel[i] = (int *)malloc(sizeof(int) * base->iheight);

		//全画素のラベル番号を0に初期化
		for (int j = 0; j < base->iheight; j++) {
			pixelLabel[i][j] = 0;
		}
	}

	for (int y = 1; y < base->iheight - 1; y++) {
		for (int x = 1; x < base->iwidth - 1; x++) {

			if (getPnmPixel(base, x, y).R == 255) {

				//周囲画素のラベル番号を取得
				int neighLabel[4] = {
					pixelLabel[x - 1][y - 1],	//左上
					pixelLabel[x][y - 1],		//上
					pixelLabel[x + 1][y - 1],	//右上
					pixelLabel[x - 1][y],		//左
				};

				if (neighLabel[0] == 0 && neighLabel[1] == 0 && neighLabel[2] == 0 && neighLabel[3] == 0) {

					//取得した周囲画素のラベル番号が全て0の場合、新たなラベル番号を振る
					cntLabel++;
					pixelLabel[x][y] = labelLUT[cntLabel] = cntLabel;
					//printf("label = %d\n", label);
				}
				else {
					int tmpLabelData = cntLabel;
					for (int i = 0; i < 4; i++) {
						if (neighLabel[i] != 0 && neighLabel[i] < tmpLabelData)
							tmpLabelData = neighLabel[i];
					}

					pixelLabel[x][y] = tmpLabelData;

					for (int i = 0; i < 4; i++) {
						if (neighLabel[i] != 0 && neighLabel[i] != tmpLabelData)
							labelLUT[neighLabel[i]] = tmpLabelData;
					}
				}
			}
		}
	}
	//
	for (int y = 1; y < save->iheight - 1; y++) {
		for (int x = 1; x < save->iwidth - 1; x++) {
			pixelLabel[x][y] = labelLUT[pixelLabel[x][y]];
		}
	}

	//ラベリング作業を行う
	for (int y = 0; y < base->iheight; y++) {
		for (int x = 0; x < base->iwidth; x++) {
			struct RGBColor setColor;

			if (pixelLabel[x][y] == 0)
				setColor.R = setColor.G = setColor.B = 0;
			else
				setColor = colorLUT[pixelLabel[x][y]];

			setPnmPixel(save, x, y, setColor);
		}
	}

	for (int i = 0; i< base->iheight; i++) {
		free(pixelLabel[i]);
	}
	free(pixelLabel);
	free(labelLUT);

	saveppmimage(save, saveImagename);
	deleteppmimg(base);
	deleteppmimg(save);
}

int isRGBColorEquals(struct RGBColor str1, struct RGBColor str2) {
	return (str1.R == str2.R) && (str1.G == str2.G) && (str1.B == str2.B);
}

int main(void) {

	struct ppmimg *image = NULL;

	image = makeimagestruct(image);
	loadppmimage("Arere.ppm", image);
	Convert2BitmapByHB(image, "binary.ppm");

	struct ppmimg *binary = NULL;
	binary = makeimagestruct(binary);
	loadppmimage("binary.ppm", binary);

	Closing(binary, "Closing.ppm", 1);
	Opening(binary, "Opening.ppm", 1);

	Labeling("Opening.ppm", "Labeling.ppm");

	deleteppmimg(image);
	deleteppmimg(binary);
}

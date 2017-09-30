#include <ppmload/ppmload.h>
#include <time.h>
//ppmload.h ppm処理ライブラリのインクルード

#define SCALE_X1 0.33
#define SCALE_Y1 0.33
#define SCALE_X2 2.7
#define SCALE_Y2 2.7

void Nearest(struct ppmimg *src, struct ppmimg *dst, double scalex, double scaley);
void Linear(struct ppmimg *src, struct ppmimg *dst, double scalex, double scaley);

int main(void){
  struct ppmimg *img=NULL, *nearest1 = NULL, *nearest2 = NULL, *liner1= NULL, *liner2 = NULL;
	//struct ppmimg <= 画像を表す構造体
	//struct ppmimg *image1 = NULL ポインタだけ作る(NULLで初期化)

	img = makeimagestruct(img);
  nearest1 = makeimagestruct(nearest1);
	nearest2 = makeimagestruct(nearest2);
	liner1 = makeimagestruct(liner1);
  liner2 = makeimagestruct(liner2);
	//生成画像へのポインタ = makeimagestruct(画像へのポインタ)
	//画像の本体を取得する → 画像へのポインタを返す
	//空の画像がこれでできる

	loadppmimage("Default.ppm", img);
	//ファイル名から、画像を読み込む(画像情報が読み込まれる)

  nearest1 = createppmimage(nearest1, img->iwidth*SCALE_X1, img->iheight*SCALE_Y1, img->cmode);
  nearest2 = createppmimage(nearest2, img->iwidth*SCALE_X2, img->iheight*SCALE_Y2, img->cmode);
  liner1 = createppmimage(liner1, img->iwidth*SCALE_X1, img->iheight*SCALE_Y1, img->cmode);
  liner2 = createppmimage(liner2, img->iwidth*SCALE_X2, img->iheight*SCALE_Y2, img->cmode);
	//imageに手動で、空の画像を生成

  Nearest(img, nearest1, SCALE_X1, SCALE_Y1);
	saveppmimage(nearest1, "Nearset Neighbor/nearest1.ppm");
  Nearest(img, nearest2, SCALE_X2, SCALE_Y2);
	saveppmimage(nearest2, "Nearset Neighbor/nearest2.ppm");
  Linear(img, liner1, SCALE_X1, SCALE_Y1);
  saveppmimage(liner1, "Linear Interpolation/liner1.ppm");
  Linear(img, liner2, SCALE_X2, SCALE_Y2);
	saveppmimage(liner2, "Linear Interpolation/liner2.ppm");

	//画像の消去(後片付け)
	deleteppmimg(img);
	deleteppmimg(nearest1);
  deleteppmimg(nearest2);
  deleteppmimg(liner1);
  deleteppmimg(liner2);
  return 0;
}

//最近傍法
void Nearest(struct ppmimg *src, struct ppmimg *dst, double scalex, double scaley) {
  int i, j;
  clock_t start, stop;


  start = clock();
  for (j = 0; j < dst->iheight-1; j++) {
    for (i = 0; i < dst->iwidth-1; i++) {
      double x = (i / scalex) + 0.5;
      double y = (j / scaley) + 0.5;
      struct RGBColor cSrc = getPnmPixel(src, (int)x, (int)y);
      setPnmPixel(dst, i, j, cSrc);
    }
  }
  stop = clock();
  printf("%ld ms\n", stop - start);
}

//線形補間法
void Linear(struct ppmimg *src, struct ppmimg *dst, double scalex, double scaley) {
  int i, j;
  clock_t start, stop;
  struct RGBColor color;

  start = clock();
  for (j = 0; j < dst->iheight-2; j++) {
    for (i = 0; i < dst->iwidth-2; i++) {
      double x0 = i / scalex;
      double y0 = j / scaley;
      int x = (int)x0;
      int y = (int)y0;
      struct RGBColor lowL = getPnmPixel(src, x, y+1);
      struct RGBColor lowR = getPnmPixel(src, x+1, y+1);
      struct RGBColor highL = getPnmPixel(src, x, y);
      struct RGBColor highR = getPnmPixel(src, x+1, y);

      color.B = (y + 1 - y0)*((x + 1 - x0)*highL.B + (x0 - x)*highR.B) + (y0 - y)*((x + 1 - x0)*lowL.B + (x0 - x)*lowR.B);

      color.G = (y + 1 - y0)*((x + 1 - x0)*highL.G + (x0 - x)*highR.G) + (y0 - y)*((x + 1 - x0)*lowL.G + (x0 - x)*lowR.G);

      color.R = (y + 1 - y0)*((x + 1 - x0)*highL.R + (x0 - x)*highR.R) + (y0 - y)*((x + 1 - x0)*lowL.R + (x0 - x)*lowR.R);

      setPnmPixel(dst, i, j, color);
    }
  }
  stop = clock();
  printf("%ld ms\n", stop - start);
}

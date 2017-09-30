#include <math.h>
#include <ppmload/ppmload.h>

//ppmload.h ppm処理ライブラリのインクルード

//階調数の設定
#define BASE 16

void cvtGray(struct ppmimg *base, struct ppmimg *clone, int sw);
void Gchannel(struct ppmimg *base, struct ppmimg *clone);
void SimpleAve(struct ppmimg *base, struct ppmimg *clone);
void MiddleVal(struct ppmimg *base, struct ppmimg *clone);
void Ntcs(struct ppmimg *base, struct ppmimg *clone);
void Hdtv(struct ppmimg *base, struct ppmimg *clone);
void GradConvers(struct ppmimg *base, struct ppmimg *clone, int num);
int Min(int a, int b, int c);
int Max(int a, int b, int c);

int main(int argc, char const *argv[]) {
	struct ppmimg *img1=NULL,*img2=NULL,*img3=NULL,*img4=NULL,*img5=NULL,*img6=NULL,*img7=NULL;
	//struct ppmimg <= 画像を表す構造体
	//struct ppmimg *image1 = NULL ポインタだけ作る(NULLで初期化)

	img1 = makeimagestruct(img1);
	img2 = makeimagestruct(img2);
	img3 = makeimagestruct(img3);
	img4 = makeimagestruct(img4);
  img5 = makeimagestruct(img5);
  img6 = makeimagestruct(img6);
  img7 = makeimagestruct(img7);
	//生成画像へのポインタ = makeimagestruct(画像へのポインタ)
	//画像の本体を取得する → 画像へのポインタを返す
	//空の画像がこれでできる

	loadppmimage("Default.ppm", img1);
	//ファイル名から、画像を読み込む(画像情報が読み込まれる)

  img2 = createppmimage(img2, img1->iwidth, img1->iheight, 1);
  img3 = createppmimage(img3, img1->iwidth, img1->iheight, 1);
  img4 = createppmimage(img4, img1->iwidth, img1->iheight, 1);
  img5 = createppmimage(img5, img1->iwidth, img1->iheight, 1);
  img6 = createppmimage(img6, img1->iwidth, img1->iheight, 1);
  img7 = createppmimage(img7, img1->iwidth, img1->iheight, 1);
  //読み込んだimage1と同じプロパティの画像を生成
  //プロパティ=サイズ、色数、PN => 色は全部ない

  cvtGray(img1, img2, 0);
  cvtGray(img1, img3, 1);
  cvtGray(img1, img4, 2);
  cvtGray(img1, img5, 3);
  cvtGray(img1, img6, 4);
  GradConvers(img6, img7, BASE);

	//名前を付けて画像をセーブする関数
	saveppmimage(img2, "1.pgm");
	saveppmimage(img3, "2.pgm");
	saveppmimage(img4, "3.pgm");
  saveppmimage(img5, "4.pgm");
  saveppmimage(img6, "5.pgm");
  saveppmimage(img7, "6.pgm");

	//画像の消去(後片付け)
	deleteppmimg(img1);
	deleteppmimg(img2);
	deleteppmimg(img3);
	deleteppmimg(img4);
  deleteppmimg(img5);
  deleteppmimg(img6);
  deleteppmimg(img7);
}

//課題の関数
void cvtGray(struct ppmimg *base, struct ppmimg *clone, int sw)
{
  switch (sw) {
  case 0:
    Gchannel(base, clone); break;
  case 1:
    SimpleAve(base, clone); break;
  case 2:
    MiddleVal(base, clone); break;
  case 3:
    Ntcs(base, clone); break;
  case 4:
    Hdtv(base, clone); break;
  default:break;
  }
}

//G-Channel法
void Gchannel(struct ppmimg *base, struct ppmimg *clone)
{
  int i, j;
  struct RGBColor cclone;

  if(clone->cmode == 1)
    for (j = 0; j < base->iheight; j++) {
      for (i = 0; i < base->iwidth; i++) {
        struct RGBColor cbase = getPnmPixel(base, i, j);

        cclone.dens = cbase.G;

        setPnmPixel(clone, i, j, cclone);
      }
    }
}

//RGB平均法
void SimpleAve(struct ppmimg *base, struct ppmimg *clone)
{
  int i, j;
  struct RGBColor cclone;

  if(clone->cmode == 1)
    for (j = 0; j < base->iheight; j++) {
      for (i = 0; i < base->iwidth; i++) {
        struct RGBColor cbase = getPnmPixel(base, i, j);

        cclone.dens = (double)(cbase.B + cbase.G + cbase.R) / 3;

        setPnmPixel(clone, i, j, cclone);
      }
    }
}

//中間値法
void MiddleVal(struct ppmimg *base, struct ppmimg *clone)
{
  int i, j;
  struct RGBColor cclone;

  if(clone->cmode == 1)
    for (j = 0; j < base->iheight; j++) {
      for (i = 0; i < base->iwidth; i++) {
        struct RGBColor cbase = getPnmPixel(base, i, j);
        int max = Max(cbase.B, cbase.G, cbase.R);
        int min = Min(cbase.B, cbase.G, cbase.R);

        cclone.dens = (max + min) / 2;

        setPnmPixel(clone, i, j, cclone);
      }
    }
}

//NTSC加重平均
void Ntcs(struct ppmimg *base, struct ppmimg *clone)
{
  int i, j;
  struct RGBColor cclone;

  if(clone->cmode == 1)
    for (j = 0; j < base->iheight; j++) {
      for (i = 0; i < base->iwidth; i++) {
        struct RGBColor cbase = getPnmPixel(base, i, j);

        cclone.dens = 0.298912*cbase.R + 0.586611*cbase.G + 0.114478*cbase.B;

        setPnmPixel(clone, i, j, cclone);
      }
    }
}

//HDTV係数による加重平均と補正
void Hdtv(struct ppmimg *base, struct ppmimg *clone)
{
  int i, j;
  double r, g, b;
  double x = 2.2;
  struct RGBColor cclone;

  if (clone->cmode == 1)
    for (j = 0; j < base->iheight; j++) {
      for (i = 0; i < base->iwidth; i++) {
        struct RGBColor cbase = getPnmPixel(base, i, j);

        r = pow(cbase.R, x) * 0.222015;
        g = pow(cbase.G, x) * 0.706655;
        b = pow(cbase.B, x) * 0.071330;

        cclone.dens = pow(r+g+b, 1/x);

        setPnmPixel(clone, i, j, cclone);
      }
    }
}

//最小
int Min(int a, int b, int c) {
  if (a < b)
    if (a < c)
      return a;
    else
      return c;
  else
    if (b < c)
      return b;
    else
      return c;
}

//最大
int Max(int a, int b, int c) {
  if (a < b)
    if (b < c)
      return c;
    else
      return b;
  else
    if (a < c)
      return c;
    else
      return a;
}

//階調数変換
void GradConvers(struct ppmimg *src, struct ppmimg *dst, int num) {
  int level[256];
  int base = 256 / 64;
  int i, j;
  struct RGBColor cclone;

  if (src->cmode == 1 && dst->cmode == 1) {
    if (1 <= num && num <= 64) {
      if (num <= 32) base = 256 / 32;
      if (num <= 16) base = 256 / 16;
      if (num <= 8) base = 256 / 8;
      if (num <= 4) base = 256 / 4;
      if (num == 2) base = 256 / 2;
      if (num == 1) base = 256;
    }

    for (i = 0; i < 256 / base; i++) {
      for (j = 0; j < base; j++) {
        level[i*base + j] = i*base;
      }
    }

    for (j = 0; j < src->iheight; j++) {
      for (i = 0; i < src->iwidth; i++) {
        struct RGBColor cbase = getPnmPixel(src, i, j);

        cclone.dens = level[cbase.dens];

        setPnmPixel(dst, i, j, cclone);
      }
    }
  }
}

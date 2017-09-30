#include <ppmload/ppmload.h>
//ppmload.h ppm処理ライブラリのインクルード
// 7/22RGB2CMYK まで

void Rgb2Cmy(struct ppmimg *img, struct ppmimg *clone);
void Rgb2Cmyk(struct ppmimg *base, struct ppmimg *img);
int Min(int a, int b, int c);
int Max(int a, int b, int c);


int main(void){
	struct ppmimg *image1=NULL, *image2=NULL, *image3=NULL;
	//struct ppmimg <= 画像を表す構造体
	//struct ppmimg *image1 = NULL ポインタだけ作る(NULLで初期化)

	image1 = makeimagestruct(image1);
	image2 = makeimagestruct(image2);
  image3 = makeimagestruct(image3);
	//生成画像へのポインタ = makeimagestruct(画像へのポインタ)
	//画像の本体を取得する → 画像へのポインタを返す
	//空の画像がこれでできる

	loadppmimage("Default.ppm",image1);
	//ファイル名から、画像を読み込む(画像情報が読み込まれる)

	cloneppmimage(image1, image2);
  cloneppmimage(image1, image3);
	//読み込んだimage1と同じプロパティの画像を生成
	//プロパティ=サイズ、色数、PN => 色は全部ない

  Rgb2Cmy(image1, image2);
  Rgb2Cmyk(image1, image3);

	//名前を付けて画像をセーブする関数
	saveppmimage(image2, "1.ppm");
  saveppmimage(image3, "2.ppm");

	//画像の消去(後片付け)
	deleteppmimg(image1);
	deleteppmimg(image2);
  deleteppmimg(image3);
}

//RGB2CMY CMY2RGB
void Rgb2Cmy(struct ppmimg *base, struct ppmimg *img) {
  int i, j;
  struct RGBColor cmy;

  for (i = 0; i < base->iheight; i++) {
    for (j = 0; j < base->iwidth; j++) {
      struct RGBColor rgb = getPnmPixel(base, j, i);

      cmy.B = 255 - rgb.R;
      cmy.G = 255 - rgb.B;
      cmy.R = 255 - rgb.G;

      setPnmPixel(img, j, i, cmy);
    }
  }
}

//CMY2CMYK CMYK2CMY?
void Rgb2Cmyk(struct ppmimg *base, struct ppmimg *img) {
  int i, j;
  struct ppmimg *clone = NULL;
  struct RGBColor cmyk;

  clone = makeimagestruct(clone);
  cloneppmimage(base, clone);

  Rgb2Cmy(base, clone);

  for (i = 0; i < clone->iheight; i++) {
    for (j = 0; j < clone->iwidth; j++) {
      struct RGBColor cmy = getPnmPixel(clone, j, i);

      cmyk.B = cmy.R - Min(cmy.B, cmy.G, cmy.R);
      cmyk.G = cmy.B - Min(cmy.B, cmy.G, cmy.R);
      cmyk.R = cmy.G - Min(cmy.B, cmy.G, cmy.R);

      setPnmPixel(img, j, i, cmyk);
    }
  }

  deleteppmimg(clone);
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

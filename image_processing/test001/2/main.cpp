#include "ppmload.h"

#include <iostream>
#include <cmath>

void Reverse(void);           // 反転
void onlyRed(void);           // 赤色抽出
void onlyGreen(void);         // 緑色抽出
void onlyBlue(void);          // 青色抽出
void averageGray(void);       // 平均グレースケール
void thresholdGray(void);     // 闘値グレースケール
void statistics(struct ppmimg *image, unsigned char color); // 出力関数

void main (void) {

  // 各処理を呼び出すだけ
  //Reverse();
  //onlyRed();
  //onlyGreen();
  //onlyBlue();
  averageGray();
  thresholdGray();
}

void Reverse(void) {
  struct ppmimg *image1 = NULL, *image2 = NULL, *image3 = NULL;

  image1 = makeimagestruct(image1);
  image2 = makeimagestruct(image2);
  image3 = makeimagestruct(image3);
  loadppmimage("cover.ppm", image1);
  cloneppmimage(image1, image2);
  image3 = createppmimage(image3, image1->iwidth, image1->iheight, image1->cmode);
  for (int j = 0; j<image1->iheight; j++) {
    for (int i = 0; i<image1->iwidth; i++) {
      struct RGBColor trgb = getPnmPixel(image1, i, j);
      if (image1->cmode == 1) {
        trgb.dens = 255 - trgb.dens;
      }
      else {
        if (20 <= i && i <= 50 && 20 <= j && j <= 50) {
          trgb.R = 255;
          trgb.G = 0;
          trgb.B = 0;
        }
        else {
          trgb.R = 255 - trgb.R;
          trgb.G = 255 - trgb.G;
          trgb.B = 255 - trgb.B;
        }
      }
      setPnmPixel(image3, i, j, trgb);
    }
  }
  saveppmimage(image3, "output/colorReverse3.ppm");
  saveppmimage(image2, "output/colorReverse2.ppm");
  saveppmimage(image1, "output/colorReverse1.ppm");
  deleteppmimg(image1);
  deleteppmimg(image2);
  deleteppmimg(image3);
}

/**
 *  赤色抽出
 */
void onlyRed(void){
	struct ppmimg *image1=NULL,*image2=NULL,*image3=NULL;

	image1 = makeimagestruct(image1);
	image2 = makeimagestruct(image2);
	image3 = makeimagestruct(image3);
	loadppmimage("cover.ppm",image1);
	cloneppmimage(image1,image2);
	image3 = createppmimage(image3,image1->iwidth,image1->iheight,image1->cmode);
	for(int j=0;j<image1->iheight;j++){
		for(int i=0;i<image1->iwidth;i++){
			struct RGBColor trgb = getPnmPixel(image1,i,j);
			if(image1->cmode == 1){
				// trgb.dens = 255 - trgb.dens;
			}else{
				// trgb.R = 0;
				trgb.G = 0;
        trgb.B = 0;
			}
			setPnmPixel(image3,i,j,trgb);
		}
	}
  //statistics(image3, 'r');
  saveppmimage(image3,"output/onlyRed.ppm");
	deleteppmimg(image1);
	deleteppmimg(image2);
	deleteppmimg(image3);
}

/**
*  緑色抽出
*/
void onlyGreen(void) {
  struct ppmimg *image1 = NULL, *image2 = NULL, *image3 = NULL;

  image1 = makeimagestruct(image1);
  image2 = makeimagestruct(image2);
  image3 = makeimagestruct(image3);
  loadppmimage("cover.ppm", image1);
  cloneppmimage(image1, image2);
  image3 = createppmimage(image3, image1->iwidth, image1->iheight, image1->cmode);
  for (int j = 0; j<image1->iheight; j++) {
    for (int i = 0; i<image1->iwidth; i++) {
      struct RGBColor trgb = getPnmPixel(image1, i, j);
      if (image1->cmode == 1) {
        //trgb.dens = 255 - trgb.dens;
      }
      else {
        trgb.R = 0;
        // trgb.G = 0;
        trgb.B = 0;
      }
      setPnmPixel(image3, i, j, trgb);
    }
  }
  //statistics(image3, 'g');
  saveppmimage(image3, "output/onlyGreen.ppm");
  deleteppmimg(image1);
  deleteppmimg(image2);
  deleteppmimg(image3);
}

/**
 *  青色抽出
 */
void onlyBlue(void) {
  struct ppmimg *image1 = NULL, *image2 = NULL, *image3 = NULL;

  image1 = makeimagestruct(image1);
  image2 = makeimagestruct(image2);
  image3 = makeimagestruct(image3);
  loadppmimage("cover.ppm", image1);
  cloneppmimage(image1, image2);
  image3 = createppmimage(image3, image1->iwidth, image1->iheight, image1->cmode);
  for (int j = 0; j<image1->iheight; j++) {
    for (int i = 0; i<image1->iwidth; i++) {
      struct RGBColor trgb = getPnmPixel(image1, i, j);
      if (image1->cmode == 1) {
        //trgb.dens = 255 - trgb.dens;
      }
      else {
        trgb.R = 0;
        trgb.G = 0;
        //trgb.B = 0;
      }
      setPnmPixel(image3, i, j, trgb);
    }
  }
  //statistics(image3, 'b');
  saveppmimage(image3, "output/onlyBlue.ppm");
  deleteppmimg(image1);
  deleteppmimg(image2);
  deleteppmimg(image3);
}

/**
*  平均値を使ってグレースケール
*/
void averageGray(void) {
  struct ppmimg *image1 = NULL, *image2 = NULL, *image3 = NULL;

  image1 = makeimagestruct(image1);
  image2 = makeimagestruct(image2);
  image3 = makeimagestruct(image3);
  loadppmimage("cover.ppm", image1);
  cloneppmimage(image1, image2);
  image3 = createppmimage(image3, image1->iwidth, image1->iheight, 1);
  for (int j = 0; j<image1->iheight; j++) {
    for (int i = 0; i<image1->iwidth; i++) {
      struct RGBColor trgb = getPnmPixel(image1, i, j);

      // カラーピクセルをグレースケール化
      trgb.dens = (trgb.R + trgb.G + trgb.B) / 3;

      setPnmPixel(image3, i, j, trgb);
    }
  }
  saveppmimage(image3, "output/grayAverage.pgm");
  deleteppmimg(image1);
  deleteppmimg(image2);
  deleteppmimg(image3);
}

/**
*  謎の闘値を使ってグレースケール
*/
void thresholdGray(void) {
  struct ppmimg *image1 = NULL, *image2 = NULL, *image3 = NULL;

  image1 = makeimagestruct(image1);
  image2 = makeimagestruct(image2);
  image3 = makeimagestruct(image3);
  loadppmimage("cover.ppm", image1);
  cloneppmimage(image1, image2);
  image3 = createppmimage(image3, image1->iwidth, image1->iheight, 1);
  for (int j = 0; j<image1->iheight; j++) {
    for (int i = 0; i<image1->iwidth; i++) {
      struct RGBColor trgb = getPnmPixel(image1, i, j);

      // カラーピクセルをグレースケール化
      trgb.dens = char(0.299 * trgb.R + 0.587 * trgb.G + 0.114 * trgb.B);

      setPnmPixel(image3, i, j, trgb);
    }
  }
  //statistics(image3, 'd');
  saveppmimage(image3, "output/grayThreshold.pgm");
  deleteppmimg(image1);
  deleteppmimg(image2);
  deleteppmimg(image3);
}


void statistics(struct ppmimg *image, unsigned char color) {
  int count = 0;
  double average = 0;
  double variance = 0;
  int max = 0;
  int min = 255;
  int median;
  int mode, modeScore = 0;
  int modeCount[256] = { 0 };
  int flag = 0;

  int center;

  for (int j = 0; j < image->iheight; j++) {
    for (int i = 0; i < image->iwidth; i++) {
      struct RGBColor trgb = getPnmPixel(image, i, j);
      int tmp;
      count++;

      if ('r' == color) {
        tmp = trgb.R;
      }
      else if ('g' == color) {
        tmp = trgb.G;
      }
      else if ('b' == color) {
        tmp = trgb.B;
      }
      else {
        tmp = trgb.dens;
      }

      average += tmp;

      if (max < tmp) {
        max = tmp;
      }

      if (tmp < min) {
        min = tmp;
      }

      modeCount[tmp]+= 1;
    }
  }
  center = count / 2;
  for (int i = 0; i < 256; i++) {
    if (modeScore < modeCount[i]) {
      modeScore = modeCount[i];
      mode = i;
    }
    center = center - modeCount[i];
    if (center < 0 && flag == 0) {
      median = i;
      flag = 1;
    }
  }

  average = average / count;

  for (int i = 0; i < 256; i++) {
    variance = pow(i - average, 2) * modeCount[i];
  }

  variance /= count;

  std::cout << "Average      :" << average << "\n";
  std::cout << "Variance     :" << variance << "\n";
  std::cout << "Maximam value:" << max << "\n";
  std::cout << "Minimum value:" << min << "\n";
  std::cout << "Median       :" << median << "\n";
  std::cout << "Mode         :" << mode << "\n\n";

  std::cout << "Histgram\n";
  for (int i = 0; i < 256; i++) {
    printf("%3d:%5d\n", i, modeCount[i]);
  }
}

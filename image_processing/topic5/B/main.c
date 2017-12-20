#include <ppmload/ppmload.h>
//ppmload.h ppm処理ライブラリのインクルード

#define N 3
#define PI 3.1415926

void Affine(struct ppmimg *src, struct ppmimg *dst, double scalX, double scalY, double moveX, double moveY, double ang);
void MatrixMul1(double mat1[][N], int mat2[N], int ans[N]);
void MatrixMul2(double mat1[][N], double mat2[][N], double ans[][N]);

int main(void){
  double scalX, scalY, moveX, moveY, ang;
	struct ppmimg *img1 = NULL, *img2 = NULL;
	//struct ppmimg <= 画像を表す構造体
	//struct ppmimg *image1 = NULL ポインタだけ作る(NULLで初期化)

  printf("X軸拡大率："); scanf("%lf", &scalX);
  printf("Y軸拡大率："); scanf("%lf", &scalY);
  printf("X軸平行移動："); scanf("%lf", &moveX);
  printf("Y軸平行移動："); scanf("%lf", &moveY);
  printf("回転角："); scanf("%lf", &ang);

	img1 = makeimagestruct(img1);
	img2 = makeimagestruct(img2);

	loadppmimage("Default.ppm", img1);

  img2 = createppmimage(img2, img1->iwidth*scalX, img1->iheight*scalY, img1->cmode);

  Affine(img1, img2, scalX, scalY, moveX, moveY, -ang);

	saveppmimage(img2, "result.ppm");

	deleteppmimg(img1);
	deleteppmimg(img2);
}

//正方行列×１列の行列の乗算
void MatrixMul1(double mat1[][N], int mat2[N], int ans[N]) {
  int i, j;

  for (i = 0; i < N; i++) {
    ans[i] = 0;
    for (j = 0; j < N; j++) ans[i] += (int)(mat1[i][j] * mat2[j]);
  }
}

//正方行列×正方行列の乗算
void MatrixMul2(double mat1[][N], double mat2[][N], double ans[][N]){
	int i, j, k;

	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			ans[i][j] = 0;
			for (k = 0; k < N; k++) ans[i][j] += mat1[i][k] * mat2[k][j];
		}
	}
}

//アフィン変換　引数:(元画像, 変換後画像, x方向倍率, y方向倍率, x方向移動, y方向移動, 回転角)
//x方向倍率  : 2
//y方向倍率  : 1.5
//x方向移動  : 100
//y方向移動  : 50
//回転角     : 60
void Affine(struct ppmimg *src, struct ppmimg *dst, double scalX, double scalY, double moveX, double moveY, double ang) {
  int i, j;
  int ans[N] = { 0,0,0 };
  double mat0[N][N] = { { 0, 0, 0 },{ 0, 0, 0 },{ 0, 0, 0 } };
  double mat1[N][N] = { { 0, 0, 0 },{ 0, 0, 0 },{ 0, 0, 0 } };
  double scal[N][N] = { { scalX, 0, 0 },{ 0, scalY, 0 },{ 0, 0, 1 } };
  double move[N][N] = { { 1, 0, moveX },{ 0, 1, moveY },{ 0, 0, 1 } };
  double rot[N][N] = { { cos(PI*ang / 180), -sin(PI*ang / 180), 0 },{ sin(PI*ang / 180), cos(PI*ang / 180), 0 },{ 0, 0, 1 } };

  for (i = 0; i < src->iheight; i++) {
    for (j = 0; j < src->iwidth; j++) {
      struct RGBColor cRgb = getPnmPixel(src, j, i);
      int mat[N] = { j, i, 1 };
      MatrixMul2(scal, move, mat0);
      MatrixMul2(mat0, rot, mat1);
      MatrixMul1(mat1, mat, ans);

      if (0 < ans[0] && ans[0] < dst->iwidth && 0 < ans[1] && ans[1] < dst->iheight)
        setPnmPixel(dst, ans[0], ans[1], cRgb);
    }
  }
}

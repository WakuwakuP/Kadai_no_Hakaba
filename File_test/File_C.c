#include <stdio.h>
#include <stdlib.h>

int IsBinaryFile( const char* FileName){
	FILE*	pFILE;
	int 	c;

	if( NULL == FileName)
	{
		return -1;
	}

	if((pFILE = fopen( FileName, "rb" )) == NULL){
		return -1;
	}
	while((c = fgetc( pFILE )) != EOF){
		if( c <= 8 ){
			// アスキーコードの08H以下が検出されたので、おそらくバイナリファイルでしょう。
			fclose( pFILE );
			return 1;
		}
	}
	fclose( pFILE );
	return 0;
}

int main(int argc, char const *argv[]){
	FILE *r_fp, *w_fp;
	int mode;
	const char* tmp;
	int character;

	/* ファイル指定忘れ判定 */
	if (argc == 3){
		/* Fileの読み込みとエラー判定 */
		mode = IsBinaryFile(argv[1]);
		if (-1 == mode){ /* ファイルがなかった場合の終了処理 */
			printf("File open error!\n");
			exit(EXIT_FAILURE);
		}else if(0 == mode){ /* ファイルがASCII形式の場合の処理 */
			/* ファイルが開けなかった場合の終了処理 */
			if((r_fp = fopen(argv[1], "r")) == NULL){
				printf("file open error!!\n");
				exit(EXIT_FAILURE);
			}
			/* ファイル読み書きの処理部 */
			w_fp = fopen(argv[2], "w");
			while((fscanf(r_fp, "%d", &tmp)) != EOF){
				fprintf(w_fp, "%d\n", tmp);
			}
		}else if(1 == mode){ /* ファイルがbinary形式の場合の処理 */
			/* ファイルが開けなかった場合の終了処理 */
			if((r_fp = fopen(argv[1], "rb")) == NULL){
				printf("file open error!!\n");
				exit(EXIT_FAILURE);
			}
			/* ファイル読み書きの処理部 */
			w_fp = fopen(argv[2], "wb");
			while(EOF != (character = fgetc(r_fp))){
				fputc(character, w_fp);
			}
		}
		fclose(r_fp);
		fclose(w_fp);
	}else{
		printf("No file specification.\n");
	}
	return 0;
}
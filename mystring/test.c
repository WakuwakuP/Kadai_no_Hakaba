#include <stdio.h>
#include "mystring.h"

int main (){
	char str[] = "Wakuwaku";
	char strc[11];
	int iRet;

	printf("%d\n", mystrlen(str));
	printf("%s\n%s\n", mystrcpy(strc, str), strc);
	printf("%s\n%s\n", mystrcat(str, "P"), str);

  iRet = mystrcmp( "12345" , "12345" );
  printf( "iRet=%d\n" , iRet );

  iRet = mystrcmp( "12346" , "12345" );
  printf( "iRet=%d\n" , iRet );

  iRet = mystrcmp( "12345" , "12346" );
  printf( "iRet=%d\n" , iRet );

  iRet = mystrcmp( "123450" , "12345" );
  printf( "iRet=%d\n" , iRet );

  iRet = mystrcmp( "12345" , "123450" );
  printf( "iRet=%d\n" , iRet );
	return 0;
}
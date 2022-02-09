/*
01. 공백 있는 문자열을 입력받아서 문자 수만큼 오른쪽으로 한 바퀴 회전하여
	출력하는 프로그램을 작성하시오.
	단, 문자열의 길이는 100 이하이다.

	문자열 입력 >> PROGRAM
	MPROGRA
	AMPROGR
	RAMPROG
	GRAMPRO
	OGRAMPR
	ROGRAMP
	PROGRAM
*/

#include <stdio.h>
#include <string.h>

#define POINTER_SOLUTION
//#define ARRAY_SOLUTION

int main() {
	char str[100];
	int i, length;

	printf("문자열 입력 >> ");
	fgets(str, 99, stdin);  // \0

	length = (int)strlen(str); // strlen은 size_t가 나오고, size_t는 unsigned __int64
	str[length - 1] = '\0'; // 맨 마지막에 \n까지 같이 넣어 주기 때문!
	length = (int)strlen(str);

	printf("%d \n", length);
	for (i = 0; i < length; i++) { // line
#ifdef ARRAY_SOLUTION
		int j = 0;
		for (j = length - i - 1; str[j] != '\0'; j++) { // 앞 부분
			printf("%c", str[j]);
		}

		for (j = 0; j < length - i - 1; j++) { // 뒷 부분
			printf("%c", str[j]);
		}
#endif
#ifdef POINTER_SOLUTION
		char* c = NULL;
		for (c = &str[length - i - 1]; *c != '\0'; c++) {
			printf("%c", *c);
		}

		for (c = str; c < &str[length - i - 1]; c++) { // 뒷 부분
			printf("%c", *c);
		}

#endif
		printf("\n");
	}

	return 0;
}
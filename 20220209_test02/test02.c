#include <stdio.h>
#include <stdlib.h>

void odd_magic_matrix(int** const arr, const int size);

int main() {
	int size, i, j;
	
	// 사용자가 n을 입력하는 부분
	printf("n by n? (n is odd number!) >> ");
	scanf("%d", &size);

	if (size % 2 == 0) { // 입력 조건 예외 처리
		printf("Error! n is odd number! ");
		return 1;
	}

	// 동적 메모리 할당 (2차원 배열)
	int** arr = (int**)malloc(sizeof(int*) * size);
	for (i = 0; i < size; i++) {
		arr[i] = (int*)malloc(sizeof(int) * size);
	}

	// 0으로 배열 초기화
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			arr[i][j] = 0;
		}
	}

	// 채우기
	odd_magic_matrix(arr, size);

	// 출력
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			printf("%2d ", arr[i][j]);
		}
		printf("\n");
	}

	// 동적 메모리 해제 (2차원 배열)
	for (i = 0; i < size; i++) {
		free(arr[i]);
	}
	free(arr);

	return 0;
}

void odd_magic_matrix(int** const arr, const int size) {
	int num = 1, row = size - 1, col = size / 2;   // 현재 위치
	arr[row][col] = num++;  // (1) 첫번째 시작 지점은 맨 아랫 줄에 중간으로 잡으면 된다. 

	while (num <= size * size) {
		int r = row, c = col; // 다음 위치
		r++; c++;        // (2) 다음 수를 현재 위치에서 한 줄 아래, 한 칸 우측에 둔다.

		if (r == size) { // (3) 만약, 현재 행에서 더 이상 다음 행으로 갈 수 없다면,
			r = 0;       //     첫번째 행으로 되돌아온다.
		}
		if (c == size) { // (3) 만약, 현재 열에서 더 이상 다음 열로 갈 수 없다면,
			c = 0;       //     첫번째 열로 되돌아온다.
		}

		if (arr[r][c] != 0) { // (4) 만약, 두고자 하는 위치에 이미 값이 존재하면,
			r = row;
			r--;      // 현재 위치로부터 한 줄 위에 같은 칸에 둔다.

			if (r == -1) // 만약 위쪽으로 넘어간다면?
				r = size - 1; // 마지막 행으로 넘어간다

			c = col; // 현재 열의 위치는 가만히 둬야 함 (위로만 올라가야 함)
		}

		row = r;
		col = c;  // 확정된 값 저장

		arr[row][col] = num++;
	}
}
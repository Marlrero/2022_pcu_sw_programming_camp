#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 100
// swapping 매크로 함수
#define SWAPPING(x, y, t) ( (t) = (x), (x) = (y), (y) = (t) )

void quick_sort(int* list, int left, int right);
int partition(int* list, int left, int right);

int main() {
    int list[MAX_SIZE];
    int i, j;
    char input[10];

    for (i = 0; i < MAX_SIZE; i++) {
        printf("숫자 입력(x를 입력하면 정렬하기): ");
        scanf("%s", input);

        if (strcmp(input, "x") == 0) {
            break;
        } else {
            list[i] = atoi(input);
        }
    }
    
    quick_sort(list, 0, i - 1);
    for (j = 0; j < i; j++) {
        printf("%d, ", list[j]);
    }
    printf("\n");

    return 0;
}

void quick_sort(int* list, int left, int right) {
    if (left < right) {
        int q = partition(list, left, right);
        quick_sort(list, left, q - 1);
        quick_sort(list, q + 1, right);
    }
}
int partition(int* list, int left, int right) {
    int pivot = list[left]; // 피벗을 첫 번째 요소로 가정
    int low = left, high = right + 1;
    int temp;

    // low와 high가 교차할 때까지 계속 반복
    do {
        // list[low]가 pivot보다 작으면 계속 low 증가
        do {
            low++;
        } while (low <= right && list[low] < pivot);

        // list[high]가 pivot보다 크면 계속 high 감소
        do {
            high--;
        } while (high >= low && list[high] > pivot);

        // low와 high가 아직 교차하지 않았다면
        // list[low]와 list[high]을 교환함
        if (low < high) {
            SWAPPING(list[low], list[high], temp);
        }
    } while (low < high);

    SWAPPING(list[left], list[high], temp); // list[left]와 list[high] 교환

    return high; // 피벗 위치 high 반환
}

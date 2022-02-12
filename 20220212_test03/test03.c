#include <stdio.h>
#include <stdlib.h>
#include <limits.h>  // pop, peek에서 비어있는 경우에 리턴하기 위해 INT_MAX 활용

// 문제 조건
typedef int element;

typedef struct StackNode {
    element item;
    struct StackNode* link; // 자기 참조 구조체로 뒤에 이를 동일하게 연결
} StackNode;

typedef struct {
    StackNode *top; // 스택의 상단
} LinkedStack;

void init(LinkedStack* s); // 스택을 초기화한다. (top과 관련)
int is_empty(LinkedStack* s); // 스택이 empty인지 검사한다.
void push(LinkedStack* s, element item); // 스택에 element를 삽입(push)한다.
element pop(LinkedStack* s); // 스택에 element를 삭제하고 이를 반환한다.
element peek(LinkedStack* s); // 스택에 top 값을 가져온다.
void display(LinkedStack* s, int stack_size); // 연결 리스트 순회 코드 (top부터)
void exit_preprocess(LinkedStack* s); // 종료 전 모두 pop하는 함수

int main() {
    LinkedStack s;
    int menu, input, stack_size = 0;

    init(&s);
    while (1) {
        printf("삽입 1, 삭제 2, 가져오기 3: ");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                scanf("%d", &input);
                push(&s, input);
                stack_size++;
                display(&s, stack_size);
                break;
            case 2:
                pop(&s);
                stack_size--;
                display(&s, stack_size);
                break;
            case 3:
                printf("%d\n", peek(&s));
                break;
            default:
                printf("프로그램을 종료합니다.");
                exit_preprocess(&s);
                exit(1);
        }
    }

    return 0;
}

void init(LinkedStack* s) { // 스택을 초기화한다. (top과 관련)
    s->top = NULL;
}

int is_empty(LinkedStack* s) { // 스택이 empty인지 검사한다.
    return (s->top == NULL);
}

void push(LinkedStack* s, element item) { // 스택에 element를 삽입(push)한다.
    StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
    if (temp == NULL) {
        fprintf(stderr, "메모리 할당 에러\n");
        return;
    } else {
        temp->item = item;   // 새로 만든 노드에 데이터 넣기
        temp->link = s->top; // 새로 맏든 노드에 다음은 이전 top이 대신함 (처음이면 NULL)
        s->top = temp;       // top포인터는 지금(최근) 추가한 것이 top!
    }
}

element pop(LinkedStack* s) { // 스택에 element를 삭제하고 이를 반환한다.
    if (is_empty(s)) {
        fprintf(stderr, "스택이 비어있습니다. 삭제할 수 없습니다!\n");
        return INT_MAX;
    } else {
        StackNode* temp = s->top;  // 가장 최근 것을 삭제하기 위해 뽑음
        element item = temp->item; // 내용물 return하기 위해 복사
        s->top = s->top->link;     // 연결 끊기
        free(temp);                // 끊어진 노드 free

        return item;
    }
}

element peek(LinkedStack* s) { // 스택에 top 값을 가져온다.
    if (is_empty(s)) {
        fprintf(stderr, "스택이 비어있습니다.\n");
        return INT_MAX;
    } else {
        return s->top->item;   // top 값 return
    }
}

void display(LinkedStack* s, int stack_size) { // 연결 리스트 순회 코드 (top부터)
    if (stack_size < 1) {
        printf("[, ]\n");
        return;
    }

    StackNode* cursor = s->top;
    element* print_arr = (element*)malloc(sizeof(element) * stack_size);
    int i;

    //printf("%d >> ", stack_size);
    for (i = 0; i < stack_size; i++) {
        print_arr[i] = cursor->item;
        cursor = cursor->link;
    }

    printf("[");
    for (i = stack_size - 1; i >= 0; i--) {
        printf("%d, ", print_arr[i]);
    }
    printf("]\n");
    free(print_arr);
}

void exit_preprocess(LinkedStack* s) { // 종료 전 모두 pop하는 함수
    while (is_empty(s)) {
        StackNode* temp = s->top;  // 가장 최근 것을 삭제하기 위해 뽑음
        element item = temp->item; // 내용물 return하기 위해 복사
        s->top = s->top->link;     // 연결 끊기
        free(temp);                // 끊어진 노드 free
    }
}
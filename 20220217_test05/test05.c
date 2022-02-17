#include <stdio.h>
#include <stdlib.h>
#include <limits.h>  // dequeue, peek에서 비어있는 경우에 리턴하기 위해 INT_MAX 활용

// 문제 조건
typedef int element;
typedef struct QueueNode {
    element item;
    struct QueueNode* link;
} QueueNode;
typedef struct {
    QueueNode* front;
    QueueNode* rear;
} QueueType;

void init(QueueType* q); // 큐를 초기화한다. (front와 rear 포인터와 관련됨)
int is_empty(QueueType* q); // 큐가 비어있는지 검사한다.
void enqueue(QueueType* q, element item); // 삽입 연산
element dequeue(QueueType* q); // 삭제 연산
element peek(QueueType* q);  // 앞에 있는 요소를 삭제하지 않고 반환
void display(QueueType* q);
void exit_preprocess(QueueType* q);

int main() {
    QueueType q;
    int menu, input;

    init(&q);
    while (1) {
        printf("삽입 1, 삭제 2, 가져오기 3: ");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                scanf("%d", &input);
                enqueue(&q, input);
                display(&q);
                break;
            case 2:
                dequeue(&q);
                if (!is_empty(&q)) {
                    display(&q);
                }
                break;
            case 3:
                printf("%d\n", peek(&q));
                break;
            default:
                printf("프로그램을 종료합니다.\n");
                exit_preprocess(&q);
                exit(1);
        }
    }

    return 0;
}

void init(QueueType* q) { // 큐를 초기화한다. (front와 rear 포인터와 관련됨)
    q->front = q->rear = NULL;
}
int is_empty(QueueType* q){ // 큐가 비어있는지 검사한다.
    return (q->front == NULL);
}
void enqueue(QueueType* q, element item) { // 삽입 연산
    QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
    if (temp == NULL) {
        fprintf(stderr, "메모리 할당 에러\n");
        return;
    } else {
        temp->item = item;
        temp->link = NULL;
        if (is_empty(q)) { // 큐가 비어 있으면
            q->front = temp;
            q->rear = temp;
        } else {
            q->rear->link = temp; // 먼저 온 것에 다음이 새로 만든 노드가 됨 (순서)
            q->rear = temp;       // rear 포인터(큐의 맨 뒤)는 새로 만든 노드가 됨
        }
    }
}
element dequeue(QueueType* q) { // 삭제 연산
    QueueNode* temp = q->front;
    element item;
    if (is_empty(q)) {
        fprintf(stderr, "큐가 비어있습니다. 삭제할 수 없습니다!\n");
        return INT_MAX;
    } else {
        item = temp->item; // 리턴하기 위해 값을 임시 저장
        q->front = q->front->link; // front에서 빼야 하므로 그 다음 노드를 가리킴
        if (q->front == NULL) // 다음 노드를 가리키는데 이것이 NULL이라면
            q->rear = NULL;   // 공백 상태이므로 NULL로 함
        free(temp);
        return item;
    }
}
element peek(QueueType* q) {  // 앞에 있는 요소를 삭제하지 않고 반환
    if (is_empty(q)) {
        fprintf(stderr, "큐가 비어있습니다\n");
        return INT_MAX;
    } else {
        return q->front->item;
    }
}
void display(QueueType* q) {
    QueueNode* cur = q->front;
    printf("[");
    for (cur = q->front; cur != NULL; cur = cur->link) {
        printf("%d, ", cur->item);
    }
    printf("]\n");
}
void exit_preprocess(QueueType* q) {
    while (!is_empty(q)) { // 큐가 비어있지 않을 때까지
        dequeue(q);
    } 
}
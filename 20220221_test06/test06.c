#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 문제의 조건
#define MAX_QUEUE_SIZE 100
typedef struct {
    int id;
    int arrival_time;
    int service_time;
} element;

// 배열 형태의 큐 선언
typedef struct {
    element queue[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

void init(QueueType* q);
int is_empty(QueueType* q);
int is_full(QueueType* q); // 큐가 모두 채워져 있는지(포화상태인지) 검사
void enqueue(QueueType* q, element item);
element dequeue(QueueType* q);
element peek(QueueType* q);

QueueType q;
// 문제의 조건(시뮬레이션에 필요한 상태 변수)
const int duration = 10; // 시뮬레이션 시간
const double arrival_prob = 0.7; // 하나의 시간 단위에 도착하는 평균 고객 수
const int max_serv_time = 5; // 한 고객에 대한 최대 서비스 시간
int clock = 0;

// 문제의 조건(시뮬레이션 결과)
int customers = 0; // 전체 고객 수
int served_customers = 0; // 서비스받은 고객 수
int waited_time = 0; // 고객들이 기다린 시간

#define TRUE  1
#define FALSE 0
int is_customer_arrived(); // 랜덤한 숫자를 생성해 고객이 도착했는지를 판단
void insert_customer(int arrival_time); // 새로 도착한 고객을 큐에 삽입
int remove_customer(); // 큐에서 기다리는 고객을 꺼내 고객 서비스 시간 반환
void print_stat(); // 통계치 출력

int main() {
    int service_time = 0;

    while (clock < duration) {
        clock++;
        fprintf(stdout, "현재시각 = %d\n", clock);
        if (is_customer_arrived()) {
            insert_customer(clock);
        }

        if (service_time > 0)
            service_time--;
        else
            service_time = remove_customer(&q);
    }

    print_stat();
    return 0;
}

void init(QueueType* q) {
    q->front = q->rear = 0;
}
int is_empty(QueueType* q) {
    return (q->front == q->rear);
}
int is_full(QueueType* q) { // 큐가 모두 채워져 있는지(포화상태인지) 검사
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
void enqueue(QueueType* q, element item) {
    if (is_full(q)) {
        fprintf(stderr, "큐가 포화상태입니다.");
        return;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->queue[q->rear] = item;
}
element dequeue(QueueType* q) {
    if (is_empty(q)) {
        fprintf(stderr, "큐가 공백상태입니다.");
        element result = {-1, -1, -1};
        return result;
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->queue[q->front];
}
element peek(QueueType* q) {
    if (is_empty(q)) {
        fprintf(stderr, "큐가 공백상태입니다.");
        element result = {-1, -1, -1};
        return result;
    }
    return q->queue[(q->front + 1) % MAX_QUEUE_SIZE];
}
int is_customer_arrived() { // 랜덤한 숫자를 생성해 고객이 도착했는지를 판단
    //0과 1사이의 실수를 생성함
    int rand_num = rand() / (double)RAND_MAX;
    return (rand_num < arrival_prob) ? TRUE : FALSE;
}
void insert_customer(int arrival_time) { // 새로 도착한 고객을 큐에 삽입
    element new_customer;
    double rand_num = rand() / (double)RAND_MAX;

    new_customer.id = customers++;
    new_customer.arrival_time = arrival_time;
    new_customer.service_time = (int)(max_serv_time * rand_num) + 1;
    //printf("%d %d %d\n", new_customer.id, new_customer.arrival_time, new_customer.service_time);
    enqueue(&q, new_customer);

    fprintf(stdout, "고객 %d이 %d분에 들어옵니다. 서비스 시간은 %d분입니다.\n",
            new_customer.id, new_customer.arrival_time, new_customer.service_time);
}
int remove_customer() { // 큐에서 기다리는 고객을 꺼내 고객 서비스 시간 반환
    element del_customer;
    int service_time = 0;

    if (is_empty(&q))
        return -1;
    
    del_customer = dequeue(&q);
    //printf("%d %d %d \n", del_customer.id, del_customer.arrival_time, del_customer.service_time);
    service_time = del_customer.service_time - 1;
    
    served_customers++;
    waited_time += clock - del_customer.arrival_time;

    fprintf(stdout, "고객 %d이 %d분에 서비스를 시작합니다. 대기시간은 %d분이었습니다.\n",
            del_customer.id, clock, clock - del_customer.arrival_time);
    return service_time;
}
void print_stat() { // 통계치 출력
    fprintf(stdout, "서비스받은 고객의 수 = %d명\n", served_customers);
    //fprintf(stdout, "전체 대기 시간 = %d분\n", waited_time);
    fprintf(stdout, "1인당 평균 대기 시간 = %lf분\n", 
            (double)waited_time / served_customers);
    fprintf(stdout, "아직 대기중인 고객의 수 = %d명\n", customers - served_customers);
}
# 큐
## 문제
큐(Queue)는 먼저 들어온 데이터가 먼저 나가는 구조로,  
이러한 특성을 선입선출(FIFO: First-In First-Out)이라고 한다.
실생활에서 큐의 대표적인 예로는 표를 사기 위해 줄을 서는 것이라고 할 수 있다.
먼저 줄 앞에 서 있는 사람(가장 먼저 온 사람)이 가장 먼저 표를 살 수 있다.  
큐는 뒤에서 새로운 데이터가 추가되어 앞에서 데이터가 하나씩 삭제되는 구조를 가지고 있다.
구조상 큐와 스택이 다른 점은 스택의 경우 삽입과 삭제가 같은 공간에서 일어나지만,
큐에서는 삽입과 삭제가 다른 쪽에서 일어난다.
큐에서 삽입이 일어나는 곳을 rear라고 하고, 삭제가 일어나는 곳을 front라고 한다.
큐에서 삽입 연산을 enqueue라고 하고, 삭제 연산을 dequeue라고 한며,
큐에서 앞에 있는 요소를 삭제하지 않고 반환하는 것을 peek라고 한다.

큐는 컴퓨터공학에서 많이 사용되는 자료구조 중 하나로 다음과 같은 곳에서 사용된다.
- 프린터의 대기열(큐)
- 게임이나 은행 등의 시스템에 접속할 때의 대기열
- CPU 스케줄링

아래와 같이 연결리스트를 사용하여 Linked queue를 생성하시오.
- 요소의 타입은 int이다.  
    ```
    typedef int element;
    ```
- 큐의 노드의 타입은 아래와 같이 구조체로 정의된다.  
    ```
    typedef struct QueueNode {
        element item;
        struct QueueNode* link; // 자기 참조 구조체
    } QueueNode;
    ```
- 큐의 front 포인터와 rear 포인터도 구조체로 정의된다.
    ```
    typedef struct {
        QueueNode* front;
        QueueNode* rear;
    } QueueType
    ```
- 추상 자료형은 아래와 같이 함수로 정의된다.
    ```
    1. void init(QueueType* q); // 큐를 초기화한다. (front와 rear 포인터와 관련됨)
    2. is_empty(QueueType* q); // 큐가 비어있는지 검사한다.
    3. void enqueue(QueueType* q, element item); // 삽입 연산
    4. element dequeue(QueueType* q); // 삭제 연산
    5. element peek(QueueType* q);  // 앞에 있는 요소를 삭제하지 않고 반환
    ```

## 입력 예 및 출력 예
삽입 1, 삭제 2, 가져오기 3: 1 10  
[10, ]  
삽입 1, 삭제 2, 가져오기 3: 3  
10  
삽입 1, 삭제 2, 가져오기 3: 1 20  
[10, 20, ]  
삽입 1, 삭제 2, 가져오기 3: 2  
[20, ]  
삽입 1, 삭제 2, 가져오기 3: 2  
[, ]  
삽입 1, 삭제 2, 가져오기 3: 2   
큐가 비어있습니다. 삭제할 수 없습니다!
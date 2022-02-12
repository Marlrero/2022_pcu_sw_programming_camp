# 연결리스트를 활용한 스택
## 문제
스택(Stack)은 사전적 의미로 어떤 것을 쌓아놓은 형태의 더미를 의미한다. 어떤 물체를 쌓는다면 맨 윗부분부터 꺼낼 수 있고, 맨 아랫부분은 윗부분을 모두 꺼내야지만 꺼낼 수 있다.  따라서 가장 최근에 들어온 것이 가장 위에 있게 되고 그리고 먼저 나갈 수 있다. 이러한 구조 때문에 컴퓨터공학에서는 "후입 선출(LIFO: Last-In First-Out)" 구조라고 부르기도 한다. 이러한 스택 구조는 컴퓨터공학에서 자주 사용되는 자료구조 중 하나이다.  
스택의 상단은 top이라고 하고, 스택의 하단을 bottom이라고 한다. 또한 스택에 저장되는 것을 element라고 한다. 만약 스택에 element가 하나도 없다면 empty stack이라고 부른다. 스택에 삽입 연산을 push, 삭제 연산을 pop이라고 하며, 맨 위에 값을 가져올 때는 peek라고 한다.  
아래는 스택의 추상 자료형이며 아래에 따라 스택을 구현하라.

- element 자료형은 int이다.  
  ``` typedef int element; ```

- 스택에 저장되는 구조는 아래와 같다.  
  ``` 
    typedef struct StackNode {
        element item;
        struct StackNode* link; // 자기 참조 구조체로 뒤에 이를 동일하게 연결
    } StackNode;

    typedef struct {
        StackNode *top; // 스택의 상단
    } LinkedStack;
  ```
- 아래의 함수의 기능은 다음과 같다. (이를 자료 구조에서는 추상자료형(ADT: Abstract Data Type)라고 부른다.)
  1) void init(LinkedStack* s) : 스택을 초기화한다. (top과 관련)
  2) int is_empty(LinkedStack* s): 스택이 empty인지 검사한다.
  3) void push(LinkedStack* s, element item): 스택에 element를 삽입(push)한다.
  4) element pop(LinkedStack* s): 스택에 element를 삭제하고 이를 반환한다.
  5) element peek(LinkedStack* s): 스택에 top 값을 가져온다.

위와 같이 구조체, 구조체 포인터, 동적 메모리 할당 기법 등을 활용하여 문제를 해결하시오.

## 입력 예 및 출력 예
삽입 1, 삭제 2, 가져오기 3: 1 10  
[10, ]  
삽입 1, 삭제 2, 가져오기 3: 3  
10  
삽입 1, 삭제 2, 가져오기 3: 1 20  
[10, 20, ]  
삽입 1, 삭제 2, 가져오기 3: 2  
[10, ]  
삽입 1, 삭제 2, 가져오기 3: 2  
[, ]  
삽입 1, 삭제 2, 가져오기 3: 2  
스택이 비어있습니다. 삭제할 수 없습니다!
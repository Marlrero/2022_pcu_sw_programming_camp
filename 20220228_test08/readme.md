# 그래프의 표현
## 문제
그래프(Graph)는 연결되어 있는 객체 간 관계를 표현할 수 있는 자료구조이다.  

### 그래프의 활용 분야
그래프는 아래와 같은 알고리즘 구현 시 반드시 필요한 자료구조이다.  
- 깊이 우선 탐색과 너비 우선 탐색
- 최소 비용 신장 트리(Minimum Spanning Tree)
  - 프림, 크루스칼 알고리즘
  - 도로 건설이나 전기 회로, 통신 선, 배관 등을 최소가 되도록 구성할 때 사용
- 최단 경로 알고리즘 (다익스트라, 플로이드, 벨만포드, A* 등)
  - 지도 애플리케이션, 네트워크 장비인 라우터에서 사용됨
- 위상 정렬
  - 프로젝트를 나눌 때 어떤 작업이 선행되고나서 해야 함을 표현하기 위한 방향 그래프의 표현  
 

### 그래프의 정의와 용어
- 그래프는 정점(Vertex)과 간선(Edge)들의 집합으로 구성된다.
- 그래프를 수학적으로 G = (V, E)로 표현할 수 있다.
- V(G)는 그래프 G의 정점들의 집합, E(G)는 그래프 G의 간선들의 집합이다.
- 정점은 노드(Node)라고도 불리며, 간선은 링크(Link)라고도 표현된다.
- 그래프는 정점을 원으로 그리고, 간선은 선으로 연결된다. (시각적인 형태이며 정의는 아님)

### 그래프의 추상 데이터 타입
그래프를 프로그램으로 구현하기 위해 아래와 같은 추상 데이터 타입이 반드시 필요하다.
```
create_graph() ::= 그래프 생성
init(g) ::= 그래프 g 초기화
insert_vertex(g, v) ::= 그래프 g에 정점 v를 삽입
insert_edge(g, u, v) ::= 그래프 g에 간선 (u, v)를 삽입
```

### 그래프의 표현(구현) 방법
그래프를 표현하는 방법은 크게 2가지가 있다.
1) 인접 행렬(adjacency matrix)  
    - 2차원 배열 M을 이용하는 방법으로 아래와 같은 알고리즘에 의해 표현된다.
        ```
        if (간선 (i, j)가 그래프에 존재)
            M[i][j] = 1
        otherwise
            M[i][j] = 0
        ```
    - 예시
        ```
        0 ----- 3
        | \     |
        |  \    |
        |   \   |
        |    \  |
        |     \ |
        |      \|
        1 ----- 2
        ```
        |M|0|1|2|3|
        |-|-|-|-|-|
        |0|0|1|1|1|
        |1|1|0|1|0|
        |2|1|1|0|1|
        |3|1|0|1|0|
    - 추상 데이터 구현을 위한 구조체
        ```
        #define MAX_VERTICES 50
        typedef struct GraphType {
            int n; // 정점 개수
            int adj_mat[MAX_VERTICES][MAX_VERTICES];
        } GraphType;
        ```
2) 인접 리스트(adjacency list)
    - 그래프를 표현할 때 연결리스트로 표현한 방식이다.
    - 예시 (그림은 인접행렬과 같음)
        ```
            []는 연결리스트의 노드이고, ->는 링크임
            0 [] -> [1] -> [2] -> [3]
            1 [] -> [0] -> [2]
            2 [] -> [0] -> [1] -> [3]
            3 [] -> [0] -> [2]
        ```
    - 추상 데이터 구현을 위한 구조체
        ```
        #define MAX_VERTICES 50
        typedef struct GraphNode {
            int vertex;
            struct GraphNode* link; // 자기 참조 구조체
        } GraphNode;
        typedef struct GraphType {
            int n; // 정점 개수
            GraphNode* adj_list[MAX_VERTICES];
        } GraphType;
        ```

위와 같이 인접 행렬이나 인접 리스트를 골라서 그래프의 추상 데이터 타입(4가지 함수)를 구조체에 맞게 구현하시오.

## 입력 예 및 출력 예
입출력 예가 없음.  
그래프를 시각적으로 표현하기 어려움.   
위 알고리즘에 맞게 구현만 할 것.
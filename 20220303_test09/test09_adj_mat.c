#include <stdio.h>

#define MAX_VERTICES 50

typedef struct GraphTypeMat {
    int n; // 정점의 개수
    int adj_mat[MAX_VERTICES][MAX_VERTICES]; // 인접행렬
} GraphTypeMat;

void graph_init_mat(GraphTypeMat* g);
void insert_vertex_mat(GraphTypeMat* g, int v);
void insert_edge_mat(GraphTypeMat* g, int start, int end);
void display_mat(GraphTypeMat* g);

// dfs
#define TRUE  1
#define FALSE 0
int visited_dfs[MAX_VERTICES];
void dfs_mat(GraphTypeMat* g, int v) {
    int u;
    visited_dfs[v] = TRUE;   // v를 방문했다고 표시
    printf("%d -> ", v);
    for (u = 0; u < g->n; u++) { // 인접 노드 탐색
        // u가 아직 방문하지 않았으면
        if (g->adj_mat[v][u] && !visited_dfs[u]) {
            dfs_mat(g, u); // 정점 u에서 DFS 재귀 호출
        }
    }
}

// bfs (linear queue)
#include <limits.h>
typedef int element;
typedef struct {
    int queue[MAX_VERTICES];
    int front, rear;
} QueueType;

void init(QueueType* q); // 큐를 초기화한다. (front와 rear 포인터와 관련됨)
int is_empty(QueueType* q); // 큐가 비어있는지 검사한다.
int is_full(QueueType* q); // 큐가 차있는지 검사한다.
void enqueue(QueueType* q, element item); // 삽입 연산
element dequeue(QueueType* q); // 삭제 연산

int visited_bfs[MAX_VERTICES];
void bfs_mat(GraphTypeMat* g, int v) {
    int u;
    QueueType q;
    init(&q);
    
    visited_bfs[v] = TRUE; // v를 방문했다고 표시
    enqueue(&q, v);  // 큐에 노드 v를 삽입
    printf("%d -> ", v);

    while (!is_empty(&q)) {
        v = dequeue(&q); // 큐에서 노드 추출
        for (u = 0; u < g->n; u++) { // 인접 노드 탐색
            // u가 아직 방문되지 않았으면
            if (g->adj_mat[v][u] && !visited_bfs[u]) {
                enqueue(&q, u); // 큐에 삽입
                visited_bfs[u] = TRUE; // 방문 표시
                printf("%d -> ", u);
            }
        }
    }
}

int main() {
    GraphTypeMat g;

    graph_init_mat(&g);

    insert_vertex_mat(&g, 0);
    insert_vertex_mat(&g, 1);
    insert_vertex_mat(&g, 2);
    insert_vertex_mat(&g, 3);
    insert_vertex_mat(&g, 4);

    insert_edge_mat(&g, 0, 1);
    insert_edge_mat(&g, 0, 2);
    insert_edge_mat(&g, 0, 4);
    insert_edge_mat(&g, 1, 2);
    insert_edge_mat(&g, 2, 3);
    insert_edge_mat(&g, 2, 4);
    insert_edge_mat(&g, 3, 4);

    display_mat(&g);

    printf("DFS: ");
    dfs_mat(&g, 0);
    printf("\n");

    printf("BFS: ");
    bfs_mat(&g, 0);
    printf("\n");

    return 0;
}

void graph_init_mat(GraphTypeMat* g) {
    int r, c;
    g->n = 0;

    for (r = 0; r < MAX_VERTICES; r++) {
        for (c = 0; c < MAX_VERTICES; c++) {
            g->adj_mat[r][c] = 0;
        }
    }
}

void insert_vertex_mat(GraphTypeMat* g, int v) {
    if ( ((g->n)+1) > MAX_VERTICES ) {
        fprintf(stderr, "그래프 정점 개수 초과!");
        return;
    }
    g->n++;
}

void insert_edge_mat(GraphTypeMat* g, int start, int end) {
    if (start >= g->n || end >= g->n) {
        fprintf(stderr, "그래프 정점 번호 오류!");
        return;
    }
    g->adj_mat[start][end] = g->adj_mat[end][start] = 1;
}

void display_mat(GraphTypeMat* g) {
    int r, c;

    for (r = 0; r < g->n; r++) {
        for (c = 0; c < g->n; c++) {
            printf("%d ", g->adj_mat[r][c]);
        }
        printf("\n");
    }
}

void init(QueueType* q) {
    q->front = q->rear = -1;
}

int is_empty(QueueType* q) {
    return (q->front == q->rear) ? TRUE : FALSE;
}

int is_full(QueueType* q) {
    return (q->rear == MAX_VERTICES - 1) ? TRUE : FALSE;
}

void enqueue(QueueType* q, element item) {
    if (is_full(q)) {
        return;
    }
    q->rear++;
    q->queue[q->rear] = item;
}

element dequeue(QueueType* q) {
    if (is_empty(q)) {
        return INT_MIN;
    }
    element item = q->queue[q->front];
    q->front++;  // 배열에 있는 값을 제거해도 됨
    return item;
}
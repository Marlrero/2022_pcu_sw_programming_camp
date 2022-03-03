#include <stdio.h>

#include <stdlib.h>
#define MAX_VERTICES 50
//#define FREE(X) free(X); X = NULL;

typedef struct GraphNode {
    int vertex; // 정점
    struct GraphNode* link; // 자기참조구조체
} GraphNode;

typedef struct GraphTypeList {
    int n; // 정점의 개수
    struct GraphNode* adj_list[MAX_VERTICES];
} GraphTypeList;

void graph_init_list(GraphTypeList* g);
void insert_vertex_list(GraphTypeList* g, int v);
void insert_edge_list(GraphTypeList* g, int start, int end);
void destroy_graph_list(GraphTypeList* g);
void display_list(GraphTypeList* g);

// dfs
#define TRUE  1
#define FALSE 0
int visited_dfs[MAX_VERTICES];
void dfs_list(GraphTypeList* g, int v) {
    GraphNode* u;
    visited_dfs[v] = TRUE;   // v를 방문했다고 표시
    printf("%d -> ", v);
    for (u = g->adj_list[v]; u != NULL; u = u->link) { // 인접 노드 탐색
        // u가 아직 방문하지 않았으면
        if (!visited_dfs[u->vertex]) {
            dfs_list(g, u->vertex); // 정점 u에서 DFS 재귀 호출
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
void bfs_list(GraphTypeList* g, int v) {
    GraphNode* u;
    QueueType q;
    init(&q);
    
    visited_bfs[v] = TRUE; // v를 방문했다고 표시
    enqueue(&q, v);  // 큐에 노드 v를 삽입
    printf("%d -> ", v);

    while (!is_empty(&q)) {
        v = dequeue(&q); // 큐에서 노드 추출
        for (u = g->adj_list[v]; u != NULL; u = u->link) { // 인접 노드 탐색
            // u가 아직 방문되지 않았으면
            if (!visited_bfs[u->vertex]) {
                enqueue(&q, u->vertex); // 큐에 삽입
                visited_bfs[u->vertex] = TRUE; // 방문 표시
                printf("%d -> ", u->vertex);
            }
        }
    }
}

int main() {
    GraphTypeList g;

    graph_init_list(&g);

    insert_vertex_list(&g, 0);
    insert_vertex_list(&g, 1);
    insert_vertex_list(&g, 2);
    insert_vertex_list(&g, 3);
    insert_vertex_list(&g, 4);

    insert_edge_list(&g, 0, 1);
    insert_edge_list(&g, 0, 2);
    insert_edge_list(&g, 0, 4);
    insert_edge_list(&g, 1, 2);
    insert_edge_list(&g, 2, 3);
    insert_edge_list(&g, 2, 4);
    insert_edge_list(&g, 3, 4);

    display_list(&g);

    printf("DFS: ");
    dfs_list(&g, 0);
    printf("\n");

    printf("BFS: ");
    bfs_list(&g, 0);
    printf("\n");

    destroy_graph_list(&g);

    return 0;
}

void graph_init_list(GraphTypeList* g) {
    int v;
    g->n = 0;

    for (v = 0; v < MAX_VERTICES; v++) {
        g->adj_list[v] = NULL;
    }
}

void insert_vertex_list(GraphTypeList* g, int v) {
    if ( ((g->n)+1) > MAX_VERTICES ) {
        fprintf(stderr, "그래프 정점 개수 초과!");
        return;
    }
    g->n++;
}

void insert_edge_list(GraphTypeList* g, int start, int end) {
    GraphNode* node;
    if (start >= g->n || end >= g->n) {
        fprintf(stderr, "그래프 정점 번호 오류!");
        return;
    }
    
    // 뒤에다가 넣는 것으로 변경
    node = (GraphNode*)malloc(sizeof(GraphNode));
    node->vertex = end;
    node->link = NULL;

    if (g->adj_list[start] == NULL) {
        g->adj_list[start] = node;
        return;
    }

    GraphNode* cur, *last;
    for (cur = g->adj_list[start]; cur != NULL; cur = cur = cur->link) {
        if (cur->link == NULL) { // 마지막 노드이면
            last = cur;
        }
    }
    last->link = node;
}

void destroy_graph_list(GraphTypeList* g) {
    int i;
    GraphNode* cur, *temp;

    for (i = 0; i < (g->n) - 1; i++) {
        for (cur = g->adj_list[i]; cur != NULL; cur = temp) {
            temp = cur->link;
            free(cur);
        }
    }
}

void display_list(GraphTypeList* g) {
    int i;
    GraphNode* cur;

    for (i = 0; i < g->n; i++) {
        printf("[%d] -> ", i);
        for (cur = g->adj_list[i]; cur != NULL; cur = cur->link) {
            printf("%d -> ", cur->vertex);
        }
        printf("NULL\n");
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
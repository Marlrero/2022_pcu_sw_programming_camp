#include <stdio.h>
#include "GraphTypeList.h"

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
    
    node = (GraphNode*)malloc(sizeof(GraphNode));
    node->vertex = end;
    node->link = g->adj_list[start];
    // 삽입을 쉽게 하기 위해 위치는 상관없으므로 연결리스트 맨 앞에서 삽입
    g->adj_list[start] = node;
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
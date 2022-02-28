#ifndef __GRAPHTYPELIST_H__
#define __GRAPHTYPELIST_H__

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

#endif
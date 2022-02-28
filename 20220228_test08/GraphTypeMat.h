#ifndef __GRAPHTYPEMAT_H__
#define __GRAPHTYPEMAT_H__

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

#endif
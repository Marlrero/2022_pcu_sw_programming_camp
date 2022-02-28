#include <stdio.h>
#include "GraphTypeMat.h"

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
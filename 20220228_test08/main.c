//#define GRAPHTYPEMAT
#define GRAPHTYPELIST

#ifdef GRAPHTYPEMAT
#include "GraphTypeMat.h"
#endif

#ifdef GRAPHTYPELIST
#include "GraphTypeList.h"
#endif

int main() {
#ifdef GRAPHTYPEMAT
    GraphTypeMat graph;
#endif

#ifdef GRAPHTYPELIST
    GraphTypeList graph;
#endif

#ifdef GRAPHTYPEMAT
	graph_init_mat(&graph);

	// 정점 삽입 (0, 1, 2, 3)
	insert_vertex_mat(&graph, 0);
	insert_vertex_mat(&graph, 1);
	insert_vertex_mat(&graph, 2);
	insert_vertex_mat(&graph, 3);

	// 간선 삽입
	insert_edge_mat(&graph, 0, 1);
	insert_edge_mat(&graph, 0, 2);
	insert_edge_mat(&graph, 0, 3);

	insert_edge_mat(&graph, 1, 0);
	insert_edge_mat(&graph, 1, 2);

	insert_edge_mat(&graph, 2, 0);
	insert_edge_mat(&graph, 2, 1);
    insert_edge_mat(&graph, 2, 3);

	insert_edge_mat(&graph, 3, 0);
    insert_edge_mat(&graph, 3, 2);

    display_mat(&graph);
#endif

#ifdef GRAPHTYPELIST
	graph_init_list(&graph);

	// 정점 삽입 (0, 1, 2, 3)
	insert_vertex_list(&graph, 0);
	insert_vertex_list(&graph, 1);
	insert_vertex_list(&graph, 2);
	insert_vertex_list(&graph, 3);

	// 간선 삽입
	insert_edge_list(&graph, 0, 1);
	insert_edge_list(&graph, 0, 2);
	insert_edge_list(&graph, 0, 3);

	insert_edge_list(&graph, 1, 0);
	insert_edge_list(&graph, 1, 2);

	insert_edge_list(&graph, 2, 0);
	insert_edge_list(&graph, 2, 1);
    insert_edge_list(&graph, 2, 3);

	insert_edge_list(&graph, 3, 0);
    insert_edge_list(&graph, 3, 2);

    display_list(&graph);
	destroy_graph_list(&graph);
#endif

    return 0;
}
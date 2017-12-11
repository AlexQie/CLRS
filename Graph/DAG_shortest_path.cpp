#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <map>
#include <queue>
#include <memory.h>

using namespace std;

const int NIL = 100000;

struct Edge{
    int weight;
    int to_vertex;
    Edge* next;

    Edge(): weight(0), next(nullptr) { };
    Edge(int ver, int w): weight(w), to_vertex(ver), next(nullptr) { };
};

struct Vertex{
    int data;
    int s_pre, d;
    Edge* edge;

    Vertex(): data(0), edge(nullptr) { };
};

struct TP_Node{
    int vertex_index;
    TP_Node* next;
};

struct TP_List{
    TP_Node* head;
};

void add_edge(vector<Vertex>& G, int s, int e, int w){
    Edge* cur_edge = new Edge(e, w);
    cur_edge->next = G[s].edge;
    G[s].edge = cur_edge;
}

vector<Vertex> build_graph(){
    int ver_n;
    cin >> ver_n;
    vector<Vertex> G(ver_n);

    int edge_n;
    cin >> edge_n;
    for (int i = 0; i < edge_n; ++i){
        int s, e, w;
        cin >> s >> e >> w;
        add_edge(G, s, e, w);
    }

    return G;
}

void DFS(const vector<Vertex>& G, int cur_vertex, TP_List* topo_list, vector<int>& visited){
    visited[cur_vertex] = 1;
    Edge* cur_edge = G[cur_vertex].edge;
    while (cur_edge){
        if (!visited[cur_edge->to_vertex]){
            DFS(G, cur_edge->to_vertex, topo_list, visited);
        }
        cur_edge = cur_edge->next;
    }

    ///Add this vertex to front of the topo_list
    TP_Node* new_node = new TP_Node;
    new_node->vertex_index = cur_vertex;
    new_node->next = topo_list->head;
    topo_list->head = new_node;
}

TP_List* topological_sort(const vector<Vertex>& G){
    TP_List* topo_list = new TP_List;
    topo_list->head = nullptr;
    vector<int> visited(G.size(), 0);
    for (size_t i = 0; i < G.size(); ++i){
        if (!visited[i]){
            DFS(G, i, topo_list, visited);
        }
    }

    return topo_list;
}

void print_graph(const vector<Vertex>& G){
    for (size_t i = 0; i < G.size(); ++i){
        cout << i << " ";
        Edge* cur_e = G[i].edge;
        while (cur_e != nullptr){
            cout << cur_e->to_vertex << " " << cur_e->weight << "   ";
            cur_e = cur_e->next;
        }
        cout << endl;
    }
}

void print_topological_sort(const vector<Vertex>& G){
    TP_List* tp_list = topological_sort(G);
    TP_Node* cur_node = tp_list->head;
    while (cur_node){
        cout << cur_node->vertex_index << " ";
        cur_node = cur_node->next;
    }
    cout << endl;
}

void initialize_single_source(vector<Vertex>& G, int s){
    for (size_t i = 0; i < G.size(); ++i){
        if (i == s){
            G[i].d = 0;
        }
        G[i].s_pre = NIL;
    }
}

void relax(vector<Vertex>& G, int u, int v, int w){
    if (G[u].d + w < G[v].d){
        G[v].d = G[u].d + w;
        G[v].s_pre = u;
    }
}

void DAG_shortest_path(vector<Vertex>& G, int s){
    TP_List* tp_list = topological_sort(G);
    initialize_single_source(G, s);
    TP_Node* cur_node = tp_list->head;
    while (cur_node){
        Edge* cur_edge = G[cur_node->vertex_index].edge;
        while (cur_edge){
            relax(G, cur_node->vertex_index, cur_edge->to_vertex, cur_edge->weight);
            cur_edge = cur_edge->next;
        }
        cur_node = cur_node->next;
    }
}

int main(){
    freopen("/home/qiechunguang/Desktop/study/cpp/algorithm_practice/algorithm_practice/test.in", "r", stdin);
    vector<Vertex> G(build_graph());
    print_graph(G);
    print_topological_sort(G);
    DAG_shortest_path(G, 0);
}

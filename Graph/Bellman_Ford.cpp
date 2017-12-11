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

void add_edge(vector<Vertex>& G, int s, int e, int w){
    Edge* cur_edge = new Edge(e, w);
    cur_edge->next = G[s].edge;
    G[s].edge = cur_edge;
}

vector<Vertex> build_graph(){
    int ver_n;
    cin >> ver_n;
    vector<Vertex> G(ver_n);
    /*
    for (int i = 0; i < ver_n; ++i){
        cin >> G[i].data;
    }
    */

    int edge_n;
    cin >> edge_n;
    for (int i = 0; i < edge_n; ++i){
        int s, e, w;
        cin >> s >> e >> w;
        add_edge(G, s, e, w);
    }

    return G;
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

void initialize_single_source(vector<Vertex>& G, int s){
    for (vector<Vertex>::iterator i = G.begin(); i != G.end(); ++i){
        i->s_pre = -1;
        i->d = NIL;
    }
    G[s].d = 0;
}

void relax(vector<Vertex>& G, int u, int v, int wuv){
    if (G[v].d > G[u].d + wuv){
        G[v].d = G[u].d + wuv;
        G[v].s_pre = u;
    }
}

bool Bellman_Ford(vector<Vertex>& G){
    for (size_t i = 1; i < G.size(); ++i){
        cout << "iter: " << i << endl;
        for (size_t vi = 0; vi < G.size(); ++vi){
            cout << vi << endl;
            Edge* cur_edge = G[vi].edge;

            while (cur_edge != nullptr){
                relax(G, vi, cur_edge->to_vertex, cur_edge->weight);
                cout << cur_edge->to_vertex << " " << cur_edge->weight << endl;
                cur_edge = cur_edge->next;
            }
            cout << "OK" << endl;
        }
        cout << "outer iter end" << endl;
    }

    cout << "OK";
    for (size_t vi = 0; vi < G.size(); ++vi){
        Edge* cur_edge = G[vi].edge;
        while (cur_edge){
            if (G[cur_edge->to_vertex].d < G[vi].d + cur_edge->weight)
                return false;
            cur_edge = cur_edge->next;
        }
    }


    return true;
}

int main(){
    freopen("/home/qiechunguang/Desktop/study/cpp/algorithm_practice/algorithm_practice/test.in", "r", stdin);
    vector<Vertex> G(build_graph());
    print_graph(G);
    Bellman_Ford(G);
}

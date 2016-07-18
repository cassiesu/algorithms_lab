#include <climits>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <queue>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS>::edge_descriptor Edge;
typedef adjacency_list<vecS, vecS, directedS, no_property,
		property<edge_capacity_t, int,
			property<edge_residual_capacity_t, int,
			property<edge_reverse_t, Edge> > > > Graph;
typedef property_map<Graph, edge_capacity_t>::type CapacityMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualMap;
typedef property_map<Graph, edge_reverse_t>::type ReverseMap;

Graph G;
CapacityMap capacity_map = get(edge_capacity, G);
ResidualMap residual_map = get(edge_residual_capacity, G);
ReverseMap reverse_map = get(edge_reverse, G);

inline void my_add_edge(int a, int b, int c) {
	Edge e1, e2;
	tie(e1, tuples::ignore) = add_edge(a, b, G);
	tie(e2, tuples::ignore) = add_edge(b, a, G);
	::capacity_map[e1] = c;
	reverse_map[e1] = e2;
	reverse_map[e2] = e1;
}

void testcase() {
	int N, M, K;
    int a,b;

	cin >> N >> M >> K;
	G = Graph(2*N*M+2);
    for (int i = 1; i <= N*M; ++i) {
        a = (i-1)/M+1;
        b = (i-1)%M+1;
        my_add_edge(i,N*M+i,1);
        if(a>1) my_add_edge(N*M+i,i-M,1);
        if(b>1) my_add_edge(N*M+i,i-1,1);
        if(a<N) my_add_edge(N*M+i,i+M,1);
        if(b<M) my_add_edge(N*M+i,i+1,1);
        if(a==1 || a==N || b==1 || b== M) {
            my_add_edge(i+N*M,N*M*2+1,1);
        }
    }
    for(int i=1;i<=K;i++) {
        cin >> a >> b;
        my_add_edge(0,a*M+b+1,1);
    }
    int f = push_relabel_max_flow(G, 0, 2*N*M+1);
    cout << f << endl;
}

int main() {
    ios::sync_with_stdio(false);
    int Z;
    cin >> Z;
    while (Z--) testcase();
}


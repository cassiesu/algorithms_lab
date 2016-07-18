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

std::queue<int> Q;
vector<int> vis;

inline void my_add_edge(int a, int b, int c) 
{
	Edge e1, e2;
	tie(e1, tuples::ignore) = add_edge(a, b, G);
	tie(e2, tuples::ignore) = add_edge(b, a, G);
	::capacity_map[e1] = c;
	reverse_map[e1] = e2;
	reverse_map[e2] = e1;
}

void testcase() 
{
	int N, M, S;
    int T;
    int dd;
    int a,b;

	cin >> N >> M >> S;
	G = Graph(N);
    for (int i = 1; i <= S; ++i)
    {
        cin >> T;
        my_add_edge(T,N,1);
    }
	for (int i = 1; i <= M; ++i) 
    {
		cin >> a >> b;
        my_add_edge(a,b,1);
        my_add_edge(b,a,1);
	}
	int best_source = -1, best_sink = -1, best_value = INT_MAX;
    int f = push_relabel_max_flow(G, 0, N);
    if(f>=S) puts("yes"); else puts("no");
}

int main() {
	ios::sync_with_stdio(false);
	int Z;
	cin >> Z;
	while (Z--) testcase();
}


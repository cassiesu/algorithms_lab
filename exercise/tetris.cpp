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
	int n, w;
    int a,b;

	cin >> w >> n;
	G = Graph(2*w);
    for (int i = 1; i <= n; ++i) {
        cin >> a >> b;
        if(a>b) swap(a,b);
        if (a==0)
            my_add_edge(a,b,1);
        else
            if(b==w)
                my_add_edge(a+w,w,1);
            else
                my_add_edge(a+w,b,1);
    }
    for(int i=1;i<w;i++)
        my_add_edge(i,i+w,1);
	int best_source = -1, best_sink = -1, best_value = INT_MAX;
    int f = push_relabel_max_flow(G, 0, w);
    cout << f << endl;
}

int main() {
	ios::sync_with_stdio(false);
	int Z;
	cin >> Z;
	while (Z--) testcase();
}


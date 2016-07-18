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

inline void my_add_edge(int a, int b, int c) {
	Edge e1, e2;
	tie(e1, tuples::ignore) = add_edge(a, b, G);
	tie(e2, tuples::ignore) = add_edge(b, a, G);
	::capacity_map[e1] = c;
	reverse_map[e1] = e2;
	reverse_map[e2] = e1;
}

void testcase() {
	int N, M;
    int out[250];
    int in[250];
    int deg[250];
    bool flag;
    int dd, dd2;

	cin >> N >> M;
	G = Graph(N);
    memset(out,0,sizeof(out));
    memset(in,0,sizeof(in));
    memset(deg,0,sizeof(deg));
	for (int i = 1; i <= M; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
        a++;b++;
        //my_add_edge(0,i,1);
		if (c==1) {
            my_add_edge(a, b, 1);
            out[a]++;
            in[b]++;
        }
		if (c==2) {
            my_add_edge(b, a, 1);
            out[b]++;
            in[a]++;
        }
        if (c==0) {
            deg[a]++;deg[b]++;
            my_add_edge(a, b, 1);
            my_add_edge(b, a, 1);
        }
	}
    dd=dd2=0;
    flag = 0;
    for(int i=1;i<=N;i++)
    {
        int s;
        cin >> s;
        if(s<out[i] || s-out[i]>deg[i]) flag = 1; 
        my_add_edge(0,i,s);
        dd2+=s;
        dd+=in[i]+deg[i]+out[i]-s;;
        my_add_edge(i,N+1,in[i]+deg[i]+out[i]-s);
    }
	
	int best_source = -1, best_sink = -1, best_value = INT_MAX;
    int f = push_relabel_max_flow(G, 0, N+1);
    if(!flag && f==dd && dd==dd2 && dd==M) puts("yes"); else puts("no");
}

int main() {
	ios::sync_with_stdio(false);
	int Z;
	cin >> Z;
	while (Z--) testcase();
}


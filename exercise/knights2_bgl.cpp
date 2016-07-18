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
	int N;
    bool v[4100];
    int a,b;
    int ans;

	cin >> N;
	G = Graph(N*N+2);
    memset(v,0,sizeof(v));
    ans = 0;
    for (int i = 1; i <= N*N; ++i)
    {
        a = (i-1)/N+1;
        b = (i-1)%N+1;
        cin >> v[i];
        if(v[i])
        {
            ans++;
            if((a+b)%2==0) my_add_edge(0,i,1);
            else my_add_edge(i,N*N+1,1);
        }
    }
    for(int i=1;i<=N*N;i++)
    {
        a = (i-1)/N+1;
        b = (i-1)%N+1;
        if(v[i] && (a+b)%2==0)
        {
            if(a>=3 && b>=2 && v[i-2*N-1])
                my_add_edge(i,i-2*N-1,1000);
            if (a>=2 && b>=3 && v[i-N-2])
                my_add_edge(i,i-N-2,1000);
            if (a>=2 && b<=N-2 && v[i-N+2]) 
                my_add_edge(i,i-N+2,1000);
            if (a>=3 && b<=N-1 && v[i-2*N+1])
                my_add_edge(i,i-2*N+1,1000);
            if(a<=N-2 && b<=N-1 && v[i+2*N+1])
                my_add_edge(i,i+2*N+1,1000);
            if (a<=N-1 && b<=N-2 && v[i+N+2])
                my_add_edge(i,i+N+2,1000);
            if (a<=N-1 && b>=3 && v[i+N-2]) 
                my_add_edge(i,i+N-2,1000);
            if (a<=N-2 && b>=2 && v[i+2*N-1])
                my_add_edge(i,i+2*N-1,1000);
        }
    }
    int f = push_relabel_max_flow(G, 0, N*N+1);
    cout << ans - f << endl;
}

int main() {
    ios::sync_with_stdio(false);
    int Z;
	cin >> Z;
	while (Z--) testcase();
}


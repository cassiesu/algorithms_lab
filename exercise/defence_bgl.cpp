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
int lft[550];

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
	int M, S;
    int T;
    int dd;
    int a,b,c;
    int total, total_;
    int l,p,g,d;

	cin >> T;
    while(T--)
    {
        cin >> l >> p;
        G = Graph(l+4);
        memset(lft,0,sizeof(lft));
        total=total_=0;
        for(int i=1;i<=l;i++)
        {
            cin >> g >> d;
            if(g-d>0)
            {
                my_add_edge(l+2,i,g-d);
            }
            else
            {
                my_add_edge(i,l+3,d-g);
                total+=d-g;
            }
        }
        for(int i=0;i<p;i++)
        {
            cin >> a >> b >> c >> d;
            if(a==b) continue;
            a++;b++;
            lft[a]-=c;
            lft[b]+=c;
            my_add_edge(a,b,d-c);
        }
        for(int i=1;i<=l;i++)
        {
            if(lft[i]>0)
            {
                total_+=lft[i];
                my_add_edge(0,i,lft[i]);
            }
            else
            {
                my_add_edge(i,l+1,-lft[i]);
            }
        }
        my_add_edge(l+2,0,1000000000);
        my_add_edge(l+1,l+3,1000000000);
        int best_source = -1, best_sink = -1, best_value = INT_MAX;
        int f = push_relabel_max_flow(G, l+2, l+3);
        if(f == total+total_) puts("yes"); else puts("no");
    }
}

int main() {
	ios::sync_with_stdio(false);
	testcase();
}


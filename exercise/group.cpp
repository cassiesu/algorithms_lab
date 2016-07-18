// Reference solution (2n+1 flow invocations).
#include <climits>
#include <algorithm>
#include <iostream>
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
	cin >> N >> M;
	G = Graph(N);
	for (int i = 0; i < M; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		my_add_edge(a, b, c);
	}
	
	int best_source = -1, best_sink = -1, best_value = INT_MAX;
	for (int u = 1; u < N; ++u) {
		int f = push_relabel_max_flow(G, 0, u);
		if (f < best_value) {
			best_value = f;
			best_source = 0;
			best_sink = u;
		}
		f = push_relabel_max_flow(G, u, 0);
		if (f < best_value) {
			best_value = f;
			best_source = u;
			best_sink = 0;
		}
	}
	// Don't forget to call the flow again for best_source and best_sink
	push_relabel_max_flow(G, best_source, best_sink);  
	
	vis = vector<int>(N, false);
	vis[best_source] = true;
	Q.push(best_source);
	while (!Q.empty()) {
		const int u = Q.front();
		Q.pop();
		graph_traits<Graph>::out_edge_iterator ebeg, eend;
		for (tie(ebeg, eend) = out_edges(u, G); ebeg != eend; ++ebeg) {
			const int v = target(*ebeg, G);
			if (residual_map[*ebeg] == 0 || vis[v]) continue;
			vis[v] = true;
			Q.push(v);
		}
	}
	
	cout << best_value << '\n' << count(vis.begin(), vis.end(), true);
	for (int u = 0; u < N; ++u) if (vis[u]) cout << ' ' << u;
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	int Z;
	cin >> Z;
	while (Z--) testcase();
}

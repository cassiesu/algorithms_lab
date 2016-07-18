// Deleted entries: BGL DFS + C-style I/O.
#include <cstdio>
#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/undirected_dfs.hpp>
using namespace std;
using namespace boost;

const int NMAX = 1000000;

typedef adjacency_list<vecS, vecS, undirectedS,
	no_property,
	property<edge_color_t, int> > Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;

bool connected;
int color[NMAX];

// Have a look at undirected_dfs documentation to see when start_vertex() and
// tree_edge() are called.
struct CustomVisitor : public default_dfs_visitor {
	void start_vertex(int u, const Graph&) {
		if (u != 0) connected = false;
		color[u] = 0;
	}
	void tree_edge(Edge e, const Graph& g) {
		const int u = source(e, g), v = target(e, g);
		color[v] = (color[u]+1)%2;
	}
};

void testcase() {
	int N, M, K;
	scanf("%d%d%d", &N, &M, &K);
	Graph G(N);
	for (int i = 0; i < M; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		add_edge(a, b, G);
	}
	
	connected = true;
	undirected_dfs(G,
		visitor(CustomVisitor()).
		edge_color_map(get(edge_color, G))  // There is no default for edge_color_map,
	);                                      // which is stupid, but at least it is 
                                            // documented.
	
	if (!connected || N < K) {
		printf("no\n");
		return;
	}
	
	// Ad hoc for introducing single-element color classes. Exercise: understand it.
	bool seen[2] = {false, false}; 
	for (int u = 0, c = 2; c < K; ++u) {
		if (!seen[color[u]]) seen[color[u]] = true;
		else color[u] = c++;
	}
	
	printf("yes\n");
	for (int c = 0; c < 2; ++c) {
		printf("%ld", count(color, color+N, c));
		for (int u = 0; u < N; ++u) if (color[u] == c)
			printf(" %d", u);
		putchar('\n');
	}
	// There might be a lot of color classes, we use a trick to keep it O(n).
	for (int u = 0, c = 2; c < K; ++u) {
		if (color[u] != c) continue;
		printf("1 %d\n", u);
		++c;
	}
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) testcase();
}


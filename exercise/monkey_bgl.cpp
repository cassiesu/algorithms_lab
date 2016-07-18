#include <boost/config.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/strong_components.hpp>

using namespace std;
using namespace boost;

void testcase() {
    typedef adjacency_list <vecS, vecS, undirectedS> Graph;
    int N,M, a,b;
    int C[1010];
    bool mat[1010][1010];
    int ans;
    int v[1010];
    int in[1010];

    cin >> N >> M;
    memset(in,0,sizeof(in));
    memset(mat,0,sizeof(mat));
    adjacency_list<vecS, vecS, directedS> G(N);
    for(int i=0;i<M;i++) {
        cin >> a >> b;
        a--;b--;
        mat[a][b]=1;
        add_edge(a, b, G);
    }
    for(int i=0;i<N;i++)
        cin >> C[i];
    typedef graph_traits<adjacency_list<vecS, vecS, directedS> >::vertex_descriptor Vertex;

    std::vector<int> component(num_vertices(G)), discover_time(num_vertices(G));
    std::vector<default_color_type> color(num_vertices(G));
    std::vector<Vertex> root(num_vertices(G));
    int num = strong_components(G, make_iterator_property_map(component.begin(), get(vertex_index, G)), 
            root_map(make_iterator_property_map(root.begin(), get(vertex_index, G))).
            color_map(make_iterator_property_map(color.begin(), get(vertex_index, G))).
            discover_time_map(make_iterator_property_map(discover_time.begin(), get(vertex_index, G))));
    memset(v,-1,sizeof(v));
    for(int i=0;i<N;i++)
        if (v[component[i]]==-1 || v[component[i]]>C[i]) v[component[i]]=C[i];
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++) {
            if(mat[i][j] && component[i]!=component[j]) {
                in[component[j]]++;
            }
        }
    ans = 0;
    for (int i = 0; i != num; ++i) {
        if(in[i]==0) 
            ans+=v[i];
    }
    cout << ans << endl;
}

int main() {
	ios::sync_with_stdio(false);
	int Z;
	cin >> Z;
	while (Z--) testcase();
    return 0;
}


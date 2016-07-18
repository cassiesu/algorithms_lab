#include <string>
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <boost/graph/max_cardinality_matching.hpp>


using namespace boost;
using namespace std;

typedef adjacency_list<vecS, vecS, undirectedS> my_graph; 

void testcase() {
    int black, white;
    int sum;
    char ch;
    int mat[2510];
    int w,h,ans;

    cin >> w >> h;
    my_graph g(w*h);
    memset(mat,0,sizeof(mat));
    sum=0;
    for(int i=0;i<h;i++)
        for(int j=0;j<w;j++) {
            cin >> ch;
            while(ch!='.'&&ch!='x') cin >> ch;
            if(ch=='.') {
                sum++;
                mat[i*w+j]=1;
                if(j>0 && mat[i*w+j-1]) {
                    add_edge(i*w+j,i*w+j-1,g);
                    add_edge(i*w+j-1,i*w+j,g);
                }
                if(i>0 && mat[i*w-w+j]) {
                    add_edge(i*w+j,i*w-w+j,g);
                    add_edge(i*w-w+j,i*w+j,g);
                }
            }
        }

    std::vector<graph_traits<my_graph>::vertex_descriptor> mate(w*h);

    bool success = checked_edmonds_maximum_cardinality_matching(g, &mate[0]);
    assert(success);

    ans = matching_size(g, &mate[0]);

    if(ans*2==sum) puts("yes"); else puts("no");
}

int main() {
    int Z;
    ios::sync_with_stdio(false);
    cin >> Z;
    while(Z--) {
        testcase();
    }
    return 0;
}


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

int main()
{
    int n,c,f,t;
    int ans;
    string s[410][20];

    cin >> t;
    while(t--)
    {
        cin >> n >> c >> f;
        for(int i=0;i<n;i++)
            for(int j=0;j<c;j++)
            {
                cin >> s[i][j];
            }

        my_graph g(n);
        for(int i=0;i<n;i++)
            for(int j=i+1;j<n;j++)
            {
                ans = 0;
                for(int k=0;k<c;k++)
                    for(int l=0;l<c;l++)
                    {
                        if(s[i][k]==s[j][l])
                        {
                            ans++;
                            break;
                        }
                    }
                if(ans>f)
                {
                    add_edge(j,i,g);
                    add_edge(i,j,g);
                }
            }

        std::vector<graph_traits<my_graph>::vertex_descriptor> mate(n);

        bool success = checked_edmonds_maximum_cardinality_matching(g, &mate[0]);
        assert(success);

        ans = matching_size(g, &mate[0]);

        if(ans * 2 ==n) puts("not optimal"); else puts("optimal");

        /*
        std::cout << "The matching is:" << std::endl;

        for(boost::tie(vi,vi_end) = vertices(g); vi != vi_end; ++vi)
            if (mate[*vi] != graph_traits<my_graph>::null_vertex() && *vi < mate[*vi])
                std::cout << "{" << *vi << ", " << mate[*vi] << "}" << std::endl;
        */
    }
    return 0;
}


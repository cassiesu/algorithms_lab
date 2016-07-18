#include <iostream>
#include <cstdio>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/boyer_myrvold_planar_test.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/ref.hpp>
#include <vector>


int main()
{

    int t,n,m,a,b;

  using namespace boost;
  using namespace std;

  typedef adjacency_list<vecS,
                         vecS,
                         undirectedS,
                         property<vertex_index_t, int>,
                         property<edge_index_t, int>
                         > graph;

    ios_base::sync_with_stdio(false); 
  scanf("%d",&t);
  while(t--)
  {
      scanf("%d %d",&n,&m);
      n++;
      graph K(n);
      for(int i=1;i<=m;i++)
      {
          scanf("%d %d",&a,&b);
          add_edge(a, b, K);
      }
      for(int i=0;i<n-1;i++)
      {
          add_edge(i,n-1,K);
      }
      property_map<graph, edge_index_t>::type e_index = get(edge_index,K);
    graph_traits<graph>::edges_size_type edge_count = 0;
      graph_traits<graph>::edge_iterator ei, ei_end;
    for(tie(ei, ei_end) = edges(K); ei != ei_end; ++ei)
                    put(e_index, *ei, edge_count++);
      if (boyer_myrvold_planarity_test(K))
            puts("yes");
      else
            puts("no");
  }
  return 0;
}


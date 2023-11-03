/*Introduction:
This is my implementation of Dijkstra algorithm. 
I have not used anz outside material except forr the text of the assignment. 
I have learnt using Classes and functions in c++. I have used recursive algorithm to find 
the shortest path. I have used class Graph to declare connections between nodes.
I used funcion Shortestpath to find the shortest path from 0 to every other node.
Function Path returns Path from 0 to x, where x is the finish. It is written 0-node1-node2...-x.
The output of the function is sum of distances from node 0, count of nodes connected to node 0 and
the average shortest path. Ussually, both graph for density of 20 percent and graph of denstity 
of 40 percent were completely connected. There were a few rare case where the graph with a density 
of 20 percent was not connected(mostly only 1 node was disconnected). 
I have declared functions for Graph Vertices and Vertex. Vertices returns integer value of how many
Vertices the graph has. Vertex lists all the unique vertices in the graph: each line of output 
contains one vertex- node x, node y and the edge that connects the nodes. I have decided not to use
every function I have written to make it simple. I have used Paths20 and Paths40 as 2 2-dimensional 
arrays for vertices between node with densities 20 and 40 percent respectively. NV20 and NV40 are 
2-dimensional arrays showing the shortest pathways from node 0 to node n. You can try use funcion 
Path(n,NV20) and Path(n,NV40) after using functin Shortestpath to show the pathway to node n.
*/
#include <ctime>
#include <iostream>
#include <list>
#include <array>
#include <time.h>
#include <stdlib.h>

using namespace std;

class Graph
{
public:
  double density ;
  int nodes ;
  double V[50][50];
  
  Graph(double d,int n, double vert[50][50])
  {
    
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (i < j)
        {
          int Ran = rand() %100;
          if (Ran < d*100)
          {
            vert[i][j] = (rand() / (double)RAND_MAX) * (10.0 - 1.0) + 1.0;
            vert[j][i] = vert[i][j];
          }
        }
      }
    }
  }

  int Vertices()
  {
    int s = 0;
    for (int i = 0; i < nodes; i++)
    {
      for (int j = 0; j < i; j++)
      {if (V[i][j]>0.1){
          s++;
          }
        }
        }
    return s;
  }
  void Vertex()
  {
    int s = 0;
    for (int i = 0; i < nodes; i++)
    {
      for (int j = 0; j < i; j++)
      {
        if (V[i][j] > 0.1)
        {
          cout << i << ' ' << j << ' '<< V[i][j] << endl;
        }
      }
    }
  }

    bool adj(int x,int y){if (V[x][y]>0.1){
        return true;
      }else{
        return false;
      };
    }
    double get_edge_value(int x, int y) { return V[x][y]; }
    void set_edge_value(double V[50][50], int x, int y, double v) { V[x][y] = v;
      V[y][x] = v;
    }
};

void ShortestPath(double f, int m,int i, double P[50][50],int NV[50][50])
    {
      int t;

      for (int l = 1; l < 50; l++)
      { 
        if (P[m][l] < 0.1)
        {
          continue;
        }
        else
        {
          if (m==0)
          { i++;
            ShortestPath(P[m][l], l,i, P, NV);
            continue;
          };
        }
        if (P[0][l] < 0.1)
        { NV[i][l] = m;
          i++;
          P[0][l] = f + P[m][l];
          ShortestPath(P[0][l], l,i, P,NV);
          
          continue;
        }
        if (P[0][l] > f + P[m][l])
        {
          
          for (t = 1; t < 50; t++)
          {
            NV[t][l] = NV[t][m];
            
          }
          for (t = 1; t < 50; t++)
          {
            if (NV[t][m] == 0)
            {
              break;
            }
            }
            NV[t][l] = m;
            i = t;
            i++;
            P[0][l] = f + P[m][l];
            ShortestPath(P[0][l], l, i, P, NV);

            continue;
          }
      }

    }
    void Path(int i, int F[50][50]){
      cout << '0' << '-';
      int w;
      for (int w = 1; w < 50; w++)
      {
        if (F[w][i] == 0)
        {
          break;
        }
        cout << F[w][i] << '-';
      }
      cout << i<<endl;
    }

    int main()
    {
      int N = 50;
      srand(time(NULL));
      double Paths20[50][50];
      double Paths40[50][50];
      int NV20[50][50];
      int NV40[50][50];
      Graph G20(0.2,N,Paths20);
      Graph G40(0.4, N, Paths40);   

      ShortestPath(0, 0, 0, Paths20, NV20);
      ShortestPath(0, 0,0, Paths40,NV40);
      double sum = 0;
      int c = 0; 

      for (int i = 1; i < N; i++)
      {
        if (Paths20[0][i] > 0.1)
        {
          c++;
          sum += Paths20[0][i];
        }
        else
        {
          cout << endl<< i;
        }
      }
      cout << endl << sum << ' ' << c << ' ' << sum / c<< endl;
      sum=0 ;
      c = 0;
        for (int i = 1; i < N; i++)
        {
          if (Paths40[0][i] > 0.1)
          {
            c++;
            sum += Paths40[0][i];
          }
          else
          {
            cout << endl << i;
          }
        }

      cout << endl<< sum << ' ' << c << ' ' << sum / c;
      /* for (n=1;n<50;n++){
        Path(n,NV20);
      } */
      /* for (n=1;n<50;n++){
        Path(n,NV40);
      } */
      return 0;
}
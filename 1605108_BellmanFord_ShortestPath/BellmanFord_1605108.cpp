#include<stdio.h>
#include<stdlib.h>
#include<iostream>

#define NULL_VALUE -999999
#define INFINITY 999999

using namespace std;

//----------------------------------------------------------------------------------edge
struct edge
{
    int u,v,w;
    edge()
    {
        u = -1;
        v = -1;
        w = NULL_VALUE;
    }
    edge(int from,int to,int weight)
    {
        u=from;
        v=to;
        w=weight;
    }
};
//----------------------------------------------------------------------------------edge


//----------------------------------------------------------------------------------Dynamic ArrayList
class ArrayList
{
    edge *list;
    int length ;
    int listMaxSize,listInitSize ;
public:
    ArrayList()
    {
        listInitSize = 2 ;
        listMaxSize = listInitSize ;
        list = new edge[listMaxSize] ;
        length = 0 ;
    }

    void insertItem(edge newitem)
    {
        edge *tempList ;
        if (length == listMaxSize)
        {
            listMaxSize = 2 * listMaxSize ;
            tempList = new edge[listMaxSize] ;
            for(int i = 0; i < length ; i++ )
            {
                tempList[i] = list[i] ;
            }

            delete[] list ;
            list = tempList ;
        }
        list[length] = newitem ;
        length++ ;
    }


    int getLength()
    {
        return length ;
    }

    edge getItem(int position)
    {
        if(position < 0 || position >= length)
            return edge(-1,-1,-1);
        return list[position] ;
    }

    ~ArrayList()
    {
        if(list)
            delete [] list;
        list = 0 ;
    }
};
//----------------------------------------------------------------------------------Graph class starts here
class Graph
{
    bool sol,dir;
    int nVertices, nEdges ;
    int *parent,*dist;
    ArrayList  adjList ;
public:
    Graph(bool f)
    {
        nVertices = 0 ;
        nEdges = 0 ;
        parent=0;
        dist=0;
        dir=f;
    }
    void setnVertices(int n)
    {
        //node number will start from 1
        nVertices=n+1;
        //deleting previous statistics
        if(parent!=0)
            delete[] parent;

        if(dist!=0)
            delete[] dist;

        dist=new int[nVertices];
        parent=new int[nVertices];

        nVertices--;
    }

    void addEdge(int u, int v,int w)
    {
        //vertex out of range
        if(u<=0 || v<=0 || u>nVertices || v>nVertices)
        {
            printf("vertex out of range\n");
            return;
        }

        this->nEdges++ ;

        adjList.insertItem(edge(u,v,w));

        if(!dir)
            adjList.insertItem(edge(v,u,w));
    }
    //--------------------------------------------------Add Edge
    //--------------------------------------------------Bellman-Ford
    void BellmanFord(int s)
    {
        int i,j,k;
        int u,v,w;

        for(i=1; i<=nVertices; i++)
        {
            dist[i]=INFINITY;
            parent[i]=-1;
        }

        dist[s]=0;

        for(i=1; i<nVertices; i++)
        {
            for(j=0; j<adjList.getLength(); j++)
            {
                u=adjList.getItem(j).u;
                v=adjList.getItem(j).v;
                w=adjList.getItem(j).w;
                if(dist[u]!=INFINITY && dist[v]>dist[u]+w)
                {
                    dist[v]=dist[u]+w;
                    parent[v]=u;
                }
            }
        }

        //negative edge cycle
        for(i=0; i<adjList.getLength(); i++)
        {
            u=adjList.getItem(i).u;
            v=adjList.getItem(i).v;
            w=adjList.getItem(i).w;
            if(dist[v]>dist[u]+w)
            {
                sol=0;
                return;
            }
        }
    }
    //--------------------------------------------------Bellman-Ford


    //--------------------------------------------------print
    void print()
    {
        if(sol)
        {
            cout << "No negative edge cycle\n"<<endl;
            for(int i=1; i<=nVertices; i++)
                cout << "vertex : " << i << " , distance : " << dist[i] << " , previous : " << parent[i] << endl;
        }
        else
            cout << "Negative edge cycle found\n"<<endl;
    }
    //--------------------------------------------------print


    //--------------------------------------------------Destruction
    ~Graph()
    {
        if(parent)
        {
            delete[] parent;
            parent=0;
        }
        if(dist)
        {
            delete[] dist;
            dist=0;
        }
    }
};
//--------------------------------------------------Destruction
//----------------------------------------------------------------------------------Graph class ends here


int main()
{

    freopen("DohaInput.txt","r",stdin);
    freopen("DohaOutput.txt","w",stdout);

    int i,j,k;
    int n,m;
    int u,v,w;
    Graph g(true);
    cin>>n>>m;
    g.setnVertices(n);
    for(i=0; i<m; i++)
    {
        cin>>u>>v>>w;
        g.addEdge(u,v,w);
    }
    int source;
    cin>>source;
    g.BellmanFord(source);
    g.print();
    return 0;
}

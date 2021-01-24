#include<cstdio>
#include<iostream>

#define NULL_VALUE -999999
#define INFINITY 999999


using namespace std;

struct edge
{
    int v,w;
    edge()
    {
        v=-1;
        w=NULL_VALUE;
    }
    edge(int end,int weight)
    {
        v=end;
        w=weight;
    }
};

//******************ArrayList class starts here*************************

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
            return {};
        return list[position] ;
    }


    ~ArrayList()
    {
        if(list)
            delete [] list;
        list = 0 ;
    }
};

//******************Heap class starts here*************************
class Heap
{
public:
    int n;
    int *heap;
    int *pos;

    int getParent(int i)
    {
        return (i-1)/2;
    }
    int getLeftChild(int i)
    {
        return 2*i+1;
    }
    int getRightChild(int i)
    {
        return 2*i+2;
    }

    Heap(int n, int *arr);
    int extractMin();
    void minHeapify(int x);
    void decreaseKey(int key, int newVal);
    void printPos() {}
};

Heap::Heap(int n, int *arr)
{
    this->n = n;
    heap = new int[n];
    for (int i=0; i<n; i++)
        heap[i] = arr[i];
    pos = new int[n];

    for (int i=0; i<n; i++)
        pos[i] = i;

    for (int i=(n/2)+1; i>=0; i--)
    {
        minHeapify(i);
    }
}

int Heap::extractMin()
{
    int min = pos[0];

    heap[0] = heap[n-1];

    swap(pos[0], pos[n-1]);

    n = n-1;

    minHeapify(0);
    printPos();
    return min;
}

void Heap::minHeapify(int x)
{
    int leftChild = getLeftChild(x);
    int rightChild = getRightChild(x);
    int smallest = x;

    if( leftChild<n && heap[leftChild] < heap[x] )
        smallest = leftChild;
    if( rightChild<n && heap[rightChild] < heap[x] )
        smallest = rightChild;

    if(smallest != x)
    {

        int temp = heap[x];
        heap[x] = heap[smallest];
        heap[smallest] = temp;

        swap(pos[x],pos[smallest]);

        minHeapify(smallest);
    }
}

void Heap::decreaseKey(int key, int newVal)
{
    int position=0;
    for (int i = 0; i < n; ++i)
    {
        if(pos[i] == key)
        {
            position = i;
            break;
        }
    }
    heap[position] = newVal;
    while (position > 0 && heap[getParent(position)] > heap[position])
    {

        int temp = heap[position];
        heap[position] = heap[getParent(position)];
        heap[getParent(position)] = temp;

        swap(pos[position], pos[getParent(position)]);

        position = getParent(position);
    }
    printPos();
}

//******************Graph class starts here**************************
class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    ArrayList  * adjList ;
    int *parent, *dist;

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v, int w);
    int getDegree(int u);
    void dijkstra(int source);
    void print();
    void showDist()
    {
        cout << "Graph dist : ";
        for (int i=0; i<nVertices; i++)
            cout << dist[i] << "  ";
        cout << endl;
    }
    void showParent()
    {
        cout << "Graph prev : ";
        for (int i=0; i<nVertices; i++)
            cout << parent[i] << "  ";
        cout << endl;
    }
};
Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    adjList = 0 ;
    directed = dir ;

    parent=0;
    dist=0;
}
void Graph::setnVertices(int n)
{
    this->nVertices = n ;

    if(adjList != NULL)
    {
        delete[] adjList ;   //delete previous list
    }
    if(parent != NULL)
    {
        delete[] parent;
    }
    if(dist != NULL)
    {
        delete[] dist;
    }

    dist=new int[nVertices];
    parent=new int[nVertices];
    adjList = new ArrayList[nVertices] ;
}
void Graph::addEdge(int u, int v, int w)
{
    if(u >= nVertices|| v >= nVertices)
    {
        printf("Vertex is out of Range!!!\n");
    }
    if(u < 0 || v < 0)
    {
        printf("Invalid Input!!!!\n");
    }
    //vertex out of range
    this->nEdges++ ;
    adjList[u].insertItem(edge(v,w)) ;
    if(!directed)
        adjList[v].insertItem(edge(u,w)) ;
}

int Graph::getDegree(int u)
{
    //returns the degree of vertex u
    if(u<0 || u >= nVertices)
    {
        printf("Invalid Input!!!\n");
        return 0;
    }
    else
        return adjList[u].getLength();
}
Graph::~Graph()
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
    if(adjList)
    {
        delete[] adjList;
        adjList=0;
    }
}

void Graph::dijkstra(int source)
{
    int i,j,k;
    int u,v,w;

    for(i=0; i<nVertices; i++)
    {
        dist[i]=INFINITY;
        parent[i]=-1;
    }

    dist[source]=0;


    Heap heap(nVertices, dist);


    while (heap.n > 0)
    {
        u = heap.extractMin();
        for (int i = 0; i < getDegree(u); ++i)
        {
            v = adjList[u].getItem(i).v;
            w = adjList[u].getItem(i).w;

            if(dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                parent[v] = u;
                heap.decreaseKey(v,dist[v]);
            }
        }


    }
}

void Graph::print()
{

    for(int i=0; i<nVertices; i++)
        cout << "vertex : " << i << " , distance : " << dist[i] << " , previous : " << parent[i] << endl;
}

//**********************Graph class ends here******************************

int main()
{

    freopen("DohaInput.txt","r",stdin);
    freopen("DohaOutput.txt","w",stdout);

    int i,j,k;
    int n,m;
    int u,v,w;

    Graph g(true);

    //printf("Number of vertices and edges: ");
    cin >> n >> m;
    g.setnVertices(n);

    for(i=0; i<m; i++)
    {
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    int source;
    cin >> source;

    g.dijkstra(source);
    g.print();

    return 0;
}

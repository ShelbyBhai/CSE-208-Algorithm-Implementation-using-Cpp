#include<cstdio>
#include<iostream>

#define NULL_VALUE -999999
#define INF 999999

using namespace std;

struct edge
{
    int u,v,w;
    edge(){}
    edge(int x) { w = x;  u = -1; v = -1; }
    edge(int start,int end,int weight)
    {
        u=start;
        v=end;
        w=weight;
    }

    /*bool operator < (edge &second)
    {
        return (this->w < second.w);
    } */
};

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

    int searchItem(edge item)
    {
        for (int i = 0; i < length; i++)
        {
            if(list[i].u==item.u && list[i].v == item.v && list[i].w==item.w )
                return i;
        }

        return NULL_VALUE;
    }

    void removeItemAt(int position)
    {
        if ( position < 0 || position >= length ) return;
        list[position] = list[length-1] ;
        length-- ;
    }

    void removeItem(edge item)
    {
        int position;
        position = searchItem(item) ;
        if ( position == NULL_VALUE ) return ;
        removeItemAt(position) ;
    }

    int getLength()
    {
        return length ;
    }

    edge getItem(int position)
    {
        if(position < 0 || position >= length) return edge(-1,-1,-1);
        return list[position] ;
    }

    void printList()
    {
        for(int i=0; i<length; i++)
            printf("%d , %d , %d\n",list[i].u,list[i].v,list[i].w);

    }

    ~ArrayList()
    {
        if(list) delete [] list;
        list = 0 ;
    }
};

//******************ArrayList class ends here*************************

class Heap
{
public:
    int n;
    edge *heap;

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

    Heap(int n, ArrayList arr);
    edge extractMin();
    void minHeapify(int x);
};

Heap::Heap(int n, ArrayList arr) {
    this->n = n;
    heap = new edge[n];
    for (int i = 0; i < n; ++i) {
        heap[i] = arr.getItem(i);
    }

    int j;
    for ( j = (n/2); j >= 0 ; --j) {
        minHeapify(j);
    }
}


void Heap::minHeapify(int x) {
    int l = getLeftChild(x);
    int r = getRightChild(x);
    int smallest = x;

    if(l < n && heap[l].w < heap[smallest].w) smallest = l;
    if(r < n && heap[r].w < heap[smallest].w) smallest = r;

    if(smallest != x) {
        swap(heap[x], heap[smallest]);
        minHeapify(smallest);
    }
}

edge Heap::extractMin() {
    edge temp = heap[0];
    swap(heap[0], heap[n-1]);
    n--;
    minHeapify(0);
    return temp;
}


//******************Graph class starts here**************************
class Graph {
    bool dir;
    int nVertices, nEdges;
    ArrayList *adjList;
    ArrayList edgeList;
    edge *KruskalMST;
public:
    edge *getKruskalMST() const;

public:

    Graph(bool f) {
        nVertices = 0;
        nEdges = 0;
        dir = f;
    }

    void setNVertices(int n) {
        nVertices = n;
        adjList = new ArrayList[nVertices];
        KruskalMST = new edge[nVertices];
    }

    void addEdge(int u, int v, int w) {
        if (u < 0 || v < 0 || u > nVertices || v > nVertices) {
            cout << "vertex out of range\n";
            return;
        }

        this->nEdges++;

        adjList[u].insertItem(edge(u, v, w));
        edgeList.insertItem(edge(u, v, w));

        if (!dir) {
            adjList[v].insertItem(edge(v, u, w));
            //edgeList.insertItem(edge(v, u, w));
        }
    }

    void Kruskal();

};

void Graph::Kruskal() {

    ArrayList cluster[nVertices];
    int clusterIdx[nVertices];
    for (int i = 0; i < nVertices; ++i) {
        cluster[i].insertItem(edge(i));
        clusterIdx[i] = i;
    }

    Heap edgeHeap(nEdges, edgeList);

    int sizeMST = 0;

    while (sizeMST < (nVertices-1)) {
        edge temp = edgeHeap.extractMin();
        int u = temp.u;
        int v = temp.v;

        if(clusterIdx[u] != clusterIdx[v]) {
            KruskalMST[sizeMST] = temp;
            sizeMST++;
            if(cluster[clusterIdx[u]].getLength() < cluster[clusterIdx[v]].getLength()) swap(u,v);
            int minClusterSize = cluster[clusterIdx[v]].getLength();
            for (int i = 0; i < minClusterSize; ++i) {
                cluster[clusterIdx[u]].insertItem(cluster[clusterIdx[v]].getItem(i));
                clusterIdx[cluster[v].getItem(i).w] = clusterIdx[u];
            }
        }
    }
}

edge *Graph::getKruskalMST() const {
    return KruskalMST;
}

//**********************Graph class ends here******************************

int main()
{

    freopen("DohaInput.txt","r",stdin);
    freopen("DohaOutput.txt","w",stdout);

    int n,m;
    int u,v,w;

    Graph g(false);

    cin >> n >> m;
    g.setNVertices(n);

    for(int i=0; i<m; i++)
    {
        cin >> u >> v >> w;
        g.addEdge(u,v,w);
    }


    g.Kruskal();
    edge *MST = g.getKruskalMST();

    int totWgt = 0;
    cout << "Added edges : " << endl;
    cout << "SRC\tDST\tWGT" << endl;
    for (int j = 0; j < (n-1); ++j) {
        totWgt += MST[j].w;
        cout << MST[j].u << "\t" <<  MST[j].v << "\t" <<  MST[j].w << endl;
    }

    cout << "\nMST Weight : " << totWgt << endl;

    return 0;
}

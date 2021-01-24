#include<bits/stdc++.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

using namespace std;

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty();
    int getLength();//return true if Queue is empty
};
Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}
int Queue::getLength()
{
    return length;
}
void Queue::enqueue(int item)
{
    if (length == queueMaxSize)
    {
        int * tempData ;
        //allocate new memory space for tempList
        queueMaxSize = 2 * queueMaxSize ;
        tempData = new int[queueMaxSize] ;
        int i, j;
        j = 0;
        for( i = rear; i < length ; i++ )
        {
            tempData[j++] = data[i] ; //copy items from rear
        }
        for( i = 0; i < rear ; i++ )
        {
            tempData[j++] = data[i] ; //copy items before rear
        }
        rear = 0 ;
        front = length ;
        delete[] data ; //free the memory allocated before
        data = tempData ; //make list to point to new memory
    }
    data[front] = item ; //store new item
    front = (front + 1) % queueMaxSize ;
    length++ ;
}
bool Queue::empty()
{
    if(length == 0)
        return true ;
    else
        return false ;
}
int Queue::dequeue()
{
    if(length == 0)
        return NULL_VALUE ;
    int item = data[rear] ;
    rear = (rear + 1) % queueMaxSize ;
    length-- ;
    return item ;
}
Queue::~Queue()
{
    if(data)
        delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************


//******************Graph class starts here**************************
class Edge
{
public:
    int source;
    int endpoint;
};

class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    int ** matrix ;
    int *color,*parent,*dist;
    int *start,*finish;
    int time;
    Queue q;
    vector<Edge> edgeinfo;
    //adjacency matrix to store the graph
    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation
public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    void printGraph();
    void approxalgo1();
    void printalgo1();
    void approxalgo2();
    void printalgo2();
};
Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    matrix = 0 ;
    color=0;
    parent=0;
    dist=0;
    start=0;
    finish=0;
    time=0;
    directed = dir ; //set direction of the graph
    //define other variables to be initialized
}
void Graph::setnVertices(int n)
{
    this->nVertices = n ;
    //allocate space for the matrix
    matrix = new int*[nVertices];
    for(int i=0; i<nVertices; i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0; j<nVertices; j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }
    if(color != NULL)
    {
        delete[] color;
    }
    if(parent != NULL)
    {
        delete[] parent;
    }
    if(dist != NULL)
    {
        delete[] dist;
    }
    if(start != NULL)
    {
        delete[] start;
    }
    if(finish != NULL)
    {
        delete[] finish;
    }
    color = new int[nVertices];
    dist = new int[nVertices];
    parent = new int[nVertices];
    start = new int[nVertices];
    finish = new int[nVertices];
}
void Graph::addEdge(int u, int v)
{
    //write your code here
    if(u >= nVertices|| v >= nVertices)
    {
        printf("Vertex is out of Range!!!\n");
    }
    if(u < 0 || v < 0)
    {
        printf("Invalid Input!!!!\n");
    }
    matrix[u][v] = 1;
    if(directed == false)
        matrix[v][u] = 1;

    Edge e;
    e.source=u;
    e.endpoint=v;
    edgeinfo.push_back(e);

}
void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u >= nVertices|| v >= nVertices)
    {
        printf("Vertex is out of Range!!!\n");
    }
    if(u < 0 || v < 0)
    {
        printf("Invalid Input!!!!\n");
    }
    matrix[u][v] = 0;
    if(directed == false)
        matrix[v][u] = 0;
}
bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(u >= nVertices|| v >= nVertices)
    {
        printf("Vertex is out of Range!!!\n");
        return false;
    }
    if(u < 0 || v < 0)
    {
        printf("Invalid Input!!!!\n");
        return false;
    }
    if(matrix[u][v] == 1 || matrix[v][u] == 1)
        return true;
    else
        return false;
}
int Graph::getDegree(int u)
{
    //returns the degree of vertex u
    if(u<0 || u >= nVertices)
    {
        //printf("Invalid Input!!!\n");
        return 0;
    }
    int count=0;
    for(int i=0; i<nVertices; i++)
    {
        if(matrix[u][i] == 1)
            count++;
    }
    return count;
}
bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    if(u >= nVertices|| v >= nVertices)
    {
        printf("Vertex is out of Range!!!\n");
        return false;
    }
    if(u < 0 || v < 0)
    {
        printf("Invalid Input!!!!\n");
        return false;
    }
    for(int i=0; i<nVertices; i++)
    {
        if(matrix[u][i] == 1 && matrix[v][i] == 1)
            return true;
    }
    return false;
}
void  Graph::approxalgo1()
{
    int edges,check=0;
    while(!edgeinfo.empty())
    {
        int indx=rand()%edgeinfo.size();
        Edge e=edgeinfo[indx];
        int src=e.source;
        int ep=e.endpoint;
        if(isEdge(src,ep))
        {
            for(int i=0; i<nVertices; i++)
            {
                matrix[src][i]=0;
                matrix[i][src]=0;
            }
            for(int i=0; i<nVertices; i++)
            {
                matrix[ep][i]=0;
                matrix[i][ep]=0;
            }
            q.enqueue(src);
            q.enqueue(ep);
        }
        edgeinfo.erase(edgeinfo.begin()+indx);
    }
}
void Graph::printalgo1()
{
    cout<<q.getLength()<<endl;
}
void Graph::approxalgo2()
{
    int maximum=-999,src,endp,check=0,counter=0;
    for(int i=1;i<=nVertices;i++)
    {

        for(int j=0;j<nVertices-1;j++)
        {//cout<<j<<endl;

            for(int k=j+1;k<nVertices;k++)
            {
                if(getDegree(k)+getDegree(j)>maximum && isEdge(j,k))
                {
                    maximum=getDegree(k)+getDegree(j);
                    src=j;
                    endp=k;
                    check=1;




                }
            }
        }

        if(check==1)
        {
            q.enqueue(src);
            q.enqueue(endp);
            for(int j=0;j<nVertices;j++)
            {
                matrix[src][j]=0;
                 matrix[j][src]=0;
            }
            for(int k=0;k<nVertices;k++)
            {
                matrix[endp][k]=0;
                 matrix[k][endp]=0;
            }
        }
        check=0;
        maximum=-999;
    }
}
void Graph::printalgo2()
{
    cout<<q.getLength()<<endl;
}
void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i);
        for(int j=0; j<nVertices; j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
        }
        printf("\n");
    }
}
Graph::~Graph()
{
    //write your destructor here
    if(matrix)
    {
        for(int i=0; i<nVertices; i++)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    if(start)
    {
        delete[] start;
        start=0;
    }
    if(finish)
    {
        delete[] finish;
        finish=0;
    }
    if(color)
    {
        delete[] color;
        color=0;
    }
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

//**********************Graph class ends here******************************

//******main function to test your code*************************
int main(void)
{
    time_t t;
    srand((unsigned)time(&t));
    Graph g(false);
    freopen("worst_case.txt","r",stdin);
    freopen("DohaOutput.txt","w",stdout);
    int e,vrtx;
    cin>>vrtx>>e;
    g.setnVertices(vrtx);
    int u,v;
    for(int i = 0; i<e; i++)
    {
        cin>>u>>v;
        g.addEdge(u-1,v-1);
    }
    g.approxalgo1();
    g.printalgo1();
}

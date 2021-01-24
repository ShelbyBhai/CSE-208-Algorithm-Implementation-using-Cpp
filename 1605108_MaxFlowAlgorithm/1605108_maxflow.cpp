#include<bits/stdc++.h>
#define inf 100000000

using namespace std;

class Queue
{
public:
    int size, capacity;
    int *arr;
    Queue(int n)
    {
        capacity = n;
        size = 0;
        arr = new int[n];
    }

    ~Queue()
    {
        delete[] arr;
        size = 0;
        capacity = 0;
    }

    void push(int x)
    {
        if(size < capacity)
            arr[size++] = x;
        else
            cout << "Queue Overflow!" << endl;
    }

    int pop()
    {
        if(size>0)
            return arr[--size];
        else
            cout << "Queue Underflow!" << endl;
    }

    bool empty()
    {
        return size == 0;
    }

    int front()
    {
        if(size > 0)
            return arr[size-1];
        else
            cout << "Queue is empty!" << endl;
    }

};
class Graph
{
    int n;
    int **res_cap, **capacity, *parent;
    bool *is_vis;
public:
    Graph(int n);
    void addEdge(int u, int v, int w);
    bool bfs(int s, int t);
    int fordFulkerson(int s, int t);
    void flowThroughEdge();
    void dfs(int s);
    void minCut(int s);
};

Graph::Graph(int n)
{
    this->n = n;
    res_cap = new int*[n + 1];
    for (int i = 0; i <= n; i++)
    {
        res_cap[i] = new int[n + 1];
    }
    capacity = new int*[n + 1];
    for (int i = 0; i <= n; i++)
    {
        capacity[i] = new int[n + 1];
    }
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
            capacity[i][j] = 0;
    }
    parent = new int[n + 1];
    is_vis = new bool[n + 1];
}

void Graph :: addEdge(int u, int v, int w)
{
    capacity[u][v] = w;
}

bool Graph :: bfs(int s, int t)
{
    for (int i = 0; i <= n; i++)
    {
        is_vis[i] = 0;
    }

    Queue q(n);

    is_vis[s] = 1;
    q.push(s);
    parent[s] = -1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v = 1; v <= n; v++)
        {
            if (!is_vis[v] && res_cap[u][v] > 0)
            {
                parent[v] = u;
                is_vis[v] = 1;
                q.push(v);
            }
        }
    }
    return is_vis[t];
}

int Graph :: fordFulkerson(int s, int t)
{
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
            res_cap[i][j] = capacity[i][j];
    }

    int flow = 0;
    int minFlow;
    int u, v;

    while (bfs(s, t))
    {
        minFlow = inf;
        v = t;
        while (1)
        {
            u = parent[v];
            minFlow = min(minFlow, res_cap[u][v]);
            v = u;
            if (v == s)
                break;
        }
        v = t;
        while (1)
        {
            u = parent[v];
            res_cap[u][v] =res_cap[u][v] - minFlow;
            res_cap[v][u] =res_cap[v][u] + minFlow;
            v = u;
            if (v == s)
                break;
        }
        flow =flow + minFlow;
    }
    return flow;
}

void Graph :: flowThroughEdge()
{
    cout<<"\nFlow Through All Edges-\n";
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (capacity[i][j] > 0)
            {
                cout<<"Flow Through " << i << " and " << j << " : " << abs(capacity[i][j]-res_cap[i][j])<<endl;
            }
        }
    }
}

void Graph :: dfs(int s)
{
    is_vis[s] = 1;
    for (int i = 1; i <= n; i++)
    {
        if (res_cap[s][i] && !is_vis[i])
            dfs(i);
    }
}

void Graph :: minCut(int s)
{
    for (int i = 0; i <= n; i++)
    {
        is_vis[i] = 0;
    }
    dfs(s);
    cout<<"\nMin Cut Edges -\n";
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (is_vis[i] && !is_vis[j] && capacity[i][j])
                cout<< i << "-" << j<<endl;
        }
    }
}

int main()
{
    freopen("DohaInput.txt", "r", stdin);
    freopen("DohaOutput.txt","w",stdout);
    int i, j, k;
    int n, m;
    int s, t;
    int u, v, w;
    cin>>n>>m;
    Graph g(n);
    for (i = 0; i < m; i++)
    {
        cin>>u>>v>>w;
        g.addEdge(u, v, w);
    }
    cin>>s>>t;
    cout << g.fordFulkerson(s, t) << endl;
    g.flowThroughEdge();
    g.minCut(s);
}

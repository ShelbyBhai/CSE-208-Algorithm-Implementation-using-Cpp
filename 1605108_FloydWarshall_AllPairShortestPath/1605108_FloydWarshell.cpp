#include<iostream>
#include<cstdio>

#define inf 1000000

using namespace std;

int main()
{
    //freopen("DohaInput.txt", "r", stdin);
    //freopen("DohaOutput.txt","w",stdout);
    int i, j, k;
    int n, m;
    int u, v, w;
    bool isNeg = false;

    cin>>n>>m;

/******************initialize****************/

    int **dist = new int*[n + 1];
    for (i = 0; i <= n; i++)
    {
        dist[i] = new int[n + 1];
    }
    int **parent = new int*[n + 1];
    for (i = 0; i <= n; i++)
    {
        parent[i] = new int[n + 1];
    }
    for (i = 0; i <= n; i++)
    {
        for (j = 0; j <= n; j++)
        {
            dist[i][j] = inf;
            parent[i][j] = -1;
        }
    }

/*******trace zero*********/

    for (i = 0; i <= n; i++)
    {
        dist[i][i] = 0;
    }

/*******value assigning***********/

    for (i = 0; i < m; i++)
    {
        cin>>u>>v>>w;
        dist[u][v] = min(w, dist[u][v]);
        parent[u][v] = u;
    }
    cout<<"                "<<"Initial Matrix\n"<<"             "<<endl;
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (dist[i][j] >= inf)
                cout<<" INF ";
            else
                cout<<" "<<dist[i][j]<<" ";
        }
        cout<<"\n"<<endl;
    }

/******Floyd_Warshall**********/

    for (k = 1; k <= n; k++)
    {
        for (i = 1; i <= n; i++)
        {
            for (j = 1; j <= n; j++)
            {
                if (dist[i][j] > dist[i][k] + dist[k][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    parent[i][j] = parent[k][j];
                }
            }
        }
    }

/********distance matrix*********/

    cout<<"             "<<"Distance Matrix\n"<<"            "<<endl;
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (dist[i][j] >= inf)
                cout<<" INF ";
            else
                cout<<" "<<dist[i][j]<<" " ;
        }
        cout<<"\n"<<endl;
    }

/*********parent matrix***********/

    cout<<"                "<<"Parent Matrix\n"<<"             "<<endl;
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (parent[i][j] >= inf)
                cout<<" INF ";
            else
                cout<<" "<<parent[i][j]<<" " ;
        }
        cout<<"\n"<<endl;
    }

/*******Negative edge cycle check********/

    for (i = 0; i <= n; i++)
    {
        if(dist[i][i] == 0)
            continue;
        else
        {
            isNeg == true;
            cout<<"Negative Edge Cycle Found!!";
            break;
        }
    }
    if(isNeg == false)
        cout<<"No Negative Edge Cycle";
    return 0;
}

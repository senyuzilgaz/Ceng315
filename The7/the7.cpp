#include "the7.h"
using namespace std;
vector<int> path1;
vector<int> path2;

struct graph
{
    int n;
    vector<pair<int, int>>* adjlist;
    bool* visited;
    int time = 0;

    graph(int x) :n(x) {
        adjlist = new vector<pair<int, int>>[n];
        visited = new bool[n];

        for (int i = 0; i < n; i++) {
            visited[i] = false;
        }
    }
    void addEdge(int x, int y, int w) {
        adjlist[x].push_back({ y,w });
    }
};


void createPath(int parent[], int j, int flag)
{
    if (parent[j] == -1)
        return;


    createPath(parent, parent[j], flag);
    if (flag == 1)
    {
        path1.push_back(j);

    }
    else if (flag == 2)
    {
        path2.push_back(j);
    }

}

int minDistance(int dist[], bool visited[], int n)
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < n; v++)
    {
        if (visited[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    }
    return min_index;
}


int calcTime(int u, int v, graph& g)
{
    for (unsigned int j = 0; j < g.adjlist[u].size(); ++j)
    {
        //cout<<"ILGAZ:  "<< g.adjlist[u][j].first << endl;
        if (g.adjlist[u][j].first == v)
            return g.adjlist[u][j].second;
    }

    return -10;
}



int dijkstra(graph& g, int src, int n, int d, int flag)
{
    int dist[n];

    bool visited[n];
    int parent[n];

    for (int i = 0; i < n; i++)
        dist[i] = INT_MAX, visited[i] = false, parent[i] = -1;

    dist[src] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = minDistance(dist, visited, n);

        visited[u] = true;

        for (int v = 0; v < n; v++)
        {
            int time = calcTime(u, v, g);

            if ((!visited[v]) && (time != -10) && (dist[u] != INT_MAX) && (dist[u] + time < dist[v]))
            {
                dist[v] = dist[u] + time;
                parent[v] = u;
            }

        }
    }
    createPath(parent, d, flag);
    return dist[d];

}



void FindRoute(int n, std::vector<Road> roads, int s, int d, int x, int y) {
    std::vector<int> path;
    int cost = INT_MAX, option1, option2;


    graph g(n);
    for (unsigned int i = 0; i < roads.size(); i++) {
        g.addEdge(roads[i].endpoints.first, roads[i].endpoints.second, roads[i].time);
        g.addEdge(roads[i].endpoints.second, roads[i].endpoints.first, roads[i].time);
    }

    path1.push_back(s);
    path2 = path1;

    option1 = (dijkstra(g, s, n, x, 1) + dijkstra(g, x, n, y, 1) + dijkstra(g, y, n, d, 1));
    option2 = (dijkstra(g, s, n, y, 2) + dijkstra(g, y, n, x, 2) + dijkstra(g, x, n, d, 2));

    if (option1 < option2)
    {
        path = path1;
        cost = option1;
    }
    else
    {
        path = path2;
        cost = option2;
    }

    std::cout << cost << " ";
    PrintRange(path.begin(), path.end());
    std::cout << std::endl;
}
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

typedef vector<vector<pair<int, int>>> Graph;
#define NODE    first
#define WEIGHT  second
#define MAKE_NODE(node, weight) make_pair(node, weight)

#define LENGTH  second

enum Color
{
    WHITE = 0,
    GRAY,
    BLACK
};

vector<vector<int>> routes;

void addRoute(const vector<pair<int, int>> & route, int v, int cost, int limit)
{
    vector<int> path;
    path.push_back(v);
    int len = cost;
    int i;
    for (i = route.size() - 1; i >= 0 && route[i].NODE != v; --i)
    {
        path.push_back(route[i].NODE);
    }
    len = len - route[i].LENGTH;
    if (len == limit)
        routes.push_back(path);
}

void dfs(const Graph &graph, int v, vector<Color> & color, vector<pair<int, int>> & route, int limit, int cost = 0)
{
    route.push_back(make_pair(v, cost));
    color[v] = GRAY;

    for (const auto &nxt : graph[v])
        if (WHITE == color[nxt.NODE] && cost + nxt.WEIGHT <= limit)
            dfs(graph, nxt.NODE, color, route, limit, cost + nxt.WEIGHT);
        else if (GRAY == color[nxt.NODE])
            addRoute(route, nxt.NODE, cost + nxt.WEIGHT, limit);

    color[v] = BLACK;
    route.pop_back();
}
/*
 * 5 6
1 2 1
2 3 2
3 4 3
4 2 4
4 5 5
5 1 6
9

 * */

int main()
{
    int n, m;           // Nodes, edges
    cin >> n >> m;

    Graph g(n);

    for (int i = 0; i < m; ++i)
    {
        int a, b, w;
        cin >> a >> b >> w;
        --a, --b;
        g[a].push_back(MAKE_NODE(b, w));
    }

    int limit;
    cin >> limit;

    vector<Color> colors(n);
    vector<pair<int, int>> route;

    for (int i = 0; i < n; ++i)
        if (WHITE == colors[i])
            dfs(g, i, colors, route, limit);

    for (const auto &rt : routes)
    {
        cout << "ROUTE: ";
        for (int i = rt.size() - 1; i >= 0; --i)
            cout << rt[i] + 1;
        cout << endl;
    }

    return 0;
}
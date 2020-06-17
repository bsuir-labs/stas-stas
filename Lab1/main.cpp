#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

typedef vector<vector<pair<int, int>>> Graph;
#define NODE    first
#define WEIGHT  second
#define MAKE_NODE(node, weight) make_pair(node, weight)

#define LENGTH  second

vector<vector<int>> routes;

void addRoute(const vector<pair<int, int>> & route)
{
    vector<int> path;
    for (const auto &node : route)
        path.push_back(node.NODE);
    routes.push_back(path);
}

void dfs(const Graph &graph, int v, vector<bool> & used, vector<pair<int, int>> & route, int limit, int cost = 0, int start = 0)
{
    route.push_back(make_pair(v, cost));
    used[v] = true;

    for (const auto &nxt : graph[v])
        if (!used[nxt.NODE] && cost + nxt.WEIGHT <= limit)
            dfs(graph, nxt.NODE, used, route, limit, cost + nxt.WEIGHT, start);
        else if (nxt.NODE == start && cost + nxt.WEIGHT == limit)
        {
            route.push_back(make_pair(nxt.NODE, cost + nxt.WEIGHT));
            addRoute(route);
            route.pop_back();
        }

    route.pop_back();
}

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

    vector<pair<int, int>> route;

    for (int i = 0; i < n; ++i)
    {
        vector<bool> used(n);
        dfs(g, i, used, route, limit, 0, i);
    }

    sort(routes.begin(), routes.end());

    for (const auto &rt : routes)
    {
        cout << "ROUTE: ";
        for (unsigned i = 0; i < rt.size(); ++i)
            cout << rt[i] + 1 << (i != rt.size() -1 ? " -> " : "\n");
    }


    return 0;
}

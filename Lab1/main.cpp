#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

typedef vector<vector<pair<int, int>>> Graph;
#define NODE    first
#define WEIGHT  second
#define MAKE_NODE(node, weight) make_pair(node, weight)
#define LENGTH  second

Graph readGraphFromFile(ifstream &fin);
vector<vector<int>> findRoutes(const Graph &graph, int length);

void dfs(const Graph &graph,
         int v,
         vector<bool> &used,
         vector<pair<int, int>> &route,
         int limit,
         vector<vector<int>> &output,
         int cost = 0,
         int start = 0);

void addRoute(const vector<pair<int, int>> &route,
              vector<vector<int>> &output);

int main()
{
    const unsigned kTestCasesNumber = 6;

    for (unsigned test = 1; test <= kTestCasesNumber; ++test)
    {

        string inputFileName = "input-" + to_string(test) + ".txt";
        string outputFileName = "output-" + to_string(test) + ".txt";

        ifstream fin;
        ofstream fout;

        fin.open(inputFileName);
        fout.open(outputFileName);

        if (!fin.is_open() || !fout.is_open())
        {
            cout << "Can't open files for test #" << test << endl;
            cout << "Skipping test." << endl;
            continue;
        }

        int cycleLength;
        fin >> cycleLength;
        if (fin.eof())
        {
            cout << "Can't find the length limit for test #" << test << endl;
            cout << "Skipping test." << endl;
            continue;
        }

        Graph graph = readGraphFromFile(fin);

        if (graph.empty())
        {
            cout << "Empty test #" << test << endl;
            cout << "Skipping." << endl;
            continue;
        }

        vector<vector<int>> routes = findRoutes(graph, cycleLength);

        // Print output
        for (const auto &route : routes)
            for (size_t i = 0; i < route.size(); ++i)
            {
                fout << route[i];
                if (i < route.size() - 1)
                    fout << " ";
                else
                    fout << "\n";
            }

    }

    return 0;
}

Graph readGraphFromFile(ifstream &fin)
{
    Graph res;

    unsigned from, to, weight;
    fin >> from >> to >> weight;

    while (!fin.eof())
    {
        if (res.size() < max(from, to))
            res.resize(max(from, to));
        --from, --to;

        res[from].push_back(MAKE_NODE(to, weight));

        fin >> from >> to >> weight;
    }

    return res;
}

vector<vector<int>> findRoutes(const Graph &graph, int length)
{
    unsigned nodes = graph.size();

    vector<vector<int>> routes;
    vector<pair<int, int>> route;

    for (unsigned i = 0; i < nodes; ++i)
    {
        vector<bool> used(nodes);
        dfs(graph, i, used, route, length, routes, 0, i);
    }

    sort(routes.begin(), routes.end());
    return routes;
}

void dfs(const Graph &graph,
         int v,
         vector<bool> &used,
         vector<pair<int, int>> &route,
         int limit,
         vector<vector<int>> &output,
         int cost,
         int start)
{
    route.push_back(make_pair(v, cost));
    used[v] = true;

    for (const auto &nxt : graph[v])
        if (!used[nxt.NODE] && cost + nxt.WEIGHT <= limit)
            dfs(graph, nxt.NODE, used, route, limit, output, cost + nxt.WEIGHT, start);
        else if (nxt.NODE == start && cost + nxt.WEIGHT == limit)
        {
            route.push_back(make_pair(nxt.NODE, cost + nxt.WEIGHT));
            addRoute(route, output);
            route.pop_back();
        }

    used[v] = false;
    route.pop_back();
}

void addRoute(const vector<pair<int, int>> & route, vector<vector<int>> &output)
{
    vector<int> path;
    for (const auto &node : route)
        path.push_back(node.NODE + 1);
    output.push_back(path);
}

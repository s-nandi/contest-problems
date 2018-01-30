//dsu on trees (merging maps)
//http://codeforces.com/contest/600/problem/E

#include <iostream>
#include <vector>
#include <map>

using namespace std;

#define ll long long

struct node
{
    map <int, int> counts;
    int maxCount;
    ll sumColors;

    node(int color = -1)
    {
        counts[color] = 1;
        maxCount = 1;
        sumColors = color;
    }
};

vector <vector<int>> graph;

struct disjointSetUnionTree
{
    int sz;
    vector <node> nodes;
    vector <int> indexes;
    vector <ll> solution;

    disjointSetUnionTree(int s)
    {
        sz = s;
        nodes.resize(sz), indexes.resize(sz), solution.resize(sz);
        for (int i = 0; i < sz; i++)
        {
            indexes[i] = i;
        }
    }

    node& operator [] (int i)
    {
        return nodes[i];
    }

    void solve(vector <vector<int>> &graph)
    {
        dfs(graph, 0, -1);
    }

    void dfs(vector <vector<int>> &graph, int curr, int prev)
    {
        for (int neighbor: graph[curr]) if (neighbor != prev)
        {
            dfs(graph, neighbor, curr);
            unionSet(indexes[curr], indexes[neighbor]);
        }
        solution[curr] = nodes[indexes[curr]].sumColors;
    }

    void unionSet(int &a, int &b)
    {
        if (nodes[a].counts.size() < nodes[b].counts.size()) swap(a, b);

        for (auto &e: nodes[b].counts)
        {
            nodes[a].counts[e.first] += e.second;
            if (nodes[a].counts[e.first] == nodes[a].maxCount)
            {
                nodes[a].sumColors += e.first;
            }
            else if(nodes[a].counts[e.first] > nodes[a].maxCount)
            {
                nodes[a].maxCount = nodes[a].counts[e.first];
                nodes[a].sumColors = e.first;
            }
        }
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;

    graph.resize(n);
    disjointSetUnionTree dsu(n);

    for (int i = 0; i < n; i++)
    {
        int c;
        cin>>c;
        dsu[i] = node(c);
    }

    for (int i = 0; i < n - 1; i++)
    {
        int x, y;
        cin>>x>>y;
        --x; --y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    dsu.dfs(graph, 0, -1);

    for (ll sol: dsu.solution)
    {
        cout<<sol<<" ";
    }
    cout<<'\n';

    return 0;
}

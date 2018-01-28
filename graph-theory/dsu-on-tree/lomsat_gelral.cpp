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
vector <node> nodes;
vector <int> indexes;
vector <ll> solution;

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

void dfs(int curr, int prev)
{
    for (int neighbor: graph[curr]) if (neighbor != prev)
    {
        dfs(neighbor, curr);
        unionSet(indexes[curr], indexes[neighbor]);
    }
    solution[curr] = nodes[indexes[curr]].sumColors;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;

    graph.resize(n);
    nodes.resize(n);
    indexes.resize(n);
    solution.resize(n);

    for (int i = 0; i < n; i++)
    {
        int c;
        cin>>c;;
        nodes[i] = node(c);
        indexes[i] = i;
    }

    for (int i = 0; i < n - 1; i++)
    {
        int x, y;
        cin>>x>>y;
        --x; --y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    dfs(0, -1);

    for (ll sol: solution)
    {
        cout<<sol<<" ";
    }
    cout<<'\n';

    return 0;
}

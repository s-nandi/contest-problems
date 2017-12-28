//traversal
//https://open.kattis.com/problems/rainbowroads (2017 Mid-Atlantic Regional)

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <utility>

using namespace std;

struct edge
{
    int a;
    int b;
    bool operator < (edge o) const
    {
        return a < o.a or (a == o.a and b < o.b);
    }
};

vector <vector<int>> graph;
map <edge, int> colors;
vector <int> conflict;

set <edge> used;
set <int> badNodes;

int n;
int MAXEDGES;

void dfs(int prev, int curr)
{
    if (used.count({prev, curr}) == 1 or used.size() == MAXEDGES or badNodes.size() == n)
    {
        return;
    }

    used.insert({prev, curr});
    badNodes.insert(curr);
    for (int neighbor: graph[curr])
    {
        if (neighbor != prev and used.count({curr, neighbor}) == 0)
            {
                dfs(curr, neighbor);
            }
    }
}

vector <int> solve()
{
    set <edge> badEdge;

    for (int i = 0; i < n; i++)
    {
        set <int> shown;
        set <int> repeated;
        for (int neighbor: graph[i])
        {
            int currColor = colors[{i, neighbor}];
            if (shown.count(currColor) == 1)
            {
                repeated.insert(currColor);
            }
            else
            {
                shown.insert(currColor);
            }
        }
        for (int neighbor: graph[i])
        {
            int currColor = colors[{i, neighbor}];

            if (repeated.count(currColor) == 1)
            {
                badEdge.insert({i, neighbor});
            }
        }
    }

    for (edge be: badEdge)
    {
        if (used.count(be) == 0)
        {
            dfs(be.a, be.b);
        }
        if (used.size() == MAXEDGES or badNodes.size() == n)
        {
            break;
        }
    }

    vector <int> sol;
    for (int i = 0; i < n; i++)
    {
        if (badNodes.count(i) == 0)
        {
            sol.push_back(i + 1);
        }

    }

    return sol;

}

int main()
{
    cin>>n;

    graph.resize(n);
    MAXEDGES = 2 * (n - 1);
    for (int i = 0; i < n - 1; i++)
    {
        int a, b, c;
        cin>>a>>b>>c;
        --a; --b;
        graph[a].push_back(b);
        graph[b].push_back(a);
        colors[{a, b}] = c;
        colors[{b, a}] = c;
    }

    vector <int> solution = solve();

    cout<<solution.size()<<'\n';
    for (int i: solution)
    {
        cout<<i<<'\n';
    }

    return 0;
}

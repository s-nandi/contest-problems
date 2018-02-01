//strongly connected components (kosaraju)
//http://codeforces.com/contest/427/problem/C

#include <iostream>
#include <vector>
#include <deque>

#define ll long long
#define INF 1231231234
#define MOD 1000000007

using namespace std;

typedef vector <vector<int>> graph;

void ordering(graph &g, int curr, vector <int> &visited, deque <int> &ordered)
{
    if (visited[curr]) return;
    visited[curr] = 1;
    for (int neighbor: g[curr]) if (!visited[neighbor])
    {
        ordering(g, neighbor, visited, ordered);
    }
    ordered.push_front(curr);
}

void categorize(graph &t, int curr, vector <int> &visited, vector <vector<int>> &components)
{
    if (visited[curr]) return;
    visited[curr] = 1;
    components.rbegin() -> push_back(curr);
    for (int neighbor: t[curr]) if (!visited[neighbor])
    {
        categorize(t, neighbor, visited, components);
    }
}

vector <vector<int>> kosarajuSCC(graph &g)
{
    int n = g.size();
    graph t(n);
    vector <int> visited(n);
    deque <int> ordered;
    vector <vector<int>> components;

    for (int i = 0; i < n; i++)
    {
        for (int j: g[i])
        {
            t[j].push_back(i);
        }
    }

    for (int i = 0; i < n; i++) if (!visited[i])
    {
        ordering(g, i, visited, ordered);
    }

    fill(visited.begin(), visited.end(), 0);

    for (int i: ordered) if (!visited[i])
    {
          components.push_back({});
          categorize(t, i, visited, components);
    }

    return components;
}

pair <ll, ll> solve(graph &g, vector <int> &costs)
{
    vector <vector<int>> components = kosarajuSCC(g);

    ll cost = 0, ways = 1;
    for (int i = 0; i < components.size(); i++)
    {
        int minCost = INF, choices = 0;
        for (int j: components[i])
        {
            if (costs[j] < minCost)
            {
                minCost = costs[j];
                choices = 1;
            }
            else if(costs[j] == minCost)
            {
                choices++;
            }
        }
        cost += minCost;
        ways = (ways * choices) % MOD;
    }

    return {cost, ways};
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;

    graph g(n);
    vector <int> costs(n);

    for (int i = 0; i < n; i++)
    {
        cin>>costs[i];
    }

    int m;
    cin>>m;

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin>>a>>b;
        --a; --b;
        g[a].push_back(b);
    }

    auto sol = solve(g, costs);
    cout<<sol.first<<" "<<sol.second<<'\n';
}

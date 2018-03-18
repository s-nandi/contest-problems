//strongly connected components (kosaraju, decomposition)
//http://codeforces.com/contest/427/problem/C

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

#define ll long long

const int INF = 1231231234;
const int MOD = 1000000007;

struct edge{int to;};
typedef vector <vector<edge>> graph;

graph getTranspose(graph &g)
{
    graph t(g.size());
    for (int i = 0; i < g.size(); i++) for (edge e: g[i])
    {
        t[e.to].push_back({i});
    }
    return t;
}

struct kosarajuSCC
{
    int n, sz = 0;
    graph g, t;
    vector <bool> visited; deque <int> ordered;
    vector <vector<int>> components;

    kosarajuSCC(graph &gr)
    {
        g = gr, t = getTranspose(gr), n = g.size();
        visited.resize(n), components.resize(n);
        getScc();
    }

    void getScc()
    {
        for (int i = 0; i < n; i++) if (!visited[i])
            ordering(i);
        for (int i: ordered) if (visited[i])
            categorize(i), ++sz;
    }

    void ordering(int curr)
    {
        if (visited[curr]) return;
        visited[curr] = true;
        for (edge e: g[curr]) if (!visited[e.to])
            ordering(e.to);
        ordered.push_front(curr);
    }

    void categorize(int curr)
    {
        if (!visited[curr]) return;
        visited[curr] = false;
        components[sz].push_back(curr);
        for (edge e: t[curr]) if (visited[e.to])
            categorize(e.to);
    }
};

vector <int> costs;

pair <ll, ll> solve(graph &g)
{
    auto scc = kosarajuSCC(g);
    ll cost = 0, ways = 1;
    for (int i = 0; i < scc.sz; i++)
    {
        int minCost = INF, choices = 0;
        for (int j: scc.components[i])
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
    costs.resize(n);

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
        g[--a].push_back({--b});
    }

    auto sol = solve(g);
    cout<<sol.first<<" "<<sol.second<<'\n';
}

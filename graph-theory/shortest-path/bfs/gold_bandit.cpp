// bfs (shortest path), dfs (detect if graph cut)
// https://open.kattis.com/problems/goldbandits
// 2014 NAIPC

#include <iostream>
#include <vector>
#include <queue>
#include <bitset>

using namespace std;

const int MAXN = 40;
const int INF = 1231231234;

struct edge{int to;};
typedef vector<vector<edge>> graph;

bool cutoff(graph &g, int curr, bitset <MAXN> &blocked, vector <int> &visited)
{
    if (curr == 0)
        return false;

    if (visited[curr] or blocked[curr])
        return true;
    visited[curr] = true;

    for (edge e: g[curr])
    {
        if (!cutoff(g, e.to, blocked, visited))
            return false;
    }
    return true;
}

struct state
{
    int i, coin, distance;
    bitset <MAXN> visited;
};

int bfs(graph &g, vector <int> &coins)
{
    vector <int> dist(g.size(), INF);
    vector <int> most(g.size(), 0);

    queue <state> q;
    q.push({0, 0, 0, bitset<MAXN>()});

    while (!q.empty())
    {
        state curr = q.front();
        q.pop();

        for (edge e: g[curr.i])
        {
            if (curr.visited[e.to] or curr.distance + 1 > dist[e.to] )
                continue;

            state nxt;
            nxt.i = e.to;
            nxt.distance = curr.distance + 1;

            bitset <MAXN> take_coin = curr.visited;
            take_coin[e.to] = 1;

            vector <int> visited(g.size());
            if (!cutoff(g, 1, take_coin, visited))
            {
                nxt.coin = curr.coin + coins[e.to];
                nxt.visited = take_coin;
            }
            else
            {
                nxt.coin = curr.coin;
                nxt.visited = curr.visited;
            }
            dist[nxt.i] = min(dist[nxt.i], nxt.distance);
            most[nxt.i] = max(most[nxt.i], nxt.coin);
            q.push(nxt);
        }
    }
    return most[1];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin>>n>>m;

    graph g(n);
    vector <int> coins(n);
    for (int i = 2; i < n; i++)
    {
        cin>>coins[i];
    }
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin>>a>>b;
        --a, --b;
        g[a].push_back({b});
        g[b].push_back({a});
    }
    int sol = bfs(g, coins);
    cout<<sol<<'\n';

    return 0;
}

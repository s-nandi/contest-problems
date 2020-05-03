// bfs, finding minimum cost edge to each node that is part of a shortest path to the node
// https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&category=762&page=show_problem&problem=6000
// 2016 East Central Regional

#include <bits/stdc++.h>

using namespace std;

struct edge{int to, w;};
typedef vector<vector<edge>> graph;

const int INF = 1231231234;

struct state
{
    int node, dist, cost;
};

vector <int> bfs(graph &g, int start)
{
    vector <int> dist(g.size(), INF), cost(g.size(), INF);

    queue <state> q;
    q.push({start, 0, 0});
    while (!q.empty())
    {
        auto curr = q.front();
        q.pop();

        if (curr.dist < dist[curr.node])
        {
            dist[curr.node] = curr.dist;
            cost[curr.node] = curr.cost;
        }
        else if(curr.dist == dist[curr.node])
        {
            cost[curr.node] = min(cost[curr.node], curr.cost);
        }
        for (edge e: g[curr.node])
        {
            state nxt = {e.to, curr.dist + 1, e.w};
            if (nxt.dist <= dist[e.to])
            {
                dist[e.to] = nxt.dist;
                q.push(nxt);
            }
        }
    }
    return cost;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    while (cin >> n >> m)
    {
        map <string, int> names;
        names["English"] = 0;
        for (int i = 0; i < n; i++)
        {
            string s;
            cin>>s;
            names[s] = i + 1;
        }
        graph g(n + 1);
        for (int i = 0; i < m; i++)
        {
            string a, b; int w;
            cin>>a>>b>>w;
            int na = names[a], nb = names[b];
            g[na].push_back({nb, w});
            g[nb].push_back({na, w});
        }
        auto costs = bfs(g, 0);

        int acc = 0;
        bool feasible = true;
        for (int i: costs)
        {
            if (i == INF)
            {
                feasible = false;
                break;
            }
            acc += i;
        }

        if (!feasible)
            cout<<"Impossible"<<'\n';
        else
            cout<<acc<<'\n';
    }

    return 0;
}

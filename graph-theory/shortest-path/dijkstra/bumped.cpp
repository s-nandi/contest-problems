// dijkstra (shortest path using at most one 0-cost edge)
// https://open.kattis.com/problems/bumped
// 2017 North American Qualifier

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 123123123123123;

struct edge{int to, w; bool flight;};
typedef vector <vector<edge>> graph;

struct state
{
    int index; ll distance;
    bool flown;

    bool operator > (const state &o) const
    {
        return make_tuple(distance, index, flown) > make_tuple(o.distance, o.index, o.flown);
    }
};

ll dijkstra(graph &g, int s, int t)
{
    priority_queue <state, vector<state>, greater<state>> pq;
    vector <vector<ll>> distances(g.size(), vector<ll>(2, INF));

    pq.push({s, 0, 0});
    while(!pq.empty())
    {
        state curr = pq.top();
        pq.pop();

        if (curr.distance > distances[curr.index][curr.flown])
            continue;
        distances[curr.index][curr.flown] = curr.distance;

        for (edge e: g[curr.index]) if (!(curr.flown and e.flight))
        {
            bool fly = curr.flown or e.flight;
            if (curr.distance + e.w < distances[e.to][fly])
            {
                distances[e.to][fly] = curr.distance + e.w;
                pq.push({e.to, distances[e.to][fly], fly});
            }
        }
    }
    return min(distances[t][0], distances[t][1]);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m, f, s, t;
    cin >> n >> m >> f >> s >> t;

    graph g(n);

    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({b, c, false});
        g[b].push_back({a, c, false});
    }
    for (int i = 0; i < f; i++)
    {
        int a, b;
        cin >> a >> b;
        g[a].push_back({b, 0, true});
    }
    cout << dijkstra(g, s, t) << '\n';

    return 0;
}

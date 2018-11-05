// dijkstra (expanding node into multiple states)
// https://open.kattis.com/problems/xentopia
// 2018 North Central NA Regional

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct edge{int to, w;};
typedef vector<vector<edge>> graph;

const ll INF = 1e18;
struct node
{
    int index; ll distance;
    bool operator > (const node &o) const
    {
        return make_pair(distance, index) > make_pair(o.distance, o.index);
    }
};

ll dijkstra(graph &g, int s, int t)
{
    priority_queue <node, vector<node>, greater<node>> pq;
    vector <ll> distances(g.size(), INF);
    vector <bool> visited(g.size());

    pq.push({s, 0});
    distances[s] = 0;
    while(!pq.empty())
    {
        node curr = pq.top();
        pq.pop();

        if (visited[curr.index]) continue;
        visited[curr.index] = true;

        for (edge e: g[curr.index]) if (curr.distance + e.w < distances[e.to])
        {
            distances[e.to] = curr.distance + e.w;
            pq.push({e.to, distances[e.to]});
        }
    }
    return distances[t];
}

int k1, k2;
int mapping(int i, int n1, int n2)
{
    return i * (k1 + 1) * (k2 + 1) + n1 * (k2 + 1) + n2;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m >> k1 >> k2;

    graph g(n * (k1 + 1) * (k2 + 1));
    for (int i = 0; i < m; i++)
    {
        int u, v, w, c;
        cin >> u >> v >> w >> c;
        --u, --v;

        int add_red = (c == 1), add_blue = (c == 2);
        for (int num_red = 0; num_red + add_red <= k1; num_red++)
        {
            for (int num_blue = 0; num_blue + add_blue <= k2; num_blue++)
            {
                for (int t = 0; t < 2; t++)
                {
                    int from = mapping(u, num_red, num_blue), to = mapping(v, num_red + add_red, num_blue + add_blue);
                    g[from].push_back({to, w});
                    swap(u, v);
                }
            }
        }
    }

    int s, t;
    cin >> s >> t;
    --s, --t;

    auto res = dijkstra(g, mapping(s, 0, 0), mapping(t, k1, k2));
    if (res >= INF)
        cout << -1 << '\n';
    else
        cout << res << '\n';
}

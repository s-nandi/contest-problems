#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define ll long long
#define INF (ll) 1e18

struct node
{
    int index; ll dist; int color;
    bool operator > (node o) const
    {
        if (dist != o.dist) return dist > o.dist;
        else return make_pair(index, color) < make_pair(o.index, o.color);
    }
};

struct edge
{
    int to, dist, color;
};

typedef vector <vector<edge>> graph;

struct distances
{
    ll d1, d2;
    int c1, c2;

    distances()
    {
        d1 = INF, d2 = INF, c1 = -1, c2 = -1;
    }

    bool update(ll d, int c)
    {
        if (d < d1)
        {
            if (c != c1)
            {
                d2 = d1, c2 = c1;
            }
            d1 = d, c1 = c;
            return true;
        }
        else if(d < d2 and c != c1)
        {
            d2 = d, c2 = c;
            return true;
        }
        return false;
    }
};

vector <distances> dijkstra(graph &g, int s)
{
    priority_queue <node, vector<node>, greater<node>> q;
    vector <distances> d(g.size());

    q.push({s, 0, -1});
    d[s].update(0, -1);

    while(!q.empty())
    {
        node currNode = q.top();
        q.pop();

        int curr = currNode.index;
        int color = currNode.color;
        ll dist = currNode.dist;

        for (edge e: g[curr])
        {
            if (color != e.color and d[e.to].update(dist + e.dist, e.color))
            {
                q.push({e.to, dist + e.dist, e.color});
            }
        }
    }

    return d;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, c;
    cin>>n>>m>>c;

    graph g(n);

    for (int i = 0; i < m; i++)
    {
        int v, u, w, c;
        cin>>v>>u>>w>>c;
        --v; --u;
        g[v].push_back({u, w, c});
    }

    int s, q;
    cin>>s>>q;

    auto sol = dijkstra(g, --s);

    for (int i = 0; i < q; i++)
    {
        int t;
        cin>>t;
        --t;
        ll res = sol[t].d1 != INF ? sol[t].d1 : -1;
        cout<<res<<'\n';
    }

    return 0;
}

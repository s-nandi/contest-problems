//dijkstra (modified ~ second shortest path)
//http://codeforces.com/gym/100570/problem/B

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define ll long long
#define INF (ll) 1e18

struct distancePair
{
    ll d1, d2;
    int c1, c2;

    bool update(ll d, int c)
    {
        bool changed = false;
        if (d < d1)
        {
            if (c != c1)
            {
                d2 = d1;
                c2 = c1;
            }
            d1 = d;
            c1 = c;
            changed = true;
        }
        else if(d < d2 and c != c1)
        {
            d2 = d;
            c2 = c;
            changed = true;
        }
        return changed;
    }
};

struct node
{
    int index;
    ll dist;
    int color;
    bool operator > (node o) const
    {
        return dist > o.dist;
    }
};

vector <vector<node>> graph;
vector <distancePair> d;

void dijkstra(int s)
{
    priority_queue <node, vector<node>, greater<node>> q;

    d[s].update(0, -1);
    q.push({s, 0, -1});

    while(!q.empty())
    {
        node currNode = q.top();
        q.pop();

        int currIndex = currNode.index;
        int currColor = currNode.color;
        ll currDist = currNode.dist;

        for (node neighbor: graph[currIndex])
        {
            int index = neighbor.index;
            ll dist = neighbor.dist;
            int color = neighbor.color;
            if (color != currColor and d[index].update(currNode.dist + dist, color))
            {
                q.push({index, currNode.dist + dist, color});
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, c;
    cin>>n>>m>>c;

    graph.resize(n);
    d.resize(n, {INF, INF, -1, -1});

    for (int i = 0; i < m; i++)
    {
        int v, u, c;
        ll w;
        cin>>v>>u>>w>>c;
        --v; --u;
        graph[v].push_back({u, w, c});
    }

    int s, q;
    cin>>s>>q;
    --s;
    dijkstra(s);

    for (int i = 0; i < q; i++)
    {
        int t;
        cin>>t;
        --t;
        ll res = d[t].d1 != INF ? d[t].d1 : -1;
        cout<<res<<'\n';
    }
}

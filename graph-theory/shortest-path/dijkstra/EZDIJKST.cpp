//dijkstra (single sink)
//http://www.spoj.com/problems/EZDIJKST/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define ll long long

const ll INF = 1e18;

struct edge {int to, w;};
typedef vector <vector<edge>> graph;

struct node
{
    int index; ll distance;

    bool operator < (const node &o) const
    {
        return make_pair(distance, index) < make_pair(o.distance, o.index);
    }

    bool operator > (const node &o) const {return o < *this;}
};

vector <ll> dijkstra(graph &g, int s)
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
    return distances;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin>>T;
    for (int test = 0; test < T; test++)
    {
        int n, k;
        cin>>n>>k;

        graph g(n);
        for (int i = 0; i < k; i++)
        {
            int a, b, c;
            cin>>a>>b>>c;
            g[--a].push_back({--b, c});
        }

        int s, t;
        cin>>s>>t;

        auto sol = dijkstra(g, --s)[--t];
        if (sol == INF) cout<<"NO"<<'\n';
        else cout<<sol<<'\n';
    }

    return 0;
}

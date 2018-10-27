// shortest path faster algorithm (direct application)
// https://www.e-olymp.com/en/problems/1453

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int INF = 30000; // given in problem statement

struct edge{int to, w;};
typedef vector <vector<edge>> graph;

vector <ll> spfa(graph &g, int s)
{
    vector <ll> distances(g.size(), INF);
    vector <int> inq(g.size());
    queue <int> q;

    distances[s] = 0;
    q.push(s);
    inq[s] = true;
    while (!q.empty())
    {
        int curr = q.front();
        q.pop();

        inq[curr] = false;
        for (edge e: g[curr])
        {
            if (distances[curr] + e.w < distances[e.to])
            {
                distances[e.to] = distances[curr] + e.w;
                if (!inq[e.to])
                {
                    q.push(e.to);
                    inq[e.to] = true;
                }
            }
        }
    }
    return distances;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    graph g(n);
    for (int i = 0; i < m; i++)
    {
        int a, b, w;
        cin >> a >> b >> w;
        g[--a].push_back({--b, w});
    }

    auto distances = spfa(g, 0);
    for (int w: distances)
        cout << w << " ";
    cout << '\n';
}

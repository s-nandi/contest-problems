// dijkstra
// http://codeforces.com/gym/101655 (problem E)
// 2013 Pacific NW Regional

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 1e18;
const int MAXW = 1000, MAXH = 1000;

vector <int> dx = {0, -1, 0, 1};
vector <int> dy = {-1, 0, 1, 0};

struct edge {int to, w;};
typedef vector <vector<edge>> graph;

struct node
{
    int index; ll distance;

    bool operator > (const node &o) const
    {
        return make_pair(distance, index) > make_pair(o.distance, o.index);
    }
};

vector <ll> dijkstra(graph &g, int s)
{
    priority_queue <node, vector<node>, greater<node>> pq;
    vector <ll> distances(g.size(), INF);
    vector <bool> visited(g.size());

    pq.push({s, 0});
    distances[s] = 0;

    while (!pq.empty())
    {
        node curr = pq.top();
        pq.pop();

        if (visited[curr.index]) continue;
        visited[curr.index] = true;

        for (edge e : g[curr.index]) if (curr.distance + e.w < distances[e.to])
        {
            distances[e.to] = curr.distance + e.w;
            pq.push({e.to, distances[e.to]});
        }
    }
    return distances;
}

int w, h;
int grid[MAXW + 5][MAXH + 5];

int mapping(int i, int j)
{
    return i * h + j;
}

bool inBounds(int i, int j)
{
    return i >= 0 and j >= 0 and i < w and j < h;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while(T--)
    {
        int k;
        cin >> k >> h >> w;

        int defeat[26];
        memset(defeat, 0, sizeof(defeat));
        for (int i = 0; i < k; i++)
        {
            char c; int def;
            cin >> c >> def;
            defeat[c - 'A'] = def;
        }

        int source;
        graph g(w * h);
        for (int i = 0; i < w; i++)
        {
            for (int j = 0; j < h; j++)
            {
                char c;
                cin >> c;
                grid[i][j] = c - 'A';
            }
        }

        for (int i = 0; i < w; i++)
        {
            for (int j = 0; j < h; j++)
            {
                if (grid[i][j] == 4)
                    source = mapping(i, j);

                int curr = mapping(i, j);
                for (int k = 0; k < dx.size(); k++)
                {
                    int nx = i + dx[k], ny = j + dy[k];
                    if (inBounds(nx, ny))
                    {
                        int neigh = mapping(nx, ny);
                        g[curr].push_back({neigh, defeat[grid[nx][ny]]});
                        g[neigh].push_back({curr, defeat[grid[i][j]]});
                    }
                }
            }
        }

        auto distances = dijkstra(g, source);
        ll best = INF;
        for (int i = 0; i < w; i++)
        {
            for (int j = 0; j < h; j++)
            {
                if (i == 0 or i == w - 1 or j == 0 or j == h - 1)
                {
                    auto possible = distances[mapping(i, j)];
                    best = min(best, possible);
                }
            }
        }
        cout << best << '\n';
    }
}

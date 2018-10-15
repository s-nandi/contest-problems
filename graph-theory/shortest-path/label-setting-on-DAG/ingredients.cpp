// label setting for DAG, knapsack dp
// http://codeforces.com/gym/101635 (problem E)
// 2017 Southwest European Regional

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair <int, int> ii;

struct edge{int to; ll cost, prestige;};
typedef vector <vector<edge>> graph;

const ll INF = 1231231231231231234;

int sz = 0;
map <string, int> mapping;
int mapped(const string &s)
{
    if (mapping.count(s))
        return mapping[s];
    else
        return (mapping[s] = sz++);
}

vector <int> inDegree;
vector <ll> prestiges, costs;
void labelSetting(graph &g)
{
    int n = g.size();
    queue <int> q;

    costs.resize(n, INF), prestiges.resize(n, -INF);
    for (int i = 0; i < n; i++) if (inDegree[i] == 0)
    {
        q.push(i);
        prestiges[i] = costs[i] = 0;
    }

    while (!q.empty())
    {
        int curr = q.front();
        q.pop();

        for (edge e: g[curr])
        {
            if (costs[curr] + e.cost < costs[e.to])
            {
                costs[e.to] = costs[curr] + e.cost;
                prestiges[e.to] = prestiges[curr] + e.prestige;
            }
            else if(costs[curr] + e.cost == costs[e.to])
            {
                prestiges[e.to] = max(prestiges[e.to], prestiges[curr] + e.prestige);
            }

            if (--inDegree[e.to] == 0)
                q.push(e.to);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int b, n;
    cin >> b >> n;

    vector <pair<int, int>> edge_list(n);
    vector <int> p(n), c(n);
    for (int i = 0; i < n; i++)
    {
        string ts, fs, waste;
        int cost, prestige;
        cin >> ts >> fs >> waste >> cost >> prestige;

        int from = mapped(fs), to = mapped(ts);

        edge_list[i] = {from, to};
        p[i] = prestige, c[i] = cost;
    }

    graph g(sz);
    inDegree.resize(sz);
    for (int i = 0; i < n; i++)
    {
        int from = edge_list[i].first, to = edge_list[i].second;
        g[from].push_back({to, c[i], p[i]});
        inDegree[to]++;
    }

    labelSetting(g);
    vector <vector<ll>> dp(sz + 1, vector<ll>(b + 1));
    for (int i = 0; i < sz; i++)
    {
        for (int j = 0; j <= b; j++)
        {
            if (j + costs[i] <= b)
                dp[i + 1][j + costs[i]] = max(dp[i][j] + prestiges[i], dp[i + 1][j + costs[i]]);

            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
        }
    }

    ll sol = dp[sz][b];
    int least = b;
    for (int i = 0; i <= b; i++)
    {
        if (dp[sz][i] == sol)
        {
            least = i;
            break;
        }
    }

    cout << sol << '\n';
    cout << least << '\n';
}

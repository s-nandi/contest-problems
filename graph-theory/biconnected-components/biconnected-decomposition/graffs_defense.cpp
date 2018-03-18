//edge biconnected components (tarjan), combonatorics
//http://www.spoj.com/problems/GRAFFDEF/

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

#define ll long long

struct edge{int to, id;};
typedef vector<vector<edge>> graph;

struct tarjanBCC
{
    int n, m = 0, sz = 0;
    graph g;
    vector <int> depths, lowlinks, bridge;
    vector <bool> br;
    vector <vector<int>> components;

    tarjanBCC(graph &gr)
    {
        g = gr, n = g.size(), getEdge();
        depths.resize(n, -1), lowlinks.resize(n), components.resize(n);
        br.resize(m);
        getBcc();
    }

    void getEdge()
    {
        for (int i = 0; i < n; i++) m += g[i].size();
        m /= 2;
    }

    void getBcc()
    {
        for (int i = 0; i < n; i++) if (depths[i] == -1)
            dfs(i);
        for (int i = 0; i < m; i++) if (br[i])
            bridge.push_back(i);
        for (int i = 0; i < n; i++) if (depths[i] != -1)
            categorize(i), sz++;
    }

    bool dfs(int curr, int prev = -1, int pid = -1)
    {
        if (depths[curr] != -1)
        {
            lowlinks[prev] = min(lowlinks[prev], depths[curr]);
            return false;
        }

        lowlinks[curr] = depths[curr] = prev != -1 ? depths[prev] + 1 : 0;
        for (edge e: g[curr]) if (e.id != pid)
        {
            if (dfs(e.to, curr, e.id))
            {
                lowlinks[curr] = min(lowlinks[curr], lowlinks[e.to]);
                if (lowlinks[e.to] > depths[curr])
                    br[e.id] = true;
            }
        }
        return true;
    }

    void categorize(int curr)
    {
        if (depths[curr] == -1) return;
        depths[curr] = -1;
        components[sz].push_back(curr);
        for (edge e: g[curr]) if (depths[e.to] != -1 and !br[e.id])
            categorize(e.to);
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    setprecision(5);

    int n, m;
    cin>>n>>m;

    graph g(n);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin>>a>>b;
        --a; --b;
        g[a].push_back({b, i});
        g[b].push_back({a, i});
    }

    auto bcc = tarjanBCC(g);

    ll totalChoices = ((ll) n * (n - 1)) / 2;
    ll badChoices = 0;
    for (int i = 0; i < bcc.sz; i++)
    {
        badChoices += (ll) bcc.components[i].size() * (n - bcc.components[i].size());
    }
    badChoices /= 2;

    cout<<fixed<<(double) badChoices / totalChoices<<'\n';

    return 0;
}

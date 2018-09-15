// biconnected components (finding # of nodes reachable without crossing bridge)
// https://open.kattis.com/problems/caveexploration
// 2018 Singapore Preliminary

#include <iostream>
#include <vector>

using namespace std;

struct edge{int to, id;};
typedef vector<vector<edge>> graph;

struct tarjanBCC
{
    int n, m = 0;
    graph g;
    vector <int> depths, lowlinks;
    vector <bool> br;

    tarjanBCC(graph &gr)
    {
        g = gr, n = g.size(), getEdge();
        depths.resize(n, -1), lowlinks.resize(n);
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

    int getSafe(int curr, vector <int> &visited)
    {
        if (visited[curr])
            return 0;
        visited[curr] = true;
        int safe = 1;
        for (edge e: g[curr]) if (!br[e.id])
            safe += getSafe(e.to, visited);
        return safe;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    graph g(n);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin>>a>>b;
        g[a].push_back({b, i});
        g[b].push_back({a, i});
    }

    auto bcc = tarjanBCC(g);
    vector <int> vis(n);
    cout<<bcc.getSafe(0, vis)<<'\n';
}

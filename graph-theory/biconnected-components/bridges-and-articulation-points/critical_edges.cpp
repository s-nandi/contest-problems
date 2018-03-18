//bridge finding
//http://www.spoj.com/problems/EC_P/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct edge{int to, id;};
typedef vector<vector<edge>> graph;
typedef vector<pair<int, int>> edgelist;

struct tarjanBCC
{
    int n, m = 0;
    graph g;
    vector <int> depths, lowlinks, bridge;
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
        for (int i = 0; i < m; i++) if (br[i])
            bridge.push_back(i);
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
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin>>T;

    for (int test = 1; test <= T; test++)
    {
        int n, m;
        cin>>n>>m;

        graph g(n);
        edgelist edges;

        for (int i = 0; i < m; i++)
        {
            int a, b;
            cin>>a>>b;
            --a; --b;
            g[a].push_back({b, i});
            g[b].push_back({a, i});
            edges.push_back({a, b});
        }

        auto bcc = tarjanBCC(g);

        edgelist sol;
        for (int i: bcc.bridge)
        {
            if (edges[i].first > edges[i].second) swap(edges[i].first, edges[i].second);
            sol.push_back({edges[i].first, edges[i].second});
        }
        sort(sol.begin(), sol.end());

        cout<<"Caso #"<<test<<'\n';

        if (sol.size() == 0) cout<<"Sin bloqueos"<<'\n';
        else
        {
            cout<<sol.size()<<'\n';
            for (auto elem: sol)
            {
                cout<<elem.first + 1<<" "<<elem.second + 1<<'\n';
            }
        }
    }

    return 0;
}

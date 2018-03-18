//finding articulation point, string processing
//https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=251

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

struct edge{int to, id;};
typedef vector<vector<edge>> graph;

struct tarjanBCC
{
    int n;
    graph g;
    vector <int> depths, lowlinks;
    vector <bool> cv;
    vector <int> cutVertex;

    tarjanBCC(graph &gr)
    {
        g = gr, n = g.size();
        depths.resize(n, -1), lowlinks.resize(n);
        cv.resize(n);
        getBcc();
    }

    void getBcc()
    {
        for (int i = 0; i < n; i++) if (depths[i] == -1)
            dfs(i);
        for (int i = 0; i < n; i++) if (cv[i])
            cutVertex.push_back(i);
    }

    bool dfs(int curr, int prev = -1, int pid = -1)
    {
        if (depths[curr] != -1)
        {
            lowlinks[prev] = min(lowlinks[prev], depths[curr]);
            return false;
        }

        lowlinks[curr] = depths[curr] = prev != -1 ? depths[prev] + 1 : 0;
        bool out = false;
        for (edge e: g[curr]) if (e.id != pid)
        {
            if (dfs(e.to, curr, e.id))
            {
                lowlinks[curr] = min(lowlinks[curr], lowlinks[e.to]);
                if (prev != -1 ? lowlinks[e.to] >= depths[curr] : out)
                    cv[curr] = true;
                out = true;
            }
        }
        return true;
    }
};

int main()
{
    int n;
    while(cin >> n)
    {
        if (n == 0) break;
        cin.ignore();

        graph g(n);
        int index = 0;
        while (true)
        {
            string s;
            getline(cin, s);
            if (s[0] ==  '0') break;

            istringstream iss(s);
            int a, b;
            iss>>a;
            --a;
            while(iss >> b)
            {
                --b;
                g[a].push_back({b, index});
                g[b].push_back({a, index});
                index++;
            }
        }
        auto bcc = tarjanBCC(g);
        cout<<bcc.cutVertex.size()<<'\n';
    }

    return 0;
}

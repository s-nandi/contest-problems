//detecting directed euler tour, implicit graph
//http://www.spoj.com/problems/WORDS1/

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

struct edge{int to, id;};
typedef vector<vector<edge>> graph;

struct eulerTour
{
    int n, m = 0, root = -1;
    graph g;
    bool isFeasible;
    vector <bool> used;
    deque <int> tour;

    eulerTour(graph &gr)
    {
        g = gr, n = g.size();
        if(isFeasible = feasible())
        {
            getEdge(), used.resize(m);
            dfs(root), isFeasible = tour.size() == m + 1;
        }
    }

    void getEdge()
    {
        for (int i = 0; i < n; i++)
            m += g[i].size();
    }

    bool feasible()
    {
        vector <int> in(n), out(n);
        for (int i = 0; i < n; i++) for (edge e: g[i])
            in[e.to]++, out[i]++;
        int neg = 0, pos = 0;
        for (int i = 0; i < n; i++)
        {
            if (!in[i] and !out[i]) continue;

            int d = in[i] - out[i];
            if (abs(d) > 1) return false;
            if (d < 0)
            {
                if (++neg > 1)
                    return false;
                root = i;
            }
            if (d > 0)
            {
                if (++pos > 1)
                    return false;
            }
            if(root == -1) root = i;
        }
        return neg == pos;
    }

    void dfs(int curr)
    {
        for (edge e: g[curr]) if (!used[e.id])
        {
            used[e.id] = true;
            dfs(e.to);
        }
        tour.push_front(curr);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin>>T;
    while(T--)
    {
        int n;
        cin>>n;

        graph g(26);
        for (int i = 0; i < n; i++)
        {
            string s;
            cin>>s;

            int in = s[0] - 'a', out = s[s.length() - 1] - 'a';
            g[in].push_back({out, i});
        }
        eulerTour eu(g);
        if (eu.isFeasible) cout<<"Ordering is possible."<<'\n';
        else cout<<"The door cannot be opened."<<'\n';
    }

    return 0;
}

//detecting and finding euler tour
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
        if (!feasible()) isFeasible = false;
        else
        {
            getEdge(), used.resize(m);
            dfs(root), isFeasible = tour.size() == m + 1;
        }
    }

    void getEdge()
    {
        for (int i = 0; i < n; i++) m += g[i].size();
    }

    bool feasible()
    {
        vector <int> inDegree(n), outDegree(n);
        for (int i = 0; i < n; i++) for (edge e: g[i])
        {
            inDegree[e.to]++, outDegree[i]++;
        }
        int numLess = 0, numGreater = 0;
        for (int i = 0; i < 26; i++)
        {
            if (!inDegree[i] and !outDegree[i]) continue;

            int diff = inDegree[i] - outDegree[i];
            if (diff > 1 or diff < -1) return false;
            if (diff < 0)
            {
                if (++numLess > 1) return false;
                root = i;
            }
            else if (diff > 0)
            {
                if (++numGreater > 1) return false;
            }
            else if(root == -1) root = i;
        }
        return numLess == numGreater;
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
    ios::sync_with_stdio(0);
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

        auto etour = eulerTour(g);

        if (etour.isFeasible) cout<<"Ordering is possible."<<'\n';
        else cout<<"The door cannot be opened."<<'\n';
    }

    return 0;
}

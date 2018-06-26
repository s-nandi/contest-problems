//geometry (law of cosines proof), dependency graph (reconstructing solution)
//https://codeforces.com/contest/996/problem/E

#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

struct edge{int to; bool neg;};
typedef vector <vector<edge>> graph;

typedef ll ptT;
struct pt
{
    ptT x, y;
    int index;

    pt operator + (const pt &o) const {return {x + o.x, y + o.y};}
    pt operator - (const pt &o) const {return {x - o.x, y - o.y};}
    ptT operator * (const pt &o) const {return x * o.x + y * o.y;}
    ptT norm2() const {return *this * *this;}
};

graph getDependency(vector <pt> &vec, ll r2, ll lim2, int &root)
{
    int numNodes = vec.size();
    graph g(numNodes);
    while (vec.size() > 1)
    {
        pt last3[3];
        for (int i = 0; i < 3; i++)
        {
            if (vec.size() == 0) last3[i] = {0, 0, -1};
            else
            {
                last3[i] = vec.back();
                vec.pop_back();
            }
        }
        bool replaced = false;
        for (int i = 0; i < 3; i++)
        {
            pt a = last3[i], b = last3[(i + 1) % 3], c = last3[(i + 2) % 3];
            ll threshold = c.index != -1 ? r2 : lim2;

            vector <pt> candidates = {a + b, a - b};
            for (int j = 0; j < candidates.size(); j++)
            {
                if (candidates[j].norm2() <= threshold)
                {
                    candidates[j].index = numNodes++;

                    g.push_back(vector <edge>());
                    g[candidates[j].index].push_back({a.index, false});
                    g[candidates[j].index].push_back({b.index, j == 1});

                    vec.push_back(candidates[j]);
                    if (c.index != -1)
                        vec.push_back(c);

                    replaced = true;
                    break;
                }
            }
            if (replaced) break;
        }
    }

    root = vec[0].index;
    return g;
}

void buildSolution(graph &g, int curr, vector <int> &sol, bool neg = false)
{
    if (g[curr].size() == 0)
        sol[curr] = neg ? -1 : 1;

    for (edge e: g[curr])
    {
        buildSolution(g, e.to, sol, e.neg ^ neg);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin>>n;

    vector <pt> vec(n);
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin>>a>>b;
        vec[i] = {a, b, i};
    }

    ll radius = 1000000;
    ll threshold = 1500000;

    int root;
    graph g = getDependency(vec, radius * radius, threshold * threshold, root);

    vector <int> sol(n);
    buildSolution(g, root, sol);

    for (int i = 0; i < sol.size(); i++)
    {
        cout<<sol[i]<<" ";
    }
    cout<<'\n';

    return 0;
}

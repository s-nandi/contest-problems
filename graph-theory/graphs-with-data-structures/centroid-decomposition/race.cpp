//centroid decomposition (sentinel visited array), dynamic programming, finding minimum edges to get path of distance k
//https://contest.yandex.com/ioi/contest/571/problems/B/
//IOI 2011

#include <iostream>
#include <vector>
//#include "grader.h"

using namespace std;

const int INF = 1031231234;
const int MAXL = 1000000;

struct edge
{
    int to, w;
};

typedef vector<vector<edge>> graph;

struct centroidDecomposition
{
    int sz;
    graph g;
    vector <int> sizes, blocked;

    int k, sol, sentinel;
    vector <int> neededEdges, exists;

    centroidDecomposition(graph &gr, int _k)
    {
        g = gr, sz = g.size();
        sizes.resize(sz), blocked.resize(sz);
        k = _k, sol = INF, sentinel = 0, neededEdges.resize(MAXL), exists.resize(MAXL);
        decompose(0);
    }

    int decompose(int curr, int prev = -1)
    {
        curr = findCentroid(calcSize(curr), curr);
        blocked[curr] = true;
        solveNode(curr, -1);
        for (edge e: g[curr]) if (e.to != prev and !blocked[e.to])
        {
            decompose(e.to, curr);
        }
        return curr;
    }

    int calcSize(int curr, int prev = -1)
    {
        sizes[curr] = 1;
        for (edge e: g[curr]) if (e.to != prev and !blocked[e.to])
        {
            sizes[curr] += calcSize(e.to, curr);
        }
        return sizes[curr];
    }

    int findCentroid(int total, int curr, int prev = -1)
    {
        while (prev != curr)
        {
            int temp = curr;
            for (edge e: g[curr]) if (e.to != prev and !blocked[e.to])
            {
                if (sizes[e.to] > total / 2)
                {
                    curr = e.to;
                    break;
                }
            }
            prev = temp;
        }
        return curr;
    }

    void solveNode(int curr, int prev = -1)
    {
        exists[0] = ++sentinel;
        neededEdges[0] = 0;
        for (edge e: g[curr]) if (e.to != prev and !blocked[e.to])
        {
            solveSubtree(e.to, curr, e.w);
            refresh(e.to, curr, e.w);
        }
    }

    template <class Operation>
    void process(int curr, int prev, int dist, int numEdge, Operation op)
    {
        if (dist > k) return;
        op(dist, numEdge);
        for (edge e: g[curr]) if (e.to != prev and !blocked[e.to])
        {
            process(e.to, curr, dist + e.w, numEdge + 1, op);
        }
    }

    void solveSubtree(int curr, int prev, int startDist)
    {
        process(curr, prev, startDist, 1, [this](int dist, int numEdge)
        {
            if (exists[k - dist] == sentinel) sol = min(sol, numEdge + neededEdges[k - dist]);
        });
    }

    void refresh(int curr, int prev, int startDist)
    {
        process(curr, prev, startDist, 1, [this](int dist, int numEdge)
        {
            if (exists[dist] == sentinel) neededEdges[dist] = min(neededEdges[dist], numEdge);
            else neededEdges[dist] = numEdge;
            exists[dist] = sentinel;
        });
    }
};

int best_path(int n, int k, int H[][2], int L[])
{
    graph g(n);
    for (int i = 0; i < n - 1; i++)
    {
        int a = H[i][0], b = H[i][1], w = L[i];
        g[a].push_back({b, w});
        g[b].push_back({a, w});
    }
    centroidDecomposition cd(g, k);

    return cd.sol != INF ? cd.sol : -1;
}

int main()
{
    int n, k;
    cin>>n>>k;

    int H[n][2], L[n];

    for (int i = 0; i < n - 1; i++)
    {
        cin>>H[i][0]>>H[i][1]>>L[i];
    }

    cout<<best_path(n, k, H, L)<<'\n';

    return 0;
}

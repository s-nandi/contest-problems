//centroid decomposition, dynamic programming
//http://codeforces.com/contest/161/problem/D

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

#define ll long long

typedef vector<vector<int>> graph;

const int MAXK = 500;

struct centroidDecomposition
{
    int sz;
    graph g;
    vector <int> sizes, blocked;

    int k; ll sol;
    int reachable[MAXK + 1];

    centroidDecomposition(graph &gr, int _k)
    {
        g = gr;
        sz = g.size(), k = _k, sol = 0;
        sizes.resize(sz), blocked.resize(sz);
        decompose(0);
    }

    int decompose(int curr, int prev = -1)
    {
        curr = findCentroid(calcSize(curr), curr);
        blocked[curr] = true;
        solveNode(curr, -1);
        for (int neighbor: g[curr]) if (neighbor != prev and !blocked[neighbor])
        {
            decompose(neighbor, curr);
        }
        return curr;
    }

    int calcSize(int curr, int prev = -1)
    {
        sizes[curr] = 1;
        for (int neighbor: g[curr]) if (neighbor != prev and !blocked[neighbor])
        {
            sizes[curr] += calcSize(neighbor, curr);
        }
        return sizes[curr];
    }

    int findCentroid(int total, int curr, int prev = -1)
    {
        while (prev != curr)
        {
            int temp = curr;
            for (int neighbor: g[curr]) if (neighbor != prev and !blocked[neighbor])
            {
                if (sizes[neighbor] > total / 2)
                {
                    curr = neighbor;
                    break;
                }
            }
            prev = temp;
        }
        return curr;
    }

    void solveNode(int curr, int prev = -1)
    {
        memset(reachable, 0, sizeof(reachable));
        reachable[0] = 1;
        for (int neighbor: g[curr]) if (neighbor != prev and !blocked[neighbor])
        {
            solveSubtree(neighbor, curr);
            refresh(neighbor, curr);
        }
    }

    template <class Operation>
    void process(int curr, int prev, int dist, Operation op)
    {
        if (dist > k) return;
        op(dist);
        for (int neighbor: g[curr]) if (neighbor != prev and !blocked[neighbor])
        {
            process(neighbor, curr, dist + 1, op);
        }
    }

    void solveSubtree(int curr, int prev)
    {
        process(curr, prev, 1, [this](int dist){ sol += reachable[k - dist]; });
    }

    void refresh(int curr, int prev)
    {
        process(curr, prev, 1, [this](int dist){ reachable[dist]++; });
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin>>n>>k;

    graph g(n);

    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin>>a>>b;
        --a, --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    centroidDecomposition cd(g, k);
    cout<<cd.sol<<'\n';

    return 0;
}

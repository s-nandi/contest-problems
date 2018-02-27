#include <iostream>
#include <vector>
#include <map>
#include <functional>

using namespace std;

#define ll long long

typedef vector<vector<int>> graph;

struct centroidDecomposition
{
    ll sol;
    vector <int> blocked, sizes;
    graph g;

    centroidDecomposition(graph &gr, int k)
    {
        int sz = gr.size();
        g = gr, sol = 0;
        sizes.resize(sz), blocked.resize(sz);
        decompose(0, -1, k);
    }

    int decompose(int curr, int prev, int k)
    {
        function <int (int, int)> calcSize = [&](int curr, int prev)
        {
            sizes[curr] = 1;
            for (int neighbor: g[curr]) if (neighbor != prev and !blocked[neighbor])
            {
                sizes[curr] += calcSize(neighbor, curr);
            }
            return sizes[curr];
        };

        auto findCentroid = [&](int curr, int prev, int n)
        {
            while (true)
            {
                bool moved = false;
                for (int neighbor: g[curr]) if (neighbor != prev and !blocked[neighbor])
                {
                    if (sizes[neighbor] > n / 2)
                    {
                        prev = curr, curr = neighbor, moved = true;
                        break;
                    }
                }
                if (!moved) break;
            }
            blocked[curr] = 1;
            return curr;
        };

        curr = findCentroid(curr, -1, calcSize(curr, -1));
        sol += solveNode(curr, -1, k);
        for (int neighbor: g[curr]) if (!blocked[neighbor])
        {
            decompose(neighbor, curr, k);
        }
        return curr;
    }

    ll solveNode(int curr, int prev, int k)
    {
        map <ll, ll> subtree;
        function <void (int, int, int)> process = [&](int curr, int prev, int dist)
        {
            if (dist > k) return;
            subtree[dist]++;
            for (int neighbor: g[curr]) if (neighbor != prev and !blocked[neighbor])
            {
                process(neighbor, curr, dist + 1);
            }
        };

        vector <ll> reachable(k + 1);
        reachable[0] = 1;
        ll acc = 0;
        for (int neighbor: g[curr]) if (neighbor != prev and !blocked[neighbor])
        {
            subtree.clear();
            process(neighbor, curr, 1);
            for (const auto &elem: subtree)
            {
                acc += elem.second * reachable[k - elem.first];
            }
            for (const auto &elem: subtree)
            {
                reachable[elem.first] += elem.second;
            }
        }
        return acc;
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

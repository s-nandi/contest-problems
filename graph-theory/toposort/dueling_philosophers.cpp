//toposort (bfs)
//https://icpcarchive.ecs.baylor.edu/index.php?option=onlinejudge&page=show_problem&problem=4206
//2012 Mid-Atlantic Regional

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct edge{int to;};
typedef vector <vector<edge>> graph;

int toposort(graph &g)
{
    int n = g.size();
    queue <int> q;
    vector <int> inDegree(n), sorted;

    for (int i = 0; i < n; i++) for (edge e: g[i])
        inDegree[e.to]++;
    for (int i = 0; i < n; i++) if (inDegree[i] == 0)
        q.push(i);

    bool hasBranch = false;
    while (!q.empty())
    {
        if (q.size() > 1) hasBranch = true;

        int curr = q.front();
        q.pop();
        sorted.push_back(curr);

        for (edge e: g[curr]) if (--inDegree[e.to] == 0)
            q.push(e.to);
    }
    if (sorted.size() < n) return 0;
    else return hasBranch ? 2 : 1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    while(true)
    {
        int n, m;
        cin>>n>>m;
        if (n == 0 and m == 0) break;

        graph g(n);

        for (int i = 0; i < m; i++)
        {
            int a, b;
            cin>>a>>b;
            g[--a].push_back({--b});
        }
        cout<<toposort(g)<<'\n';
    }

    return 0;
}

//dfs, detecting directed cycle, implicit bipartite graph
//http://codeforces.com/contest/937/problem/D

#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> graph;

bool hasCycle = false;
vector <vector<int>> visited;
vector <int> onPath;

int dfs(graph &g, int curr, vector <int> &path, int turn)
{
    if (onPath[curr]) hasCycle = true;

    if (visited[curr][turn]) return 0;
    visited[curr][turn] = true;

    path.push_back(curr + 1);
    onPath[curr] = 1;

    if (g[curr].size() == 0 and turn == 1) return 1;

    for (int neighbor: g[curr])
    {
        if (dfs(g, neighbor, path, 1 - turn))
        {
            return 1;
        }
    }

    path.pop_back();
    onPath[curr] = 0;

    return 0;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin>>n>>m;

    graph g(n);

    for (int a = 0; a < n; a++)
    {
        int ne;
        cin>>ne;
        for (int i = 0; i < ne; i++)
        {
            int b;
            cin>>b;
            g[a].push_back(--b);
        }
    }

    int s;
    cin>>s;

    vector <int> sol;
    onPath.resize(n), visited.resize(n, vector<int>(2));

    int solvable = dfs(g, --s, sol, 0);

    if (solvable == 1)
    {
        cout<<"Win"<<'\n';
        for (int i: sol)
        {
            cout<<i<<" ";
        }
        cout<<'\n';
    }
    else if(hasCycle)
    {
        cout<<"Draw"<<'\n';
    }
    else
    {
        cout<<"Lose"<<'\n';
    }

    return 0;
}

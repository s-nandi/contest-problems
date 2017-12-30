//dfs traversal, interval decomposition
//https://open.kattis.com/problems/securitybadge (2017 Mid-Atlantic Regional)

#include <set>
#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

#define ii pair<int, int>

vector <vector<int> > graph;
map <ii, ii> allowed;

bool dfs(vector <int> &visited, int curr, ii interval, int end)
{
    visited[curr] = 1;

    if (curr == end)
    {
        return true;
    }
    bool foundEnd = false;
    for (int neighbor: graph[curr])
    {
        ii requiredRange = allowed[ {curr, neighbor}];

        if (!visited[neighbor] and requiredRange.first <= interval.first and requiredRange.second >= interval.second)
        {
            foundEnd |= dfs(visited, neighbor, interval, end);
        }
    }
    return foundEnd;
}


int main()
{
    int n, m, b;
    cin>>n>>m>>b;

    int start, end;
    cin>>start>>end;
    --start;
    --end;

    graph.resize(n);
    vector <int> changes;

    for (int i = 0; i < m; i++)
    {
        int a, b, l, r;
        cin>>a>>b>>l>>r;
        --a;
        --b;
        graph[a].push_back(b);

        changes.push_back(l);
        changes.push_back(r);

        allowed[ {a, b}] = {l, r};
    }

    sort(changes.begin(), changes.end());

    int res = 0;
    bool prevReached = false;
    set <int> added;

    for (int i = 0; i < changes.size() - 1; i++)
    {
        vector <int> visited(graph.size(), 0);
        ii attemptedInterval = {changes[i], changes[i + 1]};
        bool reached = dfs(visited, start, attemptedInterval, end);
        if (reached)
        {
            added.insert(i);
            added.insert(i+1);

            res += changes[i+1] - changes[i];
            if (!prevReached)
            {
                res++;
            }
            prevReached = true;
        }
        else
        {
            prevReached = false;
        }
    }

    for (int i = 0; i < changes.size(); i++)
    {
        if (added.count(i) == 0)
        {
            ii attemptedInterval = {changes[i], changes[i]};
            vector <int> visited(graph.size(), 0);
            bool reached = dfs(visited,  start, attemptedInterval, end);
            if (reached)
            {
                res++;
            }
        }
    }

    cout << res <<'\n';
    return 0;
}

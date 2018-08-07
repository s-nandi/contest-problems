// toposort (shortest path on DAG), shortest path condition (edge ij on sh. path -> d[j] == d[i] + w_ij), generating combinations (depth limited dfs)
// https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&category=&problem=4109&mosmsg=Submission+received+with+ID+2422939
// 2012 Mid-Central Regional

#include <bits/stdc++.h>

using namespace std;

const int INF = 1231231234;
const int THRESHOLD = 7;

struct edge{int to, weight;};
typedef vector <vector<edge>> graph;

vector <int> toposort(graph &g)
{
    int n = g.size();
    queue <int> q;
    vector <int> inDegree(n), sorted;

    for (int i = 0; i < n; i++) for (edge e: g[i])
        inDegree[e.to]++;
    for (int i = 0; i < n; i++) if (inDegree[i] == 0)
        q.push(i);

    while (!q.empty())
    {
        int curr = q.front();
        q.pop();
        sorted.push_back(curr);

        for (edge e: g[curr]) if (--inDegree[e.to] == 0)
            q.push(e.to);
    }
    return sorted;
}

int n;
vector <int> revsorted;
vector <int> dist;

int feasible(graph &g, set <int> &marks)
{
    vector <int> unambiguous(n);
    unambiguous[n - 1] = true;

    for (int i: revsorted)
    {
        int feasibleNeighbors = 0;
        for (edge e: g[i])
        {
            if (unambiguous[e.to] and dist[i] == e.weight + dist[e.to])
                feasibleNeighbors++;
        }
        if (feasibleNeighbors == g[i].size() or (feasibleNeighbors >= 1 and marks.count(i)))
            unambiguous[i] = true;
    }
    return unambiguous[0];
}

int bestCombination(graph &g, set <int> &marks)
{
    if (feasible(g, marks)) return marks.size();

    int best = INF;
    if (marks.size() < THRESHOLD - 1)
    {
        int start = marks.size() > 0 ? *marks.rbegin() + 1 : 0;
        for (int i = start; i < g.size(); i++) if (marks.count(i) == 0)
        {
            marks.insert(i);
            best = min(best, bestCombination(g, marks));
            marks.erase(i);
        }
    }
    return best;
}

pair <int, int> solve(graph &g)
{
    dist.assign(n, INF);
    dist[n - 1] = 0;
    for (int i: revsorted)
    {
        for (edge e: g[i])
            dist[i] = min(dist[i], dist[e.to] + e.weight);
    }
    set <int> marks;
    return {dist[0], min(THRESHOLD, bestCombination(g, marks))};
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    while (true)
    {
        cin>>n;
        if (n == 0) break;

        graph g(n);
        for (int i = 0; i < n; i++)
        {
            char name;
            int degree;
            cin>>name>>degree;
            for (int j = 0; j < degree; j++)
            {
                char neighbor;
                int weight;
                cin>>neighbor>>weight;
                g[i].push_back({neighbor - 'A', weight});
            }
        }

        revsorted = toposort(g);
        reverse(revsorted.begin(), revsorted.end());

        auto sol = solve(g);
        cout<<sol.first<<" "<<sol.second<<'\n';
    }

    return 0;
}

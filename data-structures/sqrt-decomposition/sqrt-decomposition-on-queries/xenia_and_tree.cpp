//sqrt decomposition on queries, binary lifting for lowest common ancestor, bfs
//http://codeforces.com/contest/342/problem/E

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define INF 1231231234

vector <vector<int>> graph;
vector <int> delayed, distances;

const int bucket_size = 79; //queries are significantly more expensive

int ln = 0;
vector <vector<int>> binaryLift;
vector <int> depth;

void buildLift(int curr)
{
    for (int i = 1; i < ln; i++)
    {
        binaryLift[curr][i] = binaryLift[curr][i - 1] != -1 ? binaryLift[binaryLift[curr][i - 1]][i - 1] : -1;
    }
    for (int i: graph[curr]) if (i != binaryLift[curr][0])
    {
        binaryLift[i][0] = curr;
        depth[i] = depth[curr] + 1;
        buildLift(i);
    }
}

int lowestCommonAncestor(int l, int r)
{
    if (depth[l] > depth[r]) swap(l, r);
    int diff = depth[r] - depth[l];

    for (int i = ln - 1; i >= 0; i--)
    {
        if (1 << i & diff)
        {
            r = binaryLift[r][i];
        }
    }
    if (l == r) return l;

    for (int i = ln - 1; i >= 0; i--)
    {
        if (binaryLift[l][i] != binaryLift[r][i])
        {
            l = binaryLift[l][i], r = binaryLift[r][i];
        }
    }
    return binaryLift[l][0];
}

int pathDistance(int l, int r)
{
    return depth[l] + depth[r] - 2 * depth[lowestCommonAncestor(l, r)];
}

void update()
{
    queue <int> q;
    for (int i: delayed)
    {
        q.push(i);
        distances[i] = 0;
    }

    while(!q.empty())
    {
        int curr = q.front();
        q.pop();

        for (int neighbor: graph[curr])
        {
            if(distances[curr] + 1 < distances[neighbor])
            {
                distances[neighbor] = distances[curr] + 1;
                q.push(neighbor);
            }
        }
    }
    delayed.clear();
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin>>n>>m;
    while (1 << ln < n) ln++;

    graph.resize(n);
    binaryLift.resize(n, vector<int>(ln));
    depth.resize(n);
    distances.resize(n, INF);

    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin>>a>>b;
        --a; --b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    buildLift(0);

    delayed.push_back(0);
    update();

    for (int i = 0; i < m; i++)
    {
        int type, v;
        cin>>type>>v;
        --v;
        if (type == 1)
        {
            delayed.push_back(v);
            if (delayed.size() == bucket_size)
            {
                update();
            }
        }
        else
        {
            int nearest = distances[v];
            for (int redNode: delayed)
            {
                nearest = min(nearest, pathDistance(v, redNode));
            }
            cout<<nearest<<'\n';
        }
    }

    return 0;
}

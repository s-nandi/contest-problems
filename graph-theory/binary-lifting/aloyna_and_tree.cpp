//binary lifting, partial sum on tree
//http://codeforces.com/problemset/problem/739/B

#include <iostream>
#include <vector>
#include <map>

using namespace std;

#define ll long long

struct edge
{
    int a;
    int b;
    bool operator < (edge o) const
    {
        return a < o.a or (a == o.a and b < o.b);
    }

};

vector <ll> val;
vector <vector<int> > graph;
map <edge, ll> weight;

vector <ll> distArr;

vector <vector<int> > binLift;
vector <int> pow2;

void precompute(int n)
{
    int curr = 1;
    while(curr <= n)
    {
        pow2.push_back(curr);
        curr *= 2;
    }
}


void dfs(int curr, ll dist, int currDepth)
{
    distArr[curr] = dist;

    for (int i = 1; i < pow2.size(); i++)
    {
        if (pow2[i] > currDepth) break;
        binLift[curr][i] = binLift[binLift[curr][i - 1]][i - 1];
    }

    for (int neighbor: graph[curr])
    {
        dfs(neighbor, dist + weight[ {curr, neighbor}], currDepth + 1);
    }
}

void solve(int node, vector <int> &sol)
{
    ll lb = distArr[node] - val[node];

    int curr = node;

    for (int i = pow2.size() - 1; i >= 0; i--)
    {
        if (binLift[curr][i] == -1 or distArr[binLift[curr][i]] < lb)
        {
            continue;
        }

        curr = binLift[curr][i];
    }
    if (curr != node and distArr[curr] >= lb)
    {
        sol[curr]--;
        sol[node]++;
    }
}

int push(int curr, vector <int> &sol, vector <int> &res)
{
    int neighborSum = 0;

    for (int neighbor: graph[curr])
    {
        neighborSum += push(neighbor, sol, res);
    }
    res[curr] = neighborSum;

    return neighborSum + sol[curr];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin>>n;

    precompute(n);

    val.resize(n);
    graph.resize(n);
    distArr.resize(n);

    binLift.resize(n, vector <int>(pow2.size(), -1));


    for (int i = 0; i < n; i++)
    {
        cin>>val[i];
    }
    for (int i = 1; i < n; i++)
    {
        int p;
        ll w;
        cin>>p>>w;
        --p;
        graph[p].push_back(i);
        weight[ {p, i}] = w;
        binLift[i][0] = p;
    }

    dfs(0, 0, 0);


    vector <int> prefixSolution(n);
    for (int i = 0; i < n; i++)
        solve(i, prefixSolution);


    vector <int> result(n);
    push(0, prefixSolution, result);

    for (int res: result)
    {
        cout<<res<<" ";
    }
    cout<<'\n';

    return 0;
}

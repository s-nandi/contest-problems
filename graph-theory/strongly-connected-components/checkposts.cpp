//strongly connected components (kosaraju)
//http://codeforces.com/problemset/problem/427/C

#include <iostream>
#include <vector>
#include <stack>

#define INF 123123123123123
#define MOD 1000000007
#define ll long long

using namespace std;

ll minimumCost, numberOfWays;
vector <int> costs;

vector <vector<int>> graph, transpose;
stack <int> order;
vector <int> visited, components;
int scc_sz = 0;

void ordering(int curr)
{
    visited[curr] = 1;
    for (int neighbor: graph[curr])
    {
        if (!visited[neighbor])
        {
            ordering(neighbor);
        }
    }
    order.push(curr);
}

void categorize(int curr)
{
    visited[curr] = 0;
    components[curr] = scc_sz;
    for (int neighbor: transpose[curr])
    {
        if (visited[neighbor])
        {
            categorize(neighbor);
        }
    }
}

void kosarajuSCC()
{
    int n = graph.size();
    visited.resize(n, 0);
    components.resize(n, -1);

    for (int i = 0; i < n; i++)
    {
        if (visited[i]) continue;

        ordering(i);
    }

    while (!order.empty())
    {
          int curr = order.top();
          order.pop();

          if (!visited[curr]) continue;

          categorize(curr);
          scc_sz++;
    }
}

void solve()
{
    kosarajuSCC();

    vector <ll> cheapest(scc_sz, INF), numChoices(scc_sz);
    for (int i = 0; i < graph.size(); i++)
    {
        int ind = components[i];
        if (costs[i] < cheapest[ind])
        {
            cheapest[ind] = costs[i];
            numChoices[ind] = 1;
        }
        else if(costs[i] == cheapest[ind])
        {
            numChoices[ind]++;
        }
    }

    minimumCost = 0, numberOfWays = 1;
    for (int i = 0; i < scc_sz; i++)
    {
        minimumCost += cheapest[i];
        numberOfWays = (numberOfWays * numChoices[i]) % MOD;
    }
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;

    graph.resize(n);
    transpose.resize(n);
    costs.resize(n);

    for (int i = 0; i < n; i++)
    {
        cin>>costs[i];
    }

    int m;
    cin>>m;

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin>>a>>b;
        --a; --b;
        graph[a].push_back(b);
        transpose[b].push_back(a);
    }

    solve();
    cout<<minimumCost<<" "<<numberOfWays<<'\n';
}

//SCC (Kosaraju)

#include <stack>
#include <vector>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>

#define MOD 1000000007
#define ll long long

using namespace std;

stack <int> order;
vector <int> visited;

vector <int> components;
int curr_component = 0;

void dfsOrder(vector <vector<int>> &graph, int curr)
{
    visited[curr] = 1;

    for (int neighbor: graph[curr])
    {
        if (!visited[neighbor])
        {
            dfsOrder(graph, neighbor);
        }
    }

    order.push(curr);
}

void dfsReverse(vector <vector<int>> &graph, int curr)
{
    visited[curr] = 0;
    components[curr] = curr_component;

    for (int neighbor: graph[curr])
    {
        if (visited[neighbor])
        {
            dfsReverse(graph, neighbor);
        }
    }
}


void scc(vector <vector<int>> &g, vector <vector<int>> &tg)
{
    visited.resize(g.size(), 0);
    components.resize(g.size(), -1);

    for (int i = 0; i < g.size(); i++)
    {
        if (visited[i]) continue;

        dfsOrder(g, i);
    }

    while (!order.empty())
    {
          int start = order.top();
          order.pop();

          if (!visited[start]) continue;

          dfsReverse(tg, start);
          curr_component++;
    }
}


pair <ll, ll> check(vector <vector<int>> &graph, vector <int> &elements)
{
    int n = graph.size();
    vector <vector<int>> transpose(n, vector<int>());

    for (int i = 0; i < graph.size(); i++)
    {
        for(int j: graph[i])
        {
            transpose[j].push_back(i);
        }
    }

    scc(graph, transpose);

    map <int, ll> leastCost;
    map <int, ll> numWays;
    for (int i = 0; i < elements.size(); i++)
    {
        ll val = elements[i];
        ll ind = components[i];
        if (leastCost.count(ind) == 0)
        {
            leastCost[ind] = val;
            numWays[ind] = 1;
        }
        else if (val < leastCost[ind])
        {
            leastCost[ind] = val;
            numWays[ind] = 1;
        }
        else if(val == leastCost[ind])
        {
            numWays[ind]++;
        }
    }

    pair <ll, ll> res;
    ll cost, ways;
    cost = 0;
    ways = 1;
    for (auto elem: leastCost)
    {
        int ind = elem.first;
        ll minCost = elem.second;
        ll waysThis = numWays[ind];

        cost += minCost;
        ways = (waysThis * ways) % MOD;
    }

    res.first = cost;
    res.second = ways;
    return res;
}


int main()
{
    int n;
    cin>>n;
    vector <int> checks(n);
    for (int i = 0; i < n; i++)
    {
        cin>>checks[i];
    }
    vector <vector<int>> graph(n, vector<int>());
    int m;
    cin>>m;
    for (int i = 0; i <m; i++)
    {
        int from, to;
        cin>>from>>to;
        --from;
        --to;
        graph[from].push_back(to);
    }

    pair<ll, ll>  res = check(graph, checks);
    cout<<res.first<<" "<<res.second<<endl;
}

//network flow (edmond-karp), sieve factorization
//http://codeforces.com/contest/498/problem/C

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

#define INF 12312312

vector <int> a;
vector <vector<int>> graph;
vector <vector<int>> residual;

set <int> primes;
map <pair<int, int>, int> factors;

int SQRTN;

void sieve()
{
    vector <int> isPrime(SQRTN, 1);
    for (int i = 2; i < SQRTN; i++)
    {
        if (!isPrime[i]) continue;
        primes.insert(i);

        for (int j = i * i; j < SQRTN; j += i)
        {
            isPrime[j] = 0;
        }
    }

    for (int i = 0; i < a.size(); i++)
    {
        int num = a[i];
        for (int p: primes)
        {
            int acc = 0;
            while (num % p == 0)
            {
                acc++;
                num /= p;
            }
            factors[{a[i], p}] = acc;
        }

        if (num != 1)
        {
            primes.insert(num);
            factors[{i, num}] = 1;
        }
    }
}

int bfs(int source, int sink)
{
    queue <int> q;
    vector <int> anc(graph.size(), -1);
    q.push(source);

    bool reached = false;

    while (!q.empty())
    {
        int curr = q.front();
        q.pop();

        if (curr == sink)
        {
            reached = true;
            break;
        }

        for (int neighbor: graph[curr])
        {
            if (anc[neighbor] == -1 and residual[curr][neighbor] > 0)
            {
                q.push(neighbor);
                anc[neighbor] = curr;
            }
        }
    }

    if (!reached)
    {
        return 0;
    }

    int node = sink;
    int augment = INF;

    while (node != source)
    {
        int prev = anc[node];
        augment = min(augment, residual[prev][node]);
        node = prev;
    }

    node = sink;

    while (node != source)
    {
        int prev = anc[node];
        residual[prev][node] -= augment;
        residual[node][prev] += augment;
        node = prev;
    }

    return augment;
}

int edmondkarp(int source, int sink)
{
    int res = 0;
    while (true)
    {
        int delta = bfs(source, sink);
        if (delta == 0)
        {
            break;
        }
        res += delta;
    }

    return res;
}

int main()
{
    int n, m;
    cin>>n>>m;

    a.resize(n);

    int MAXN = -1;
    for (int i = 0; i < n; i++)
    {
        cin>>a[i];
        MAXN = max(MAXN, a[i]);
    }
    SQRTN = sqrt(MAXN);

    sieve();

    int s = n;
    int t = n + 1;

    graph.resize(n + 2);
    residual.resize(n + 2, vector<int>(n + 2));

    for (int i = 0; i < m; i++)
    {
        int n1, n2;
        cin>>n1>>n2;
        --n1; --n2;

        if (!(n1 & 1))
        {
            swap(n1, n2);
        }

        graph[n1].push_back(n2);
        graph[n2].push_back(n1);

        residual[n1][n2] = INF;
        residual[n2][n1] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        if (i & 1)
        {
            graph[s].push_back(i);
        }
        else
        {
            graph[i].push_back(t);
        }
    }

    vector <vector<int>> residualCopy(residual);

    int sol = 0;

    for (int p: primes)
    {
        residual = residualCopy;
        for (int i = 0; i < n; i++)
        {
            int capacity =  factors.count({a[i], p}) ? factors[{a[i], p}] : 0;

            if (i & 1)
            {
                residual[s][i] = capacity;
            }
            else
            {
                residual[i][t] = capacity;
            }
        }

        sol += edmondkarp(s, t);
    }

    cout<<sol<<'\n';

    return 0;
}

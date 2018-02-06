//expected value, priority first search, greedy
//http://codeforces.com/contest/912/problem/D

#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <iomanip>

using namespace std;

#define ll long long

typedef pair<int, int> position;

int n, m, r, k;
vector <int> dx = {0, -1, 0, 1};
vector <int> dy = {-1, 0, 1, 0};

ll numScoops(int x, int y)
{
    return (ll) (min(x, n - r) - max(x - r + 1, 0) + 1) * (min(y, m - r) - max(y - r + 1, 0) + 1);
}

struct node
{
    int x, y; ll value;

    node(int i, int j)
    {
        x = i, y = j, value = numScoops(x, y);
    }

    bool operator < (node o) const
    {
        return value != o.value ? value < o.value : make_pair(x, y) < make_pair(o.x, o.y);
    }
};

bool inBounds(int x, int y)
{
    return x >= 0 and y >= 0 and x < n and y < m;
}

int main()
{
    cin>>n>>m>>r>>k;

    priority_queue<node, vector<node>, less<node>> pq;
    pq.push(node{n / 2, m / 2});

    set <position> visited;
    visited.insert({n / 2, m / 2});

    ll totalValue = 0;
    int added = 0;
    while (added < k and !pq.empty())
    {
        node curr = pq.top();
        pq.pop();

        totalValue += curr.value;
        added++;

        for (int i = 0; i < 4; i++)
        {
            int nx = curr.x + dx[i], ny = curr.y + dy[i];

            if (inBounds(nx, ny) and visited.count({nx, ny}) == 0)
            {
                visited.insert({nx, ny});
                pq.push({nx, ny});
            }
        }
    }

    double denominator = (ll) (n - r + 1) * (m - r + 1);
    cout<<setprecision(9)<<fixed<<totalValue / denominator<<'\n';

    return 0;
}

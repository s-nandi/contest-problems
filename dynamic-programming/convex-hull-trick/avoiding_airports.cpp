//dynamic programming, convex hull trick
//https://open.kattis.com/problems/avoidingairports (2017 Mid-Atlantic Regional)

#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

#define ll long long
#define INF 123123123121231

struct node
{
    int endTime;
    ll cost;

    ll value(int startTime)
    {
        ll diff = startTime - endTime;
        return diff * diff + cost;
    }

    double overtake(node b)
    {
        double quotient1 = float(b.cost - cost) / (b.endTime - endTime);
        return (quotient1 + b.endTime + endTime)/2.0;
    }
};

struct cht
{
    vector <node> hull;

    ll bestCost(int time)
    {
        if (hull.size() == 0)
        {
            return INF;
        }

        node temp = {time, 0};
        int maxv = upper_bound(hull.begin(), hull.end(), temp, [](node a, node b){return a.endTime < b.endTime;}) - hull.begin();

        if (maxv == 0)
        {
            return INF;
        }

        maxv--;

        ll left = 1;
        ll right = maxv;

        while (left < right)
        {
            ll mid = (left + right) / 2;
            if (hull[mid - 1].overtake(hull[mid]) >= time)
            {
                right = mid;
            }
            else
            {
                left = mid + 1;
            }
        }

        if (hull[left - 1].overtake(hull[left]) < time)
        {
            return hull[maxv].value(time);
        }
        else
        {
            return hull[left - 1].value(time);
        }
    }

    void addNode(node newNode)
    {
        while (hull.size() >= 2 and hull[hull.size() - 2].overtake(newNode) < hull[hull.size() - 2].overtake(hull[hull.size() - 1]))
        {
            hull.pop_back();
        }
        hull.push_back(newNode);
    }
};

struct edge
{
    int a;
    int b;
    int s;
    int e;
    bool operator < (edge b) const
    {
        return e < b.e;
    }
};

int main()
{
    int n, m;
    cin>>n>>m;
    vector <edge> edges;
    for (int i = 0; i < m; i++)
    {
        int a, b, s, e;
        cin>>a>>b>>s>>e;
        --a; --b;
        edges.push_back({a, b, s, e});
    }

    sort(edges.begin(), edges.end());

    vector <cht> hulls(n);
    hulls[0].hull.push_back({0, 0});

    ll sol = -1;

    if (n == 1)
    {
        cout<<0<<'\n';
    }
    else
    {
        for (edge e: edges)
        {
            int from = e.a;
            int to = e.b;
            int startTime = e.s;
            int endTime = e.e;

            ll minCost = hulls[from].bestCost(startTime);
            hulls[to].addNode({endTime, minCost});

            if (to == n - 1)
            {
                if (sol == -1 or minCost < sol)
                {
                    sol = minCost;
                }
            }
        }

        cout<<sol<<'\n';
    }

    return 0;
}

//binary search on answer (simulation)
//http://codeforces.com/contest/913/problem/D

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct node
{
    int limit;
    int time;
    int index;

    bool operator < (node o) const
    {
        if (time != o.time) return time < o.time;
        return index < o.index;
    }
};

vector <node> nodes;

bool simulate(int m, int threshold)
{
    if (m == 0) return true;
    int printed = 0, totalTime = 0;
    for (node no: nodes)
    {
        if (no.limit < m) continue;
        totalTime += no.time;
        if (++printed == m or totalTime > threshold) break;
    }

    bool res = totalTime <= threshold and printed == m ? true : false;
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, t;
    cin>>n>>t;

    for (int i = 0; i < n; i++)
    {
        int a, time;
        cin>>a>>time;
        nodes.push_back({a, time, i + 1});
    }
    sort(nodes.begin(), nodes.end());

    int l = 0;
    int r = n;

    while (l < r)
    {
        int m = (l + r + 1) / 2;

        if (simulate(m, t))
        {
            l = m;
        }
        else
        {
            r = m - 1;
        }
    }

    cout<<l<<'\n'<<l<<'\n';
    if (l > 0)
    {
        int printed = 0;
        for (node no: nodes)
        {
            if (no.limit < l) continue;
            cout<<no.index<<" ";
            if (++printed == l) break;
        }
    }
    cout<<'\n';

    return 0;
}

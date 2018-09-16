// 2 pointer technique
// http://codeforces.com/contest/1041/problem/D

#include <iostream>
#include <vector>

using namespace std;

const int INF = 1231231234;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, h;
    cin>>n>>h;

    vector <pair<int, int>> a(n);
    for (int i = 0; i < n; i++)
    {
        cin>>a[i].first>>a[i].second;
    }
    a.push_back({INF, INF + 1});

    int len = 0, gap = 0, best = -1;
    for (int l = 0, r = -1; l < n; l++)
    {
        while (r + 1 < n)
        {
            int widen = r + 1 == l ? 0 : a[r + 1].first - a[r].second;
            if (gap + widen < h)
            {
                gap += widen;
                len += a[r + 1].second - a[r + 1].first;
                r++;
            }
            else
                break;
        }
        best = max(best, len + h);

        len -= a[l].second - a[l].first;
        gap = l + 1 >= r ? 0 : gap - (a[l + 1].first - a[l].second);
    }
    cout<<best<<'\n';

    return 0;
}

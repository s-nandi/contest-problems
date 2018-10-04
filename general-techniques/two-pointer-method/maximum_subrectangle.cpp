// two pointer method, looping through fixed parameter to speed up
// http://codeforces.com/contest/1060/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 1231231231231234;

ll rangeSum(vector <ll> &ps, int l, int r)
{
    return l == 0 ? ps[r] : ps[r] - ps[l - 1];
}

vector <ll> prefixSums;
int longestColumn(int n, ll limit, vector <int> &col)
{
    ll smallestRow = INF;
    for (int i = 0; i + n - 1 < prefixSums.size(); i++)
        smallestRow = min(smallestRow, rangeSum(prefixSums, i, i + n - 1));

    int mx = 0;
    int cost = 0;
    for (int l = 0, r = 0; l < col.size(); l++)
    {
        while (r < col.size() and ((ll) cost + col[r]) * smallestRow <= limit)
        {
            cost += col[r];
            r++;
        }
        mx = max(mx, r - l);
        cost -= col[l];
    }
    return mx;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector <int> a(n), b(m);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++)
    {
        cin >> b[i];
    }

    int limit;
    cin >> limit;

    prefixSums.resize(n);
    prefixSums[0] = a[0];
    for (int i = 1; i < n; i++)
        prefixSums[i] = prefixSums[i - 1] + a[i];

    int best = 0;
    for (int d1 = 1; d1 <= n; d1++)
        best = max(best, d1 * longestColumn(d1, limit, b));
    cout << best << '\n';
}

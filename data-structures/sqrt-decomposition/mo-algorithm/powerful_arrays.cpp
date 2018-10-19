//sqrt decomposition, mo's algorithm
//http://codeforces.com/problemset/problem/86/D

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int BLOCK = 447;
const int MAXN = 1000000;

struct mo_query
{
    int l, r, ind;

    bool operator < (mo_query o) const
    {
        if (l / BLOCK != o.l / BLOCK)
            return l < o.l;
        else
            return (l / BLOCK) & 1 ? (o.r < r) : (r < o.r);
    }
};

int counts[MAXN + 5];
void mo_add(ll elem, ll &sol)
{
    int cnt = counts[elem]++;
    sol += elem * ((cnt + 1) * (cnt + 1) - cnt * cnt);
}

void mo_rmv(ll elem, ll &sol)
{
    int cnt = counts[elem]--;
    sol -= elem * (cnt * cnt - (cnt - 1) * (cnt - 1));
}

int main()
{
    int n, q;
    cin>>n>>q;

    vector <int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    vector <mo_query> queries(q);
    for (int i = 0; i < q; i++)
    {
        int l, r;
        cin>>l>>r;
        queries[i] = {--l, --r, i};
    }
    sort(queries.begin(), queries.end());

    ll sol = 0;
    int lp = 0, rp = 0;
    vector <ll> sols(q);
    for (auto q: queries)
    {
        while (lp < q.l)
            mo_rmv(a[lp++], sol);
        while (lp > q.l)
            mo_add(a[--lp], sol);
        while (rp <= q.r)
            mo_add(a[rp++], sol);
        while (rp - 1 > q.r)
            mo_rmv(a[--rp], sol);

        sols[q.ind] = sol;
    }

    for (auto i: sols)
        cout << i << '\n';
}

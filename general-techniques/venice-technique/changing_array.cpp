// venice map (xor), greedy (non-trivial proof)
// http://codeforces.com/contest/1054/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct veniceMap
{
    map <int, int> cnt;
    int level = 0;

    int operator [](int i)
    {
        int f = i ^ level;
        if (!cnt.count(f))
            return 0;
        return cnt[f];
    }

    void insert(int i)
    {
        level ^= i;
        cnt[i ^ level]++;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    int FULL = (1 << k) - 1;

    vector <int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    veniceMap counts;
    ll sol = 0;
    for (int i = 0; i < n; i++)
    {
        int regular = a[i];
        int flipped = FULL - a[i];

        ll rgain = (i + 1) - (counts[regular] + (regular == 0));
        ll fgain = (i + 1) - (counts[flipped] + (flipped == 0));

        if (rgain >= fgain)
        {
            sol += rgain;
            counts.insert(regular);
        }
        else
        {
            sol += fgain;
            counts.insert(flipped);
        }
    }
    cout << sol << '\n';
}

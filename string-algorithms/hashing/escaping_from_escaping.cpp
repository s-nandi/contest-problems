//double hashing, binary search on answer
//https://www.urionlinejudge.com.br/judge/en/problems/view/2093

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define ll long long

const int MAXN = 100005;
const int alpha = 37;
const int MOD[2] = {1000000007, 1000000013};

int pAlpha[2][MAXN];
void precompute_hash()
{
    for (int t = 0; t < 2; t++)
    {
        pAlpha[t][0] = 1;
        for (int i = 1; i < MAXN; i++)
            pAlpha[t][i] = (ll) alpha * pAlpha[t][i - 1] % MOD[t];
    }
}

int multpow(int v, int p, int t)
{
    return (ll) v * pAlpha[t][p] % MOD[t];
}

int mapping(char c){return c - '0' + 1;}

struct hasher
{
    int len = 0, t;
    vector <int> h;

    hasher(int type) : t(type) {h.assign(1, 0);}
    void init(string &s)
    {
        h.assign(1, 0), len = 0;
        for (int i = 0; i < s.length(); i++) push(s[i]);
    }

    void push(char c)
    {
        h.push_back(h[len] + multpow(mapping(c), len + 1, t));
        h.back() %= MOD[t];
        len++;
    }

    int query(int l, int r)
    {
        return multpow((h[r] - h[l - 1] + MOD[t]) % MOD[t], MAXN - l, t);
    }
};

struct hashPair
{
    hasher h[2] = {hasher(0), hasher(1)};

    hasher& operator [] (int i){return h[i];}
    pair <int, int> query(int l, int r){return {h[0].query(l, r), h[1].query(l, r)};}
};

int numHash(hashPair &hp, int len)
{
    vector <pair<int, int>> hashes;
    for (int i = 1; i + len - 1 <= hp[0].len; i++)
        hashes.push_back(hp.query(i, i + len - 1));
    sort(hashes.begin(), hashes.end());
    hashes.erase(unique(hashes.begin(), hashes.end()), hashes.end());
    return hashes.size();
}

int logn(int n)
{
    int ln = 0;
    while (1 << ln < n) ln++;
    return ln;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    precompute_hash();

    string s;
    cin>>s;

    hashPair h;
    h[0].init(s), h[1].init(s);

    int l = 1, r = logn(s.length()) + 1;
    while(l < r)
    {
        int m = (l + r) / 2;
        ll taken = numHash(h, m), possible = 1 << m;

        if (possible <= taken) l = m + 1;
        else r = m;
    }
    cout<<l<<'\n';

    return 0;
}

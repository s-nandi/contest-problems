//double hashing (prefix hashes, hash set), binary search on answer
//https://www.codechef.com/problems/SSTORY

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MAXN 250005
#define ll long long

int alpha[2] = {37, 53};
int MOD[2] = {1000000007, 1000000009};
vector <int> powAlpha[2];

int mult(int a, int b, int t)
{
    ll res = ((ll) a * (ll) b) % MOD[t];
    return res;
}

void precompute()
{
    for (int t = 0; t < 2; t++)
    {
        powAlpha[t].resize(MAXN);
        powAlpha[t][0] = 1;
        for (int i = 1; i < MAXN; i++)
        {
            powAlpha[t][i] = mult(alpha[t], powAlpha[t][i - 1], t);
        }
    }
}

struct subHash
{
    int hashValue;

    subHash(){}
    subHash(int hashing, int power, int t)
    {
        hashValue = mult(hashing, powAlpha[t][MAXN - power], t);
    }

    bool operator < (subHash o) const
    {
        return hashValue < o.hashValue;
    }
};

struct hasher
{
    int len;
    vector <int> prefixHash[2];

    void add(char c)
    {
        for (int t = 0; t < 2; t++)
            prefixHash[t].push_back((prefixHash[t][len] + mult(powAlpha[t][len + 1], (c - 'a' + 1), t)) % MOD[t]);
        len++;
    }

    void initialize(string &s)
    {
        len = 0;
        prefixHash[0] = {0}, prefixHash[1] = {0};
        for (int i = 0; i < s.size(); i++) add(s[i]);
    }

    pair <subHash, subHash> query(int l, int r)
    {
        pair <subHash, subHash> res;
        for (int t = 0; t < 2; t++)
        {
            auto curr = subHash((prefixHash[t][r] - prefixHash[t][l - 1] + MOD[t]) % MOD[t], l, t);
            if (t == 0) res.first = curr;
            else res.second = curr;
        }
        return res;
    }
};

int check(hasher &h1, hasher &h2, int len)
{
    vector <pair<subHash, subHash>> hashes;

    for (int i = 1; i + len - 1 <= h1.len; i++)
    {
        auto curr = h1.query(i, i + len - 1);
        hashes.push_back(curr);
    }
    sort(hashes.begin(), hashes.end());

    for (int i = 1; i + len - 1 <= h2.len; i++)
    {
        auto curr = h2.query(i, i + len - 1);
        if (binary_search(hashes.begin(), hashes.end(), curr)) return i - 1;
    }
    return -1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    precompute();
    string s, t;
    cin>>s>>t;

    hasher h1, h2;
    h1.initialize(s), h2.initialize(t);

    int l = 0, r = t.size(), pos;
    while(l < r)
    {
        int m = (l + r + 1) / 2;
        int res = check(h1, h2, m);

        if (res != -1)
        {
            l = m;
            pos = res;
        }
        else
        {
            r = m - 1;
        }
    }
    if (l == 0)
    {
        cout<<0<<'\n';
    }
    else
    {
        cout<<t.substr(pos, l)<<'\n';
        cout<<l<<'\n';
    }

    return 0;
}

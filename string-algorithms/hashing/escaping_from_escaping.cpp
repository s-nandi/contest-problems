//double hashing, binary search on answer
//https://www.urionlinejudge.com.br/judge/en/problems/view/2093

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

#define ll long long
#define MAXN 100005

int alpha[2] = {13, 37};
int MOD[2] = {1000000007, 1000000009};
vector <int> powAlpha[2];

int mult(int a, int b, int t)
{
    ll res = ((ll) a * b) % MOD[t];
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

     bool operator == (subHash o) const
    {
        return hashValue == o.hashValue;
    }
};

struct hasher
{
    int len;
    vector <int> prefixHash[2];

    void add(char c)
    {
        for (int t = 0; t < 2; t++)
            prefixHash[t].push_back((prefixHash[t][len] + mult(powAlpha[t][len + 1], (c - '0' + 1), t)) % MOD[t]);
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

int numHash(hasher &h, int len)
{
    vector <pair<subHash, subHash>> hashes;
    for (int i = 1; i + len - 1 <= h.len; i++)
    {
        hashes.push_back(h.query(i, i + len - 1));
    }
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

    precompute();

    string s;
    cin>>s;

    hasher h; h.initialize(s);

    int l = 1, r = logn(s.length()) + 1;
    while(l < r)
    {
        int m = (l + r) / 2;

        ll taken = numHash(h, m), possible = 1 << m;
        if (possible <= taken)
        {
            l = m + 1;
        }
        else
        {
            r = m;
        }
    }
    cout<<l<<'\n';

    return 0;
}

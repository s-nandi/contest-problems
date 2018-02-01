//double hashing (prefix hashes, hash set)
//http://codeforces.com/problemset/problem/271/D

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MAXN 1501
#define ll long long

int alpha[2] = {37, 53};
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

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    precompute();
    string s;
    cin>>s;
    int len = s.length();

    hasher h;
    h.initialize(s);

    string bstring;
    cin>>bstring;
    int bad[26];

    for (int i = 0; i < 26; i++)
    {
        bad[i] = bstring[i] == '0' ? 1 : 0;
    }

    int k;
    cin>>k;

    vector <int> prefixSums(len + 1);

    prefixSums[0] = 0;
    for (int i = 1; i <= len; i++)
    {
        prefixSums[i] = prefixSums[i - 1] + bad[s[i - 1] - 'a'];
    }

    vector <pair<subHash, subHash>> valid;

    for (int i = 1; i <= len; i++)
    {
        for (int j = i; j <= len; j++)
        {
            if (prefixSums[j] - prefixSums[i - 1] <= k)
            {
                valid.push_back(h.query(i, j));
            }
        }
    }
    sort(valid.begin(), valid.end());
    valid.erase(unique(valid.begin(), valid.end()), valid.end());

    cout<<valid.size()<<'\n';

    return 0;
}

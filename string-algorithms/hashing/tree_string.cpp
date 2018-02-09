//double hashing (prefix sums), dfs, backtrack
//http://codeforces.com/problemset/problem/291/E

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

#define ll long long
#define MAXN 1000005

typedef vector <vector<int>> graph;

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

    bool operator == (subHash o) const
    {
        return hashValue == o.hashValue;
    }
};

struct hasher
{
    int len;
    vector <int> prefixHash[2];

    void addChar(char c)
    {
        for (int t = 0; t < 2; t++)
            prefixHash[t].push_back((prefixHash[t][len] + mult(powAlpha[t][len + 1], (c - 'a' + 1), t)) % MOD[t]);
        len++;
    }

    void removeChar()
    {
        for (int t = 0; t < 2; t++) prefixHash[t].pop_back();
        len--;
    }

    void initialize(string &s)
    {
        len = 0;
        prefixHash[0] = {0}, prefixHash[1] = {0};
        for (int i = 0; i < s.size(); i++) addChar(s[i]);
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

hasher wordHash, needleHash;
pair <subHash, subHash> target;

int dfs(graph &g, int curr, vector <string> &edges)
{
    int res = 0;
    for (char c: edges[curr])
    {
        wordHash.addChar(c);
        if (wordHash.len >= needleHash.len)
        {
            auto subword = wordHash.query(wordHash.len - needleHash.len + 1, wordHash.len);
            if (subword == target) res++;
        }
    }
    for (int neighbor: g[curr])
    {
        res += dfs(g, neighbor, edges);
    }
    for (int i = 0; i < edges[curr].length(); i++)
    {
        wordHash.removeChar();
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    precompute();
    int n;
    cin>>n;

    graph g(n);
    vector <string> edges(n);
    edges[0] = "";

    for (int i = 1; i <= n - 1; i++)
    {
        int p; string s;
        cin>>p>>s;
        g[--p].push_back(i);
        edges[i] = s;
    }

    string needle, blank = "";
    cin>>needle;

    needleHash.initialize(needle);
    wordHash.initialize(blank);

    target = needleHash.query(1, needleHash.len);
    cout<<dfs(g, 0, edges)<<'\n';

    return 0;
}

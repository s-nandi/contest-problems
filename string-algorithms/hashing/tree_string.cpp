//double hashing (prefix sums), dfs, backtrack
//http://codeforces.com/problemset/problem/291/E

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define ll long long

const int MAXN = 300005;
const int alpha = 37;
const int MOD[2] = {1000000007, 1000000009};

struct edge{int to; string str;};
typedef vector <vector<edge>> graph;

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

int mapping(char c){return c - '0' + 1;} //PS: remember to offset by 1

struct hasher
{
    int len, t;
    vector <int> h;

    hasher(int type) : t(type) {h.assign(1, 0), len = 0;}
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

    void pop(){h.pop_back(), len--;}

    int query(int l, int r)
    {
        ++l, ++r;
        return multpow((h[r] - h[l - 1] + MOD[t]) % MOD[t], MAXN - l, t);
    }
};

struct hashPair
{
    hasher h[2] = {hasher(0), hasher(1)};

    hasher& operator [] (int i){return h[i];}
    int length(){return h[0].len;}
    pair <int, int> query(int l, int r){return {h[0].query(l, r), h[1].query(l, r)};}
};

hashPair h, th;
pair <int, int> target;

int dfs(graph &g, int curr, const string &prevEdge)
{
    int res = 0;
    for (char c: prevEdge)
    {
        h[0].push(c), h[1].push(c);
        if (h.length() >= th.length())
        {
            auto possible = h.query(h.length() - th.length(), h.length() - 1);
            if (possible == target) res++;
        }
    }
    for (edge e: g[curr])
        res += dfs(g, e.to, e.str);
    for (int i = 0; i < prevEdge.length(); i++)
        h[0].pop(), h[1].pop();
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    precompute_hash();

    int n;
    cin>>n;

    graph g(n);
    for (int i = 1; i < n; i++)
    {
        int a; string s;
        cin>>a>>s;
        g[--a].push_back({i, s});
    }
    string t;
    cin>>t;

    th[0].init(t), th[1].init(t);
    target = th.query(0, t.length() - 1);

    cout<<dfs(g, 0, "")<<'\n';

    return 0;
}

// matrix exponentiation (creating transition matrix w/ bitmasks, using fibonacci to count)
// http://codeforces.com/gym/101635 (problem C)
// 2017 Southwest European Regional

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 1000000000;
const int MAXN = 8;
const int MAXB = (1 << MAXN);

typedef ll matT;
struct matrix : vector<vector<matT>>
{
    matrix(int r, int c, int v = 0){resize(r, vector<matT>(c, v));}
};

matrix operator * (const matrix &a, const matrix &b)
{
    matrix c(a.size(), b[0].size());
    for (int i = 0; i < a.size(); i++)
        for (int k = 0; k < b.size(); k++)
            for (int j = 0; j < b[0].size(); j++)
                c[i][j] = (c[i][j] + (ll) a[i][k] * b[k][j] % MOD) % MOD;
    return c;
}

matrix operator ^ (const matrix &a, ll p)
{
    matrix acc(a.size(), a.size()), res = a;
    for (int i = 0; i < a.size(); i++)
        acc[i][i] = 1;
    for (; p; p >>= 1)
    {
        if (p & 1)
            acc = acc * res;
        res = res * res;
    }
    return acc;
}

int n;
bitset <MAXB> convert(int bm)
{
    bitset <MAXB> res;
    for (int i = 0; i < n; i++)
        res[i] = bm & (1 << i) ? 1 : 0;
    return res;
}

int fib[MAXN + 5];
void precompute()
{
    fib[1] = 1, fib[2] = 2;
    for (int i = 3; i <= MAXN; i++)
        fib[i] = fib[i - 1] + fib[i - 2];
}

ll numWays(bitset <MAXB> &from, bitset <MAXB> &to)
{
    bitset <MAXB> filled;
    for (int i = 0; i < n; i++)
    {
        if (from[i] == 1 and to[i] == 1)
            return 0;
        else if(from[i] == 0 and to[i] == 1)
            filled[i] = 1;
        else
            filled[i] = from[i];
    }

    vector <int> stretches;
    for (int i = 0; i < n; i++) if (filled[i] == 0)
    {
        int old = i;
        while (i + 1 < n and filled[i + 1] == 0)
            i++;
        stretches.push_back(i - old + 1);
    }

    ll ways = 1;
    for (int i: stretches)
    {
        ways = ways * fib[i];
        ways %= MOD;
    }
    return ways;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    precompute();

    ll m;
    cin >> n >> m;

    vector <bitset<MAXB>> converted(1 << n);
    for (int i = 0; i < (1 << n); i++)
        converted[i] = convert(i);

    matrix mat(1 << n, 1 << n);
    for (int i = 0; i < (1 << n); i++)
    {
        for (int j = 0; j < (1 << n); j++)
            mat[i][j] = numWays(converted[i], converted[j]);
    }

    auto res = mat ^ m;
    cout << res[0][0] << '\n';
}

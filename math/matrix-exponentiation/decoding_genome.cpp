//matrix exponentiation, combinatorics(recurrence relation)
//http://codeforces.com/contest/222/problem/E

#include <iostream>
#include <vector>

using namespace std;

#define MOD 1000000007
#define ll long long

struct matrix
{
    vector <vector<ll>> values;
    int h;
    int w;

    matrix(int height, int width, int v = 0)
    {
        h = height;
        w = width;
        values.resize(h, vector<ll>(w, v));
    }

    matrix operator * (matrix o)
    {
        matrix res(h, o.w);
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < o.w; j++)
            {
                ll sum = 0;
                for (int k = 0; k < w; k++)
                {
                    sum = (sum + (values[i][k] * o.values[k][j]) % MOD) % MOD;
                }
                res.values[i][j] = sum;
            }
        }
        return res;
    }

    matrix pow(ll p)
    {
        matrix acc(h, w);
        for (int i = 0; i < w; i++)
        {
            acc.values[i][i] = 1;
        }

        matrix res = *this;

        while (p)
        {
            if (p & 1)
            {
                acc = acc * res;
            }

            res = res * res;
            p /= 2;
        }

        return acc;
    }
};

int mapping(char c)
{
    if (c >= 'a' and c <= 'z')
    {
        return c - 'a';
    }
    else
    {
        return c - 'A' + 26;
    }
}

int main()
{
    ll n, m, k;
    cin>>n>>m>>k;

    matrix state(m, m, 1);

    for (int i = 0; i < k; i++)
    {
        char a, b;
        cin>>a>>b;
        state.values[mapping(a)][mapping(b)] = 0;
    }

    matrix ones(m, 1, 1);
    matrix res = state.pow(n - 1) * ones;

    ll sol = 0;
    for (int i = 0; i < m; i++)
    {
        sol = (res.values[i][0] + sol) % MOD;
    }
    cout<<sol<<'\n';

    return 0;
}

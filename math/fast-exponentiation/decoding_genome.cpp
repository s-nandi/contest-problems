//matrix exponentiation, combinatorics(recurrence relation)
//http://codeforces.com/contest/222/problem/E

#include <iostream>
#include <vector>

using namespace std;

#define MOD 1000000007
#define ll long long

struct matrix
{
    vector <vector<ll>> val;
    int h;
    int w;

    matrix(int height, int width, int init = 0, bool isIdentity = false)
    {
        h = height;
        w = width;
        val.resize(h, vector<ll>(w, init));

        if (isIdentity)
        {
            for (int i = 0; i < h; i++)
            {
                val[i][i] = 1;
            }
         }
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
                    sum = (sum + (val[i][k] * o.val[k][j]) % MOD) % MOD;
                }
                res.val[i][j] = sum;
            }
        }
        return res;
    }

    matrix pow(ll p)
    {
        matrix acc(h, w, 0, true);
        matrix res = *this;

        if (p == 0)
        {
            return acc;
        }
        while (p > 1)
        {
            if (p % 2 == 0)
            {
                res = res * res;
                p /= 2;
            }
            else
            {
                acc = acc * res;
                res = res * res;
                p =  (p - 1) / 2;
            }
        }

        return acc * res;
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
        state.val[mapping(a)][mapping(b)] = 0;
    }

    matrix ones(m, 1, 1);
    matrix res = state.pow(n - 1) * ones;

    ll sol = 0;
    for (int i = 0; i < m; i++)
    {
        sol = (res.val[i][0] + sol) % MOD;
    }
    cout<<sol<<'\n';

    return 0;
}

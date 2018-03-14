//matrix exponentiation, combinatorics(recurrence relation)
//http://codeforces.com/contest/222/problem/E

#include <iostream>
#include <vector>

using namespace std;

#define ll long long

const int MOD = 1000000007;

int mult(int a, int b)
{
    return ((ll) a * b) % MOD;
}

struct matrix : vector <vector<ll>>
{
    matrix(int h, int w, int v){resize(h, vector<ll>(w, v));}
    matrix(int h, int w) : matrix(h, w, 0) {}
    int height(){return (*this).size();}
    int width(){return (*this)[0].size();}

    matrix operator * (matrix &o)
    {
        matrix c(height(), o.width());
        for (int i = 0; i < c.height(); i++)
        {
            for (int j = 0; j < c.width(); j++)
            {
                int sum = 0;
                for (int k = 0; k < width(); k++)
                {
                    sum = (sum + mult((*this)[i][k], o[k][j])) % MOD;
                }
                c[i][j] = sum;
            }
        }
        return c;
    }

    matrix pow(ll p)
    {
        matrix acc(height(), width()), res = *this;
        for (int i = 0; i < width(); i++)
        {
            acc[i][i] = 1;
        }
        while (p)
        {
            if (p & 1) acc = acc * res;
            res = res * res;
            p >>= 1;
        }

        return acc;
    }
};

int mapping(char c)
{
    if (c >= 'a' and c <= 'z') return c - 'a';
    else return c - 'A' + 26;
}

int main()
{
    ll n; int m, k;
    cin>>n>>m>>k;

    matrix state(m, m, 1), ones(m, 1, 1);
    for (int i = 0; i < k; i++)
    {
        char a, b;
        cin>>a>>b;
        state[mapping(a)][mapping(b)] = 0;
    }
    state = state.pow(n - 1);
    matrix res = state * ones;

    int sol = 0;
    for (int i = 0; i < m; i++)
    {
        sol = (res[i][0] + sol) % MOD;
    }
    cout<<sol<<'\n';

    return 0;
}

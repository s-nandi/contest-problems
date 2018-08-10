// matrix exponentiation (fibonacci)
// https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&category=704&page=show_problem&problem=5383
// 2015 Greater NY Regional

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MOD = 1000000000;

typedef int matT;
typedef long long matLT;
struct matrix : vector<vector<matT>>
{
    matrix(int h, int w, matT v = 0){resize(h, vector<matT>(w, v));}
    int height() const {return (*this).size();}
    int width() const {return (*this)[0].size();}

    int mult(matT a, matT b)
    {
        return (matLT) a * b % MOD;
    }

    matrix operator * (const matrix &o)
    {
        matrix c(height(), o.width());
        for (int i = 0; i < c.height(); i++)
        {
            for (int j = 0; j < c.width(); j++)
            {
                matT sum = 0;
                for (int k = 0; k < width(); k++)
                    sum = (sum + mult((*this)[i][k], o[k][j])) % MOD;
                c[i][j] = sum;
            }
        }
        return c;
    }

    matrix operator ^ (ll p)
    {
        matrix acc(height(), width()), res = *this;
        for (int i = 0; i < width(); i++) acc[i][i] = 1;
        for (; p; p >>= 1)
        {
            if (p & 1) acc = acc * res;
            res = res * res;
        }
        return acc;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin>>T;

    matrix base(2, 1);
    base[0][0] = 1;

    matrix fib(2, 2, 1);
    fib[1][1] = 0;
    while (T--)
    {
        int k; ll n;
        cin>>k>>n;
        --n;

        matrix res = (fib ^ n) * base;
        cout<<k<<" "<<res[0][0]<<'\n';
    }

    return 0;
}

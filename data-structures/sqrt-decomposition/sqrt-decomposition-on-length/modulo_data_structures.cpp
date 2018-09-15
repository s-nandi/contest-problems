// sqrt decomposition on length (updating elements congruent to some modulo, process large and small modulos differently)
// https://open.kattis.com/problems/modulodatastructures
// 2018 Singapore Preliminary

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

typedef long long ll;

const int BLOCK = 1000;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin>>n>>q;

    vector <ll> arr(n + 1);

    ll lazy[BLOCK][BLOCK];
    memset(lazy, 0, sizeof(lazy));

    for (int i = 0; i < q; i++)
    {
        int type;
        cin>>type;
        if (type == 1)
        {
            int a, b, v;
            cin>>a>>b>>v;

            if (b < BLOCK)
            {
                lazy[a][b] += v;
            }
            else
            {
                for (int it = a; it <= n; it += b)
                {
                    arr[it] += v;
                }
            }
        }
        else
        {
            int p;
            cin>>p;

            int res = arr[p];
            for (int m = 1; m < BLOCK; m++)
            {
                res += lazy[p % m][m];
            }
            cout<<res<<'\n';
        }
    }
}

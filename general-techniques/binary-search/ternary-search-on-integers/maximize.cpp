//ternary search (integers), prefix sums
//http://codeforces.com/contest/939/problem/E

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

#define ll long long

vector <ll> ps, elem;

double func(int i, int j)
{
    return double(ps[i] + elem[j]) / (i + 2);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    cin>>q;

    ps.resize(q), elem.resize(q);

    int nn = 0;
    double maxDiff = 0.0;

    for (int i = 0; i < q; i++)
    {
        int type;
        cin>>type;

        if (type == 1)
        {
            int x;
            cin>>x;

            elem[nn] = x;
            ps[nn] = nn > 0 ? ps[nn - 1] + x : x;
            nn++;

            if (nn == 1) continue;

            int l = 0;
            int r = nn - 2;

            while (l < r)
            {
                int m = (l + r) / 2;

                bool gr = m < nn - 2 ? func(m, nn - 1) > func(m + 1, nn - 1) : false;

                if (gr)
                {
                    l = m + 1;
                }
                else
                {
                    r = m;
                }
            }

            maxDiff = double(x) - func(l, nn - 1);
        }
        else
        {
            cout<<fixed<<setprecision(11)<<maxDiff<<'\n';
        }
    }

    return 0;
}

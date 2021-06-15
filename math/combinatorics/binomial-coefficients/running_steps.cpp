// combinatorics, precompute choose function (pascals identity)
// https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&category=704&page=show_problem&problem=5382
// 2015 Greater NY Regional

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXT = 34;

vector <vector<ll>> pascal;
ll choose(int i, int j)
{
    return pascal[i][min(j, i - j)];
}

void precomputePascal(int n)
{
    pascal.resize(n + 1, vector <ll>(n / 2 + 1));
    pascal[0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        pascal[i][0] = 1;
        for (int j = 1; j <= i / 2; j++)
        {
            pascal[i][j] = choose(i - 1, j - 1) + choose(i - 1, j);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    precomputePascal(MAXT);

    int T;
    cin>>T;
    while(T--)
    {
        int k, n;
        cin>>k>>n;

        ll sol = 0;
        for (int two = 0; 2 * two <= n; two++)
        {
            int one = n - 2 * two;

            if (one & 1 or two & 1) continue;
            if (one > two) continue;

            int eachLeg = choose(one / 2 + two / 2, one / 2);
            sol += (ll) eachLeg * eachLeg;
        }
        cout<<k<<" "<<sol<<'\n';
    }

    return 0;
}

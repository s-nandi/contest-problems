//greedy (cheaper for one step -> cheaper globally)
//https://codeforces.com/contest/998/problem/C

#include <iostream>

using namespace std;

typedef long long ll;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll x, y;
    cin>>n>>x>>y;

    string s;
    cin>>s;

    int r = 0;
    char prev = '1';
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] != prev)
        {
            prev = s[i];
            if (s[i] == '0')
            {
                r++;
            }
        }
    }

    ll cost1 = (r - 1) * x + y;
    ll cost2 = r * y;

    ll bestCost = max(0LL, min(cost1, cost2));

    cout<<bestCost<<'\n';

    return 0;
}

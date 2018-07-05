//adding gaps in array, math
//https://csacademy.com/contest/round-83/task/smallest-missing-numbers/statement/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

ll sum(ll a, ll len)
{
    return len * a + (len - 1) * len / 2;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin>>n>>m;

    vector <int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin>>a[i];
    }
    a.push_back(0);
    sort(a.begin(), a.end());

    ll sol = 0;
    int rem = m;
    for (int i = 1; i < a.size(); i++)
    {
        int add = min(a[i] - a[i - 1] - 1, rem);
        sol += sum(a[i - 1] + 1, add);
        rem -= add;
    }
    if (rem > 0) sol += sum(a.back() + 1, rem);

    cout<<sol<<'\n';

    return 0;
}

//prefix sums on intervals, binary search
//https://www.e-olymp.com/en/problems/5071

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin>>n;
    cin>>m;

    vector <int> prefixSum(n);

    for (int i = 0; i < m; i++)
    {
        int l, r;
        cin>>l>>r;
        --l; --r;
        prefixSum[l]++;
        if (r + 1 < n)
            prefixSum[r + 1]--;
    }

    vector <int> coins(n);
    coins[0] = prefixSum[0];

    for (int i = 1; i < n; i++)
    {
        coins[i] = coins[i - 1] + prefixSum[i];
    }
    sort(coins.begin(), coins.end());

    int q;
    cin>>q;

    for (int i = 0; i < q; i++)
    {
        int x;
        cin>>x;
        cout<<coins.size() - (lower_bound(coins.begin(), coins.end(), x) - coins.begin())<<'\n';
    }

    return 0;
}

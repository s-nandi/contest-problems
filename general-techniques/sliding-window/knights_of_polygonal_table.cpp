//sliding window
//http://codeforces.com/contest/994/problem/B

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <tuple>

using namespace std;

typedef long long ll;

struct knight
{
    int power, coin, index;
    bool operator < (const knight &o) const
    {
        return tie(power, coin, index) < tie(o.power, o.coin, o.index);
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin>>n>>k;

    vector <knight> knights(n);
    for (int i = 0; i < n; i++)
    {
        cin>>knights[i].power;
    }
    for (int i = 0; i < n; i++)
    {
        cin>>knights[i].coin;
        knights[i].index = i;
    }
    sort(knights.begin(), knights.end());

    ll feasible[n];
    multiset <int> window;
    ll windowSum = 0;
    for (int i = 0; i < n; i++)
    {
        feasible[knights[i].index] = windowSum + knights[i].coin;
        if (k == 0) continue;

        if (window.size() >= k)
        {
            auto it = window.begin();
            int least = *it;
            if (knights[i].coin > least)
            {
                window.erase(it);
                windowSum -= least;
                window.insert(knights[i].coin);
                windowSum += knights[i].coin;
            }
        }
        else
        {
            window.insert(knights[i].coin);
            windowSum += knights[i].coin;
        }
    }

    for (int i = 0; i < n; i++)
    {
        cout << feasible[i] << " ";
    }
    cout<<'\n';

    return 0;
}

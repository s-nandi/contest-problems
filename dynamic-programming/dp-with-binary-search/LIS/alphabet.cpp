// longest increasing subsequence
// http://codeforces.com/gym/101201
// 2016 Pacific NW Regional

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T, class Op> int LIS(vector <T> &v, Op cmp)
{
    vector <T> dp;
    for (auto elem: v)
    {
        int pos = lower_bound(dp.begin(), dp.end(), elem, cmp) - dp.begin();
        if (pos == dp.size())
            dp.push_back(elem);
        else
            dp[pos] = elem;
    }
    return dp.size();
}

int main()
{
    string s;
    cin>>s;

    vector <char> v(s.begin(), s.end());

    auto cmp = [](char a, char b)
    {
        return a < b;
    };

    cout << 26 - LIS(v, cmp) << '\n';
}

// greedy, finding longest strictly zig-zagging subsequence (greedily choose last element from increasing/decreasing segment => answer is # of inc/decreasing changes)
// https://open.kattis.com/problems/zigzag2
// 2016 Southeast NA Regional

#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    vector <int> a(n);
    for (int &i: a)
        cin >> i;

    int sol = 0, type = -1;
    for (int i = 0; i + 1 < a.size(); i++)
    {
        if (a[i] == a[i + 1])
            continue;
        if ((a[i] < a[i + 1]) != type)
            sol++;
        type = (a[i] < a[i + 1]);
    }
    cout << sol + 1 << '\n';
}

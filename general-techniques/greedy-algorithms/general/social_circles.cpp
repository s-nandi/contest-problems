// greedy (merging circular sets w/ minimum cost)
// http://codeforces.com/contest/1060/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector <int> left(n), right(n);
    for (int i = 0; i < n; i++)
    {
        cin >> left[i] >> right[i];
    }
    sort(left.begin(), left.end(), greater<int>());
    sort(right.begin(), right.end(), greater<int>());

    ll sol = 0;
    for (int i = 0; i < n; i++)
    {
        sol += max(left[i], right[i]);
    }
    cout << sol + n << '\n';

    return 0;
}

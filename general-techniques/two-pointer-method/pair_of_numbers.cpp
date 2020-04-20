//invariant maintenance (finding extremes for both directions), finding longest subarray that contains its gcd
//http://codeforces.com/contest/359/problem/D

#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin>>n;

    vector <int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin>>a[i];
    }

    int curr;
    vector <int> lm(n, -1), rm(n, -1);
    for (int i = 0, j = 0; i < n; ++j, i = j)
    {
        curr = a[i];
        while (j + 1 < n)
        {
            if (a[j + 1] >= curr and a[j + 1] % curr == 0) ++j;
            else if (a[j + 1] < curr and curr % a[j + 1] == 0) curr = a[++j];
            else break;
        }
        for (int k = i; k <= j; k++) rm[k] = j;
    }
    for (int i = n - 1, j = n - 1; i >= 0; j--, i = j)
    {
        curr = a[i];
        while (j - 1 >= 0)
        {
            if (a[j - 1] >= curr and a[j - 1] % curr == 0) --j;
            else if (a[j - 1] < curr and curr % a[j - 1] == 0) curr = a[--j];
            else break;
        }
        for (int k = i; k >= j; k--) lm[k] = j;
    }

    int longest = 0;
    set <int> vals;
    for (int i = 0; i < n; i++)
    {
        int possible = rm[i] - lm[i];
        if (possible > longest) longest = possible, vals = {lm[i]};
        else if (possible == longest) vals.insert(lm[i]);
    }

    cout<<vals.size()<<" "<<longest<<'\n';
    for (int i: vals) cout<<i + 1<<" ";
    cout<<'\n';

    return 0;
}

// gcd, detect if number is gcd of some contiguous subarray
// https://open.kattis.com/problems/gcds
// 2014 NAIPC

#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

const int MAXN = 100;

int gcd(int a, int b)
{
    while (b != 0)
        tie(a, b) = make_tuple(b, a % b);
    return a;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector <int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin>>a[i];
    }
    int sol = 0;
    for (int g = 0; g <= MAXN; g++)
    {
        bool feasible = false;
        int curr = a[0];
        for (int i = 0; i < n; i++)
        {
            if (g != 0 and curr % g != 0)
                curr = a[i];
            else
                curr = gcd(curr, a[i]);
            if (curr == g)
                feasible = true;
        }
        sol += feasible;
    }
    cout<<sol<<'\n';
}

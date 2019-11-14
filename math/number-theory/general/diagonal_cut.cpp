// number theory (gcd), # of evenly split blocks by line segment on a integer grid 
// https://open.kattis.com/problems/diagonalcut
// 2019 North American Qualifier

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long a, b;
    cin >> a >> b;
    if (a > b)
        swap(a, b);

    auto g = gcd(a, b);
    b /= g, a /= g;
    if ((b - a) % 2 != 0) {
        cout << 0 << '\n';
    }
    else {
        cout << g << '\n';
    }
}

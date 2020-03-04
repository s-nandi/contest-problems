// greedy, two pointers-ish kinda not really
// https://codeforces.com/contest/1305/problem/B

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    vi rems;
    for (int l = 0, r = sz(s) - 1; l < r; l++, r--) {
      while (l + 1 < sz(s) and s[l] != '(')
        l++;
      while (r - 1 >= 0 and s[r] != ')')
        r--;
      if (l < r) {
        rems.PB(l);
        rems.PB(r);
      } else break;
    }
    if (empty(rems)) cout << 0 << '\n';
    else {
      cout << 1 << '\n' << sz(rems) << '\n';
      sort(all(rems));
      trav(i, rems) cout << i + 1 << " ";
      cout << '\n';
    }
}

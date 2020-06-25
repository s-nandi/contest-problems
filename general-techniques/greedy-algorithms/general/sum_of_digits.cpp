// constructive, breaking up candidate solution into parts (prefix, repeating 9's, last digit), greedy (sh. number with target digit sum)
// https://codeforces.com/contest/1373/problem/E

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using ii = pair<int, int>;
using vi = vector<int>;

#define rep(i, a, b) for(auto i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

const int MAXN = 150;
const int MAXK = 9;

int to_digit(char c){return c - '0';}
char to_char(int i){return i + '0';}

void minn(string& res, const string& s) {
  if (empty(res)) res = s;
  else {
    if (sz(s) < sz(res)) res = s;
    else if (sz(s) == sz(res)) res = min(res, s);
  }
}

string make_sum(int target_sum) {
  string res{};
  for (int i = 0; target_sum; i++) {
    auto max_value = (i == 0) ? 8 : 9;
    if (target_sum >= max_value) res += to_char(max_value);
    else res += to_char(target_sum);
    target_sum -= to_digit(res.back());
  }
  return string(rbegin(res), rend(res));
}

int units_digit_sum(int lo, int hi){
  int res = 0;
  rep(i, lo, hi + 1) res += i % 10;
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while(T--) {
    int n, k;
    cin >> n >> k;
    int cnt = k + 1;

    string sol{};
    rep(trailing_nines, 0, MAXN + 1) {
      rep(lastdigit, 0, 10) {
        bool wrap = lastdigit + cnt - 1 >= 10;
        int before_wrap = !wrap ? cnt : 9 - lastdigit + 1;
        int after_wrap = !wrap ? 0 : (lastdigit + cnt - 1) - 9;
        
        int lastdigit_contrib = units_digit_sum(lastdigit, lastdigit + cnt - 1);
        int nine_contrib = 9 * trailing_nines * before_wrap;
        int carry_contrib = after_wrap;

        int rem = n - lastdigit_contrib - nine_contrib - carry_contrib;
        if (rem < 0) continue;
        if (rem % cnt != 0) continue;
        int prefix_contrib = rem / cnt;

        string front = make_sum(prefix_contrib); // generated string can't end with a 9, since
                                                 // we already fixed the # of trailing 9's 
        string nines = string(trailing_nines, '9');
        string possible = front + nines + to_string(lastdigit);
        minn(sol, possible);
      }
    }
    cout << (empty(sol) ? "-1" : sol) << '\n';
  }
}

// constructive (proofy), game theory (parity), cannot pair off stones if there is a majority element => if majority exists, firstplayer wins, otherwise check parity (ie. pair stones)
// https://codeforces.com/contest/1396/problem/B

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using vi = vector<int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

const int INF = 1031231234;
bool heuristic(const vi& a) {
  ll sum = 0;
  ll mx = -INF;
  trav(i, a) {
    sum += i;
    mx = max<ll>(mx, i);
  }
  sum -= mx;
  if (mx > sum) return true;
  else return (sum + mx) & 1;
}

const string firstplayer = "T";
const string secondplayer = "HL";

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vi a(n);
    trav(i, a) cin >> i;
    auto res = heuristic(a);
    cout << (res ? firstplayer : secondplayer)<< '\n';
  }
}

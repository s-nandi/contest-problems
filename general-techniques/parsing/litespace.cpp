// ad-hoc (implementation, parsing)
// https://open.kattis.com/problems/litespace
// 2020 Mount Allison Showdown (MAPS)

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define sz(x) (int)(x).size()

ll parsenum(const string& s, int& it) {
  int sgn = 1;
  if (s[it++] == 'T') sgn = -1;
  ll acc = 0LL;
  while(s[it] != 'N') {
    assert(it < sz(s));
    acc *= 2;
    acc += (s[it] == 'T');
    it++;
  }
  it++;
  return sgn * acc;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  cin >> s;
  int i = 0;
  stack<ll> st;
  while (i < sz(s)) {
    if (i + 1 < sz(s) and s[i] == 'S' and s[i + 1] == 'S') {
      i += 2;
      auto v = parsenum(s, i);
      st.push(v);
    } else if(i + 2 < sz(s) and s.substr(i, 3) == "SNS") {
      if (st.empty()) {
        cout << "Invalid copy operation" << '\n';
      } else {
        st.push(st.top());
      }
      i += 3;
    } else if (i + 2 < sz(s) and s.substr(i, 3) == "SNT") {
      if (sz(st) < 2) {
        cout << "Invalid swap operation" << '\n';
      } else {
        auto a = st.top(); st.pop();
        auto b = st.top(); st.pop();
        st.push(a);
        st.push(b);
      }
      i += 3;
    } else if (i + 2 < sz(s) and s.substr(i, 3) == "SNN") {
      if (sz(st) == 0) {
        cout << "Invalid remove operation" << '\n';
      } else {
        st.pop();
      }
      i += 3;
    } else if (i + 3 < sz(s) and s.substr(i, 4) == "TSSS") {
      if (sz(st) < 2) cout << "Invalid addition operation" << '\n';
      else {
        auto a = st.top(); st.pop();
        auto b = st.top(); st.pop();
        st.push(a + b);
      }
      i += 4;
    } else if (i + 3 < sz(s) and s.substr(i, 4) == "TSST") {
      if (sz(st) < 2) cout << "Invalid subtraction operation" << '\n';
      else {
        auto a = st.top(); st.pop();
        auto b = st.top(); st.pop();
        st.push(b - a);
      }
      i += 4;
    }  else if (i + 3 < sz(s) and s.substr(i, 4) == "TSSN") {
      if (sz(st) < 2) cout << "Invalid multiplication operation" << '\n';
      else {
        auto a = st.top(); st.pop();
        auto b = st.top(); st.pop();
        st.push(b * a);
      }
      i += 4;
    }  else if (i + 3 < sz(s) and s.substr(i, 4) == "TSTS") {
      if (sz(st) < 2) cout << "Invalid division operation" << '\n';
      else {
        auto a = st.top(); st.pop();
        if (a == 0) {
          cout << "Division by zero" << '\n';
          st.push(a);
        } else {
          auto b = st.top(); st.pop();
          st.push(b / a);
        }
      }
      i += 4;
    }  else if (i + 3 < sz(s) and s.substr(i, 4) == "TNST") {
      if (sz(st) < 1) cout << "Invalid print operation" << '\n';
      else {
        auto a = st.top(); st.pop();
        cout << a << '\n';
      }
      i += 4;
    } 
  }
}

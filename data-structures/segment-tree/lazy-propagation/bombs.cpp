// lazy segtree (max query, sum update), amortized analysis (monotone dec. solution)
// https://codeforces.com/contest/1326/problem/E

#include <bits/stdc++.h>
using namespace std;
 
using vi = vector<int>;
 
#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define sz(a) (int)size(a)
 
const int INF = 1231231234;
 
struct ST {
    int s;
    vi v, t;
    vi l, r;
    ST(const auto& vec) : s{sz(vec)}, v(2*s), t(2*s), l(2*s,-1), r(2*s,-1) {
        build(0, 0, s - 1, vec);
    }
    void build(int i, int lb, int rb, const auto& vec) {
        if (lb == rb) v[i] = vec[lb];
        else {
            int mb = (lb + rb) / 2;
            l[i] = i + 1; r[i] = i + 2 * (mb - lb + 1);
            build(l[i], lb, mb, vec);
            build(r[i], mb + 1, rb, vec);
            v[i] = max(v[l[i]], v[r[i]]);
        }
    }
    void prop(int i) {
        if (t[i]) {
            v[l[i]] += t[i]; t[l[i]] += t[i];
            v[r[i]] += t[i]; t[r[i]] += t[i];
            t[i] = 0;
        }
    }
    void modify(int ql, int qr, auto u) {modify(0, 0, s - 1, ql, qr, u);}
    void modify(int i, int lb, int rb, int ql, int qr, auto u) {
        if (rb < ql || qr < lb) return;
        else if (ql <= lb && rb <= qr) {v[i] += u; t[i] += u;} 
        else {
            prop(i);
            int mb = (lb + rb) / 2;
            modify(l[i], lb, mb, ql, qr, u);
            modify(r[i], mb + 1, rb, ql, qr, u);
            v[i] = max(v[l[i]], v[r[i]]);
        }
    }
    
    auto query(int ql, int qr) { return query(0, 0, s - 1, ql, qr); }
    int query(int i, int lb, int rb, int ql, int qr) {
        if (rb < ql || qr < lb) return -INF;
        else if (ql <= lb && rb <= qr) return v[i];
        else {
            int mb = (lb + rb) / 2;
            return max(query(l[i], lb, mb, ql, qr), query(r[i], mb + 1, rb, ql, qr));
        }
    }
};
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n;
    cin >> n;
    vi p(n + 1), ip(n + 1), q(n);
    rep(i, 1, n + 1) {
        cin >> p[i];
        ip[p[i]] = i;
    }
    rep(i, 0, n) {
        cin >> q[i];
    }
    int curr = n + 1;
    ST st{vi(n + 1)};
    vi sols(n);
    rep(i, 0, n) {
        while(st.query(1, n) <= 0)
            st.modify(1, ip[--curr], 1);
        st.modify(1, q[i], -1);
        sols[i] = curr;
    }
    trav(i, sols) cout << i << " "; cout << '\n';
}

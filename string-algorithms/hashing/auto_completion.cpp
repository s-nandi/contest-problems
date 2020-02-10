// hashing, storing table of prefix hash to all string with that prefix
// https://open.kattis.com/problems/autocompletion
// 2018 ProgNova

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a: x)
#define all(a) begin(a), end(a)
#define sz(a) (int)size(a)

const auto MOD = vector{1'000'000'007, 1'000'000'009};
const auto alpha = 523;

struct hasher {
    ll vs{0};
    int t;
    hasher(int t = 0) : t{t} {}
    int mapping(auto c){return c - 'a' + 1;}
    void push(auto c) {
        vs = (vs * alpha % MOD[t] + mapping(c)) % MOD[t];
    }
    operator ll() const {return vs;}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<string> a(n);
    trav(s, a) cin >> s;
    sort(all(a));

    map<pair<int, int>, vector<int>> index_per_hash;
    vector<pair<int, int>> word_hash(n);
    rep(i, 0, n) {
        auto h1 = hasher(0), h2 = hasher(1);
        auto& s = a[i];
        rep(j, 0, sz(s)) {
            h1.push(s[j]);
            h2.push(s[j]);
            if (j < sz(s) - 1) {
                index_per_hash[{h1, h2}].push_back(i);
            }
            else {
                word_hash[i] = {h1, h2};
            }
        }
    }

    int q;
    cin >> q;
    rep(i, 0, q) {
        string s;
        cin >> s;
        string res = "";
        int wsz = 0;
        auto h1 = hasher(0), h2 = hasher(1);
        for(auto j = 0; j < sz(s); j++) {
            if (s[j] == '#') {
                auto cnt = 1;
                while (j + 1 < sz(s) and s[j + 1] == '#') {
                    j++;
                    cnt++;
                }
                
                if (index_per_hash.count({h1, h2})) {
                    auto& indices = index_per_hash[{h1, h2}];
	  
                    auto ind = indices[(cnt - 1) % sz(indices)];
                    rep(k, wsz, sz(a[ind])) {
                        res += a[ind][k];
                    }
                    tie(h1.vs, h2.vs) = word_hash[ind];
                    wsz = sz(a[ind]);
                }
            } else {
                h1.push(s[j]);
                h2.push(s[j]);
                res += s[j];
                wsz++;
            }
        }
        cout << res << '\n';
    }
}

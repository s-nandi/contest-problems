// dp with monotone queue, binary search on answer
// https://codeforces.com/gym/100801/attachments (problem J)
// 2015 NEERC Northern Subregional

#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;
 
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)x.size()
 
template <typename T, class Operation>
struct monotoneQueue
{
    int sz = 0;
    deque <T> elements;
    Operation op;
 
    monotoneQueue(Operation o) : op(o) {}
 
    void insert(T elem)
    {
        while (!elements.empty() and op(elem, elements.back()))
            elements.pop_back();
        elements.push_back(elem), sz++;
    }
 
    void erase(T elem)
    {
        if(elements.front() == elem)
            elements.pop_front();
        sz--;
    }
 
    T query() const {return elements.front();}
};
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    freopen("journey.in", "r", stdin);
    freopen("journey.out", "w", stdout);
 
    int n, t;
    cin >> n >> t;
    t -= (n - 1);
    
    vector<int> p(n);
    rep(i, 1, n) cin >> p[i];
    vector<int> d(n);
    rep(i, 2, n) cin >> d[i];
 
    auto cmp = less<>{};
    auto feas = [&](ll range) {
                    auto q = monotoneQueue<ll, decltype(cmp)>(cmp);
                    vector<ll> dp(n);
                    q.insert(0);
                    rep(i, 2, n) {
                        auto possible = q.query();
                        dp[i] = d[i] + q.query();
                        
                        q.insert(dp[i]);                        
                        if (i > range)
                            q.erase(dp[i - range]); 
                    }
                    return q.query();
                };
 
    int lo = 1, hi = n - 1;
    while (lo < hi) {
        auto mid = (lo + hi) / 2;
        if (feas(mid) <= t) hi = mid;
        else lo = mid + 1;
    }
    auto best = *min_element(next(begin(p), lo), end(p));
    cout << best << '\n';
}

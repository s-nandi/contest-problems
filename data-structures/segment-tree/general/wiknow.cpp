// segment tree, line sweep, fixing a segment and finding the active segment with smallest r
// https://open.kattis.com/problems/wiknow
// 2018 Singapore Regional

#include <bits/stdc++.h>
using namespace std;

constexpr auto MAXN = 400'000 + 5;
constexpr auto INF = 1231231234;

struct event {
    int l, r, pos, value;

    auto is_add() const { return l == pos; }
    auto operator<(const auto& o) const { return tuple(pos, is_add()) < tuple(o.pos, o.is_add()); }
};

template <typename T, typename Combinator>
struct segment_tree {
    vector<T> elems;
    Combinator combine;
    T identity;
    int sz;

    segment_tree(const auto& container, Combinator combine, T identity)
        : elems(2 * container.size()), combine(combine), identity{identity}, sz(container.size()) {
        transform(container.begin(), container.end(), elems.begin() + sz,
                  [](auto elem) { return T(elem); });
        for (int i = sz - 1; i >= 1; i--) {
            elems[i] = combine(elems[i << 1], elems[i << 1 | 1]);
        }
    }

    auto modify(int i, auto update) {
        elems[i] = update(elems[i += sz]);
        for (i >>= 1; i >= 1; i >>= 1) {
            elems[i] = combine(elems[i << 1], elems[i << 1 | 1]);
        }
    }

    auto query(int l, int r) {
        T lacc = identity, racc = identity;
        for (l += sz, r += sz; l <= r; ++l >>= 1, --r >>= 1) {
            if (l & 1) lacc = combine(lacc, elems[l]);
            if (!(r & 1)) racc = combine(elems[r], racc);
        }
        return combine(lacc, racc);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    auto nums = vector<int>(n);
    for (auto& num : nums) {
        cin >> num;
    }

    auto occurences = vector(MAXN, vector<int>{});
    for (int i = 0; i < n; i++) {
        occurences[nums[i]].push_back(i);
    }

    auto events = vector<event>{};
    for (int v = 0; v < MAXN; v++) {
        for (int i = 0; i + 1 < occurences[v].size(); i++) {
            auto l = occurences[v][i];
            auto r = occurences[v][i + 1];
            events.push_back({l, r, l, v});
            events.push_back({l, r, r, v});
        }
    }
    sort(begin(events), end(events));

    auto minner = [](auto a, auto b) { return min(a, b); };
    auto assign = [](auto val) { return [val](auto elem) { return val; }; };
    auto st = segment_tree(vector<int>(MAXN, INF), minner, INF);

    auto sol = pair(INF, INF);
    for (auto e : events) {
        auto smallest_before = st.query(0, e.r - 1);
        if (smallest_before != INF) {
            auto possible = pair(smallest_before, e.value);
            sol = min(sol, possible);
        }
        if (e.is_add()) {
            st.modify(e.r, assign(e.value));
        } else {
            st.modify(e.r, assign(INF));
        }
    }
    auto [A, B] = sol;
    if (A == INF) {
        cout << -1 << '\n';
    } else {
        cout << A << " " << B << '\n';
    }
}

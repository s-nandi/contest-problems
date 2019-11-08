// Area of union of rectangles (area covered by odd # of rectangles), lazy seg tree (flipping range)
// https://codeforces.com/gym/259143 (F)
// 2018 Pacific Northwest Regional

#include <bits/stdc++.h>
using namespace std;

struct node {
    int sum = 0, active = 0;

    void init(int i) { sum = i; }
    node combine(const node& a, const node& b) {
        sum = a.sum + b.sum;
        active = a.active + b.active;
        return *this;
    }
} acc;

struct segmentTree {
    node n;
    int lb, rb;
    bool lazy, isLazy;
    segmentTree *l, *r;

    segmentTree() {}
    segmentTree(const auto& v) : segmentTree(0, v.size() - 1, v) {}
    segmentTree(int ql, int qr, const auto& v) : lb(ql), rb(qr) {
        resetLazy();
        if (lb == rb) {
            n.init(v[lb]);
            return;
        }
        int m = (lb + rb) >> 1;
        l = new segmentTree(lb, m, v), r = new segmentTree(m + 1, rb, v);
        n.combine(l->n, r->n);
    }

    auto query(int l, int r) { return queryn(l, r).active; }
    node queryn(int ql, int qr) {
        pushLazy();
        if (lb > qr or rb < ql) return node();
        if (lb >= ql and rb <= qr) return n;
        return acc.combine(l->queryn(ql, qr), r->queryn(ql, qr));
    }

    void modify(int ql, int qr, auto v) {
        pushLazy();
        if (lb > qr or rb < ql) return;
        if (lb >= ql and rb <= qr) {
            setLazy(v), pushLazy();
            return;
        }
        l->modify(ql, qr, v), r->modify(ql, qr, v);
        n.combine(l->n, r->n);
    }

    void pushLazy() {
        if (!isLazy) return;
        if (lazy) n.active = (n.sum - n.active);
        if (lb != rb) l->setLazy(lazy), r->setLazy(lazy);
        resetLazy();
    }

    void setLazy(auto v) { lazy ^= v, isLazy = true; }
    void resetLazy() { lazy = false, isLazy = false; }
};

template <typename T>
struct compressor {
    vector<T> s;
    compressor(const vector<T>& vals) : s{vals} {
        sort(begin(s), end(s));
        s.erase(unique(begin(s), end(s)), end(s));
    }
    auto kth_element(auto k) { return s[k]; }
    auto index_of(auto v) { return lower_bound(begin(s), end(s), v) - begin(s); }
};

struct event {
    int x, y1, y2;
    bool add;

    bool operator<(const auto& o) const {
        return tie(x, add, y1, y2) < tie(o.x, o.add, o.y1, o.y2);
    }
};

using rectangle = array<int, 4>;  // x1 y1 x2 y2
auto rectangle_union_area(const auto& rs) {
    vector<event> events;
    vector<int> ys, xs;
    for (const auto& [x1, y1, x2, y2] : rs) {
        ys.insert(end(ys), {y1, y2});
        xs.insert(end(xs), {x1, x2});
        events.push_back({x1, y1, y2, true});
        events.push_back({x2, y1, y2, false});
    }
    auto compressed = compressor(ys);
    sort(begin(events), end(events));

    vector<int> deltas(compressed.s.size() - 1);
    for (int i = 0; i < deltas.size(); i++) {
        deltas[i] = compressed.kth_element(i + 1) - compressed.kth_element(i);
    }

    auto area = 0LL;
    segmentTree st(deltas);
    auto prev_x = events[0].x;
    for (int it = 0; it < events.size(); it++) {
        if (events[it].x != prev_x) {
            auto dy = st.query(0, deltas.size() - 1);
            auto dx = events[it].x - prev_x;
            area += 1LL * dy * dx;
        }
        prev_x = events[it].x;

        auto y1 = compressed.index_of(events[it].y1);
        auto y2 = compressed.index_of(events[it].y2);
        if (y1 == y2) continue;
        st.modify(y1, y2 - 1, 1);
    }
    return area;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<rectangle> rects(n);
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        rects[i] = {x1, y1, x2, y2};
    }
    auto sol = rectangle_union_area(rects);
    cout << sol << '\n';
}

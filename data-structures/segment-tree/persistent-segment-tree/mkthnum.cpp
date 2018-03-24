//persistent segment tree (offline processing), coordinate compression, finding kth element in (l, r) range
//http://www.spoj.com/problems/MKTHNUM/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct node
{
    int sum = 0;

    void init(int i){sum = i;}
    void modify(int v){sum += v;}
    node combine(const node &a, const node &b)
    {
        sum = a.sum + b.sum;
        return *this;
    }
} acc;

struct segmentTree
{
    node n;
    int lb, rb;
    segmentTree *l, *r;

    segmentTree(){}
    segmentTree(int s, int def = 0) : segmentTree(0, s - 1, def) {}
    segmentTree(int ql, int qr, int def) : lb(ql), rb(qr)
    {
        if (lb == rb){n.init(def); return;}
        int m = (lb + rb) >> 1;
        l = new segmentTree(lb, m, def), r = new segmentTree(m + 1, rb, def);
        n.combine(l -> n, r -> n);
    }

    int query(int l, int r){return queryn(l, r).sum;} /*PS*/
    node queryn(int ql, int qr)
    {
        if (lb > qr or rb < ql) return node();
        if (lb >= ql and rb <= qr) return n;
        return acc.combine(l -> queryn(ql, qr), r -> queryn(ql, qr));
    }

    segmentTree* modify(int qp, int v)
    {
        if (lb > qp or rb < qp) return this;
        if (lb == rb)
        {
            segmentTree* st = new segmentTree(*this);
            st -> n.modify(v);
            return st;
        }
        segmentTree* st = new segmentTree(*this);
        st -> l = l -> modify(qp, v), st -> r = r -> modify(qp, v);
        st -> n.combine(st -> l -> n, st -> r -> n);
        return st;
    }
};

typedef vector<segmentTree> segmentTreePs;
void modify(segmentTreePs &st, int p, int v)
{
    st.push_back(*st.back().modify(p, v));
}

vector <pair<int, int>> compressed;
int compression(int i)
{
    pair <int, int> obj = {i, -1};
    return lower_bound(compressed.begin(), compressed.end(), obj) - compressed.begin();
}

int getKthElement(segmentTreePs &st, int lb, int rb, int k)
{
    int l = 0, r = st.size();
    while (l < r)
    {
        int m = (l + r) / 2;

        if (st[m].query(lb, rb) <= k) l = m + 1;
        else r = m;
    }
    return compressed[l - 1].first;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin>>n>>m;

    vector <int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin>>a[i];
        compressed.push_back({a[i], i});
    }
    sort(compressed.begin(), compressed.end());

    segmentTreePs st = {segmentTree(n)};
    for (int i = 0; i < n; i++)
    {
        modify(st, compressed[i].second, 1);
    }

    for (int i = 0; i < m; i++)
    {
        int l, r, k;
        cin>>l>>r>>k;

        cout<<getKthElement(st, --l, --r, --k)<<'\n';
    }

    return 0;
}

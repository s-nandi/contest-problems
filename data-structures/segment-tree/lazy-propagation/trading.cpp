//segment tree (lazy propagation), arithmetic progression updates, max query
//https://www.e-olymp.com/en/problems/7482

#include <iostream>
#include <vector>

using namespace std;

#define ll long long

const ll INF = 123123123123123123;

struct node
{
    ll maxVal = -INF;

    void init(ll i){maxVal = i;}
    node combine(const node &a, const node &b)
    {
        maxVal = max(a.maxVal, b.maxVal);
        return *this;
    }
} acc;

struct segmentTree
{
    node n;
    int lb, rb;
    ll a0, delta; bool isLazy;
    segmentTree *l, *r;

    segmentTree(){}
    segmentTree(int s, int def = 0) : segmentTree(0, s - 1, def) {}
    segmentTree(int ql, int qr, int def) : lb(ql), rb(qr)
    {
        resetLazy();
        if (lb == rb){n.init(def); return;}
        int m = (lb + rb) >> 1;
        l = new segmentTree(lb, m, def), r = new segmentTree(m + 1, rb, def);
        n.combine(l -> n, r -> n);
    }

    int query(int l, int r){return queryn(l, r).maxVal;}
    node queryn(int ql, int qr)
    {
        pushLazy();
        if (lb > qr or rb < ql) return node();
        if (lb >= ql and rb <= qr) return n;
        return acc.combine(l -> queryn(ql, qr), r -> queryn(ql, qr));
    }

    void modify(int ql, int qr, ll start, ll diff)
    {
        pushLazy();
        if (lb > qr or rb < ql) return;
        if (lb >= ql and rb <= qr)
        {
            setLazy(proj(start, diff, lb - ql), diff), pushLazy();
            return;
        }
        l -> modify(ql, qr, start, diff), r -> modify(ql, qr, start, diff);
        n.combine(l -> n, r -> n);
    }

    void pushLazy()
    {
        if (!isLazy) return;
        n.maxVal = max(n.maxVal, a0 + (rb - lb) * delta);
        if (lb != rb) l -> setLazy(a0, delta), r -> setLazy(proj(a0, delta, r -> lb - lb), delta);
        resetLazy();
    }

    void setLazy(ll a, ll d)
    {
        if (proj(a, d, rb - lb) >= proj(a0, delta, rb - lb))
            a0 = a, delta = d;
        isLazy = true;
    }
    void resetLazy(){a0 = delta = 0, isLazy = false;}

    ll proj(ll a0, ll delta, int i){return a0 + delta * i;}
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin>>n>>m;

    segmentTree st(n);

    for (int i = 0; i < m; i++)
    {
        int l, r; ll x;
        cin>>l>>r>>x;

        st.modify(--l, --r, x, 1LL);
    }

    for (int i = 0; i < n; i++)
    {
        cout<<st.query(i, i)<<" ";
    }
    cout<<'\n';

    return 0;
}

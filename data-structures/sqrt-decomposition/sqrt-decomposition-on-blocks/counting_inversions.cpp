// sqrt decomposition on blocks (maintaining sorted blocks), window range queries, assignment update
// https://www.spoj.com/problems/SWAPS/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int INF = 1231231234;
const int BLOCK = 800;

struct sqrt_block
{
    vector <pair<int, int>> elements;

    void modifyPartial(int p, int v)
    {
        for (auto &elem: elements) if (elem.second == p)
            elem.first = v;
        sort(elements.begin(), elements.end());
    }

    int queryWhole(int lo, int hi)
    {
        return lower_bound(elements.begin(), elements.end(), make_pair(hi + 1, -INF)) -
               lower_bound(elements.begin(), elements.end(), make_pair(lo, -INF));
    }

    int queryPartial(int l, int r, int lo, int hi)
    {
        int res = 0;
        for (auto &elem: elements) if (l <= elem.second and elem.second <= r)
            res += (lo <= elem.first and elem.first <= hi);
        return res;
    }
};

struct block_decomposition
{
    int sz, bsz, nb;
    vector <sqrt_block> blocks;

    block_decomposition(const vector <int> &v, int BLOCK_SIZE) : sz(v.size()), bsz(BLOCK_SIZE), nb(sz / BLOCK_SIZE + 1), blocks(nb)
    {
        for (int i = 0; i < v.size(); i++)
            blocks[i / bsz].elements.push_back({v[i], i});
        for (auto &b: blocks)
            sort(b.elements.begin(), b.elements.end());
    }

    int overlap(int i, int ql, int qr)
    {
        int lb = i * bsz, rb = (i + 1) * bsz - 1;
        if (ql <= lb and qr >= rb) return 2;
        else if (ql > rb or qr < lb) return 0;
        else return 1;
    } // 2: query covers block, 1: query overlaps block, 0: no overlap

    void modify(int p, int v)
    {
        for (int i = 0; i < nb; i++) if (overlap(i, p, p) != 0)
        {
        	blocks[i].modifyPartial(p, v);
        }
    }

    int query(int ql, int qr, int lo, int hi)
    {
        int acc = 0;
        for (int i = 0; i < nb; i++)
        {
            auto o = overlap(i, ql, qr);
            if (o == 2)
                acc += blocks[i].queryWhole(lo, hi);
            else if (o == 1)
                acc += blocks[i].queryPartial(ql, qr, lo, hi);
        }
        return acc;
    }
};

int setPosition(int p, int v, vector <int> &a, block_decomposition &bd)
{
    if (a[p] == v)
        return 0;

    int n = a.size();
    ll diff = 0;
    if (p - 1 >= 0)
    {
        if (v < a[p])
            diff += bd.query(0, p - 1, v + 1, a[p]);
        else
            diff -= bd.query(0, p - 1, a[p] + 1, v);
    }
    if (p + 1 < n)
    {
        if (a[p] < v)
            diff += bd.query(p + 1, n - 1, a[p], v - 1);
        else
            diff -= bd.query(p + 1, n - 1, v, a[p] - 1);
    }
    bd.modify(p, v);
    a[p] = v;
    return diff;
}

struct fenwickTree
{
    vector <int> elements;

    fenwickTree(int s)
    {
        elements.resize(s + 1);
    }

    void modify(int i, int v)
    {
        for (i++; i < elements.size(); i += i & (-i)) elements[i] += v; /*PS*/
    }

    int query(int i)
    {
        int ans = 0;
        for (i++; i > 0; i -= i & (-i)) ans += elements[i]; /*PS*/
        return ans;
    }

    int query(int l, int r) {return query(r) - query(l - 1);}
};

vector <int> sorted;
int mapping(int i)
{
    return lower_bound(sorted.begin(), sorted.end(), i) - sorted.begin();
}

ll initialInversions(vector <int> &a, block_decomposition &bd)
{
    sorted = a;
    sort(sorted.begin(), sorted.end());

    int n = a.size();
    fenwickTree ft(n);
    ll numInversions = 0;
    for (int i = 0; i < n; i++)
    {
        int pos = mapping(a[i]);
        numInversions += ft.query(pos + 1, n - 1);
        ft.modify(pos, 1);
    }
    return numInversions;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    vector <int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    block_decomposition bd(a, BLOCK);
    ll numInversions = initialInversions(a, bd);

    int q;
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        int p, v;
        cin >> p >> v;
        --p;

        numInversions += setPosition(p, v, a, bd);
        cout << numInversions << '\n';
    }
}

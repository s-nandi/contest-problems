//fenwick tree of treaps (duplicate handling), find # of numbers between [a, b] in interval [l, r] queries, inversion count
//https://codeforces.com/contest/785/problem/E

#include <iostream>
#include <vector>
#include <tuple>
#include <random>
#include <ctime>

using namespace std;

typedef long long ll;

struct treap
{
    struct node
    {
        int key, priority, cnt;
        node *l, *r;
        int sz;

        node(int k) : priority(rand() << 16 ^ rand()), l(NULL), r(NULL), cnt(1) {init(k);}
        void init(int k) {sz = cnt, key = k;}

        node* refresh()
        {
            sz = cnt;
            sz += getSz(l) + getSz(r);
            return this;
        }

        void changeCount(int d){cnt += d, sz += d;}

        static int getSz(node* &n){return n ? n -> sz : 0;}
    };

    node* root = NULL;

    pair <node*, node*> splitKey(node* curr, int key)
    {
        if (!curr) return {NULL, NULL};
        pair <node*, node*> res;
        if (curr -> key <= key)
        {
            tie(curr -> r, res.second) = splitKey(curr -> r, key);
            res.first = curr -> refresh();
        }
        else
        {
            tie(res.first, curr -> l) = splitKey(curr -> l, key);
            res.second = curr -> refresh();
        }
        return res;
    }

    node* meld(node* &a, node* &b)
    {
        if (!a or !b) return a ? a : b;
        if (a -> priority >= b -> priority)
        {
            a -> r = meld(a -> r, b);
            return a -> refresh();
        }
        else
        {
            b -> l = meld(a, b -> l);
            return b -> refresh();
        }
    }

    void insert(int k)
    {
        auto a = splitKey(root, k - 1), b = splitKey(a.second, k);
        if (b.first) b.first -> changeCount(1);
        else b.first = new node(k);
        root = meld(a.first, root = meld(b.first, b.second));
    }

    void erase(int k)
    {
        auto a = splitKey(root, k - 1), b = splitKey(a.second, k);
        if (!b.first) root = meld(a.first, b.second);
        else
        {
            b.first -> changeCount(-1);
            root = meld(a.first, root = meld(b.first, b.second));
        }
    }

    int numBetween(int k1, int k2)
    {
        auto a = splitKey(root, k1 - 1), b = splitKey(a.second, k2);
        int res = node::getSz(b.first);
        root = meld(a.first, root = meld(b.first, b.second));
        return res;
    }
};

struct fenwickTree
{
    struct node : treap{};

    vector <node> elements;

    fenwickTree(int s)
    {
        elements.resize(s + 1);
    }

    void insert(int i, int v)
    {
        for (i++; i < elements.size(); i += i & (-i)) elements[i].insert(v);
    }

    void replace(int i, int v, int old)
    {
        for (i++; i < elements.size(); i += i & (-i))
        {
            elements[i].erase(old);
            elements[i].insert(v);
        }
    }

    int numBetween(int i, int k1, int k2)
    {
        int res = 0;
        for (i++; i > 0; i -= i & (-i)) res += elements[i].numBetween(k1, k2);
        return res;
    }

    int numBetween(int l, int r, int k1, int k2) {return numBetween(r, k1, k2) - numBetween(l - 1, k1, k2);}
};

int swapPositions(int l, int r, vector <int> &a, fenwickTree &ft)
{
    int n = a.size();
    int change = 0;
    if (r - l >= 2)
    {
        if (a[l] < a[r])
            change = 2 * ft.numBetween(l + 1, r - 1, a[l] + 1, a[r] - 1);
        else
            change = -2 * ft.numBetween(l + 1, r - 1, a[r] + 1, a[l] - 1);
    }
    if (a[l] < a[r]) change++;
    else if(a[l] > a[r]) change--;

    ft.replace(l, a[r], a[l]), ft.replace(r, a[l], a[r]);
    swap(a[l], a[r]);
    return change;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(time(0));

    int n, q;
    cin>>n>>q;

    vector <int> a(n);
    fenwickTree ft(n);
    for (int i = 0; i < n; i++)
    {
        a[i] = i;
        ft.insert(i, a[i]);
    }

    ll numInversions = 0;
    for (int i = 0; i < q; i++)
    {
        int l, r;
        cin>>l>>r;
        --l, --r;
        if (l > r) swap(l, r);

        numInversions += swapPositions(l, r, a, ft);

        cout<<numInversions<<'\n';
    }

    return 0;
}

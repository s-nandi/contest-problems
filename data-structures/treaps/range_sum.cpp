//treaps (implicit), append/prepend updates, range sum queries
//http://www.spoj.com/problems/RANGESUM/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

#define ll long long

struct node
{
    int key, priority;
    node *l, *r;
    int sz; ll sum;

    node(int k)
    {
        key = k, priority = (rand() << 16) ^ rand(), l = NULL, r = NULL, sz = 1, sum = k;
    }

    void refresh()
    {
        sz = 1, sum = key;
        if (l) sz += l -> sz, sum += l -> sum;
        if (r) sz += r -> sz, sum += r -> sum;
    }
};

struct treap
{
    node* root;

    treap()
    {
        root = NULL;
    }

    void splitIndex(node* curr, int index, node* &l, node* &r)
    {
        l = NULL, r = NULL;
        if (!curr) return;

        int lSize = getSz(curr -> l);
        if (lSize <= index)
        {
            splitIndex(curr -> r, index - lSize - 1, curr -> r, r);
            l = curr;
        }
        else
        {
            splitIndex(curr -> l, index, l, curr -> l);
            r = curr;
        }
        curr -> refresh();
    }

    node* meld(node* &a, node* &b)
    {
        if (!a or !b) return a ? a : b;
        else if (a -> priority >= b -> priority)
        {
            a -> r = meld(a -> r, b);
            a -> refresh();
            return a;
        }
        else
        {
            b -> l = meld(a, b -> l);
            b -> refresh();
            return b;
        }
    }

    void prepend(int k)
    {
        node *a = new node(k);
        root = meld(a, root);
    }

    void append(int k)
    {
        node *a = new node(k);
        root = meld(root, a);
    }

    ll query(int l, int r)
    {
        node *a, *b, *c;
        splitIndex(root, l - 1, a, b);
        splitIndex(b, r - l, b, c);

        ll res = b -> sum;

        root = meld(a, b);
        root = meld(root, c);
        return res;
    }

    int getSz(node* n) { return n ? n -> sz : 0; }
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    srand(time(0));

    int n;
    cin>>n;

    treap trp;
    for (int i = 0; i < n; i++)
    {
        int v;
        cin>>v;
        trp.append(v);
    }

    int q;
    cin>>q;

    for (int i = 0; i < q; i++)
    {
        int type;
        cin>>type;

        if (type == 1)
        {
            int l, r;
            cin>>l>>r;
            cout<<trp.query(--l, --r)<<'\n';
        }
        else if(type == 2)
        {
            int v;
            cin>>v;
            trp.prepend(v);
        }
    }

    return 0;
}

//treaps (explicit & implicit), min and max difference queries, insert/delete updates
//http://www.spoj.com/problems/TREAP/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

#define INF 1231231234

struct node
{
    int value, priority;
    node *l, *r;
    int sz, minElement, maxElement, minDifference;

    node(int k)
    {
        value = k, priority = (rand() << 16) ^ rand(), l = NULL, r = NULL, sz = 1, minElement = k, maxElement = k, minDifference = INF;
    }

    void refresh()
    {
        sz = 1, maxElement = value, minElement = value, minDifference = INF;
        if (l)
        {
            sz += l -> sz;
            minElement = min(minElement, l -> minElement);
            maxElement = max(maxElement, l -> maxElement);
            minDifference = min(min(minDifference, l -> minDifference), value - (l -> maxElement));
        }
        if (r)
        {
            sz += r -> sz;
            minElement = min(minElement, r -> minElement);
            maxElement = max(maxElement, r -> maxElement);
            minDifference = min(min(minDifference, r -> minDifference), (r -> minElement) - value);
        }
    }
};

struct treap
{
    node* root;

    treap()
    {
        root = NULL;
    }

    void split(node* curr, int v, node* &l, node* &r, bool byKey)
    {
        l = NULL, r = NULL;
        if (!curr) return;

        int leftCmp = byKey ? curr -> value : getSz(curr -> l);
        if (leftCmp <= v)
        {
            split(curr -> r, byKey ? v : v - leftCmp - 1, curr -> r, r, byKey);
            l = curr;
        }
        else
        {
            split(curr -> l, v, l, curr -> l, byKey);
            r = curr;
        }
        curr -> refresh();
    }

    void splitKey(node* curr, int key, node* &l, node* &r) { split(curr, key, l, r, true); }
    void splitIndex(node* curr, int index, node* &l, node* &r) { split(curr, index, l, r, false); }

    node* meld(node* &a, node* &b)
    {
        if (!a or !b) return a ? a : b;

        if (a -> priority >= b -> priority)
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

    void insert(int k)
    {
        node *a, *b, *c, *nn = new node(k);
        splitKey(root, k - 1, a, b);
        splitKey(b, k, b, c);
        root = meld(a, nn);
        root = meld(root, c);
    }

    void erase(int k)
    {
        node *a, *b, *c;
        splitKey(root, k - 1, a, b);
        splitKey(b, k, b, c);
        root = meld(a, c);
    }

    int query(int l, int r, int type)
    {
        node *a, *b, *c;

        if (l == r) return -1;

        splitIndex(root, l - 1, a, b);
        splitIndex(b, r - l, b, c);

        int res = !type ? (b -> maxElement - b -> minElement) : b -> minDifference;

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

    int q;
    cin>>q;

    treap trp;

    for (int i = 0; i < q; i++)
    {
        char type;
        cin>>type;

        if (type == 'I' or type == 'D')
        {
            int v;
            cin>>v;
            if (type == 'I') trp.insert(v);
            else trp.erase(v);
        }
        else if(type == 'X' or type == 'N')
        {
            int l, r;
            cin>>l>>r;

            if (type == 'X') cout<<trp.query(l, r, 0)<<'\n';
            else cout<<trp.query(l, r, 1)<<'\n';
        }
    }

    return 0;
}

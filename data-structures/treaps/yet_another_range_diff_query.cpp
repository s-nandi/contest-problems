//treaps, min and max difference in interval queries, insert/delete updates
//http://www.spoj.com/problems/TREAP/

#include <iostream>
#include <vector>
#include <tuple>

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

    node* refresh()
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
        return this;
    }
};

struct treap
{
    node* root;

    treap()
    {
        root = NULL;
    }

    pair <node*, node*> splitValue(node* curr, int value)
    {
        if (!curr) return {NULL, NULL};

        pair <node*, node*> res;
        if (curr -> value <= value)
        {
            tie(curr -> r, res.second) = splitValue(curr -> r, value);
            res.first = curr -> refresh();
        }
        else
        {
            tie(res.first, curr -> l) = splitValue(curr -> l, value);
            res.second = curr -> refresh();
        }
        return res;
    }

    pair <node*, node*> splitIndex(node* curr, int index)
    {
        if (!curr) return {NULL, NULL};

        pair <node*, node*> res;
        if (getSz(curr -> l) <= index)
        {
            tie(curr -> r, res.second) = splitIndex(curr -> r, index - getSz(curr -> l) - 1);
            res.first = curr -> refresh();
        }
        else
        {
            tie(res.first, curr -> l) = splitIndex(curr -> l, index);
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
            a = a -> refresh();
            return a;
        }
        else
        {
            b -> l = meld(a, b -> l);
            b = b -> refresh();
            return b;
        }
    }

    void insert(int k)
    {
        node *a, *b, *c, *nn = new node(k);
        tie(a, b) = splitValue(root, k - 1);
        tie(b, c) = splitValue(b, k);
        root = meld(a, nn);
        root = meld(root, c);
    }

    void erase(int k)
    {
        node *a, *b, *c;
        tie(a, b) = splitValue(root, k - 1);
        tie(b, c) = splitValue(b, k);
        root = meld(a, c);
    }

    int query(int l, int r, int type)
    {
        node *a, *b, *c;

        if (l == r) return -1;

        tie(a, b) = splitIndex(root, l - 1);
        tie(b, c) = splitIndex(b, r - l);

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

//treaps (implicit, lazy propagation), reverse/split/prepend queries, inorder traversal
//https://www.codechef.com/JAN12/problems/CARDSHUF/

#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

struct node
{
    int key, priority, sz;
    node *l, *r;
    bool lazy;

    node(int k)
    {
        key = k, priority = (rand() << 16) ^ rand(), l = NULL, r = NULL, sz = 1, lazy = false;
    }

    node* refresh()
    {
        sz = 1;
        if (l) sz += l -> sz;
        if (r) sz += r -> sz;
        return this;
    }

    void pushLazy()
    {
        if (lazy)
        {
            swap(l, r);
            if (l) l -> setLazy();
            if (r) r -> setLazy();
            resetLazy();
        }
    }

    void setLazy() {lazy ^= true;}
    void resetLazy(){lazy = false;}
};

struct treap
{
    node* root;

    treap()
    {
        root = NULL;
    }

    pair <node*, node*> splitIndex(node* curr, int index)
    {
        if (!curr) return {NULL, NULL};
        curr -> pushLazy();

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
        if (a) a -> pushLazy();
        if (b) b -> pushLazy();
        if (!a or !b) return a ? a: b;

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

    void append(int k)
    {
        node *a = new node(k);
        root = meld(root, a);
    }

    void shuffle(int A, int B, int C)
    {
        node *a, *b, *c;
        tie(a, b) = splitIndex(root, A);
        tie(b, c) = splitIndex(b, B);
        root = meld(a, c);
        tie(a, c) = splitIndex(root, C);
        b -> setLazy();
        root = meld(b, c);
        root = meld(a, root);
    }

    int popFirst()
    {
        node* t;
        tie(t, root) = splitIndex(root, 0);
        return t -> key;
    }

    vector <int> inorder()
    {
        vector <int> v;
        inorder(root, v);
        return v;
    }

    void inorder(node* &curr, vector <int> &v)
    {
        if (!curr) return;
        curr -> pushLazy();

        inorder(curr -> l, v);
        v.push_back(curr -> key);
        inorder(curr -> r, v);
    }

    int getSz(node* n) { return n ? n -> sz : 0; }
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin>>n>>q;

    treap trp;

    for (int i = 1; i <= n; i++)
    {
        trp.append(i);
    }

    for (int i = 0; i < q; i++)
    {
        int a, b, c;
        cin>>a>>b>>c;
        trp.shuffle(--a, --b, --c);
    }

    for (int i: trp.inorder())
    {
        cout<<i<<" ";
    }
    cout<<'\n';

    return 0;
}

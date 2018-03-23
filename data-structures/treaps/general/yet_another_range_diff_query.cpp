//treaps, min and max difference queries, insert/delete updates
//http://www.spoj.com/problems/TREAP/

#include <iostream>
#include <vector>
#include <tuple>
#include <random>
#include <ctime>

using namespace std;

const int INF = 1231231234;

struct node
{
    int key, priority;
    node *l, *r;
    int sz, minElement, maxElement, minDifference;

    node(int k) : priority(rand() << 16 ^ rand()), l(NULL), r(NULL) {init(k);}
    void init(int k) {sz = 1, key = k, minElement = k, maxElement = k, minDifference = INF;}

    node* refresh()
    {
        init(key);
        sz += getSz(l) + getSz(r);
        if (l)
        {
            minElement = min(minElement, l -> minElement), maxElement = max(maxElement, l -> maxElement);
            minDifference = min(min(minDifference, l -> minDifference), key - (l -> maxElement));
        }
        if (r)
        {
            minElement = min(minElement, r -> minElement), maxElement = max(maxElement, r -> maxElement);
            minDifference = min(min(minDifference, r -> minDifference), (r -> minElement) - key);
        }
        return this;
    }

    static int getSz(node* n){return n ? n -> sz : 0;}
};

struct treap
{
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

    pair <node*, node*> splitIndex(node* curr, int index)
    {
        if (!curr) return {NULL, NULL};
        pair <node*, node*> res;
        if (node::getSz(curr -> l) <= index)
        {
            tie(curr -> r, res.second) = splitIndex(curr -> r, index - node::getSz(curr -> l) - 1);
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
        b.first = new node(k);
        root = meld(a.first, root = meld(b.first, b.second));
    }

    void erase(int k)
    {
        auto a = splitKey(root, k - 1), b = splitKey(a.second, k);
        root = meld(a.first, b.second);
    }

    int query(int l, int r, int type)
    {
        if (l == r) return -1;
        auto a = splitIndex(root, l - 1), b = splitIndex(a.second, r - l);
        int res = !type ? (b.first -> maxElement - b.first -> minElement) : b.first -> minDifference;
        root = meld(a.first, root = meld(b.first, b.second));
        return res;
    }
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

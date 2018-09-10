// tree isomorphism (branches are distinct, recursively check if left/right branches match)
// https://icpc.kattis.com/problems/ceiling
// 2016 ICPC World Finals

#include <iostream>
#include <vector>

using namespace std;

struct tree
{
    int val;
    tree *l, *r;

    tree(){}
    tree(int v)
    {
        val = v;
        l = r = NULL;
    }

    void insert(int v)
    {
        if (v < val)
        {
            if (!l)
                l = new tree(v);
            else
                l -> insert(v);
        }
        else
        {
            if (!r)
                r = new tree(v);
            else
                r -> insert(v);
        }
    }
};

bool isomorphic(tree* a, tree* b)
{
    if (!a or !b)
        return !a and !b;
    return isomorphic(a -> l, b -> l) and isomorphic(a -> r, b -> r);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin>>n>>k;

    int sol = 0;
    vector <tree*> trees(n);
    for (int i = 0; i < n; i++)
    {
        vector <int> a(k);
        for (int j = 0; j < k; j++)
        {
            cin>>a[j];
        }
        trees[i] = new tree(a[0]);
        for (int j = 1; j < k; j++)
        {
            trees[i] -> insert(a[j]);
        }

        bool isUnique = true;
        for (int j = 0; j < i; j++)
        {
            if (isomorphic(trees[i], trees[j]))
            {
                isUnique = false;
                break;
            }
        }
        if (isUnique)
            sol++;
    }
    cout<<sol<<'\n';
}

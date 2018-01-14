//k-th order tree
//http://www.spoj.com/problems/ORDERSET/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct segmentTree
{
    int sz;
    vector <int> elements;

    segmentTree(int s)
    {
        sz = 1;
        while (sz < s) sz *= 2;
        elements.resize(2 * sz);
    }

    void modify(int p, int val)
    {
        p += sz;
        if (elements[p] + val >= 0 and elements[p] + val <= 1) //remove if multiset is wanted
        {
            elements[p] += val;
        }
        while (p >= 2)
        {
            elements[p >> 1] = elements[p] + elements[p ^ 1];
            p >>= 1;
        }
    }

    int queryCount(int l, int r)
    {
        int acc = 0;
        l += sz;
        r += sz;
        while (l <= r)
        {
            if (l & 1)
            {
                acc += elements[l];
                l++;
            }
            if (!(r & 1))
            {
                acc += elements[r];
                r--;
            }
            l >>= 1;
            r >>= 1;
        }
        return acc;
    }

    int queryKth(int k)
    {
        if (elements[1] < k) return -1;

        int currNode = 1;
        while (currNode < sz)
        {
            if (elements[currNode << 1] >= k)
            {
                currNode = currNode << 1;
            }
            else
            {
                k -= elements[currNode << 1];
                currNode = currNode << 1 | 1;
            }
        }
        return currNode - sz;
    }
};

struct query
{
    char type;
    int val;
};

vector <int> numbers;

int mapping(int i)
{
    return lower_bound(numbers.begin(), numbers.end(), i) - numbers.begin();
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    cin>>q;

    numbers.resize(q);
    vector <query> queries(q);
    for (int i = 0; i < q; i++)
    {
        char t;
        int v;
        cin>>t>>v;
        queries[i] = {t, v};
        numbers[i] = v;
    }

    sort(numbers.begin(), numbers.end());
    numbers.erase(unique(numbers.begin(), numbers.end()), numbers.end());

    segmentTree st(numbers.size());

    for (query qu: queries)
    {
        if (qu.type != 'K') qu.val = mapping(qu.val);

        if (qu.type == 'I')
        {
            st.modify(qu.val, 1);
        }
        else if(qu.type == 'D')
        {
            st.modify(qu.val, -1);
        }
        else if(qu.type == 'C')
        {
            cout<<st.queryCount(0, qu.val - 1)<<'\n';
        }
        else
        {
            int res = st.queryKth(qu.val);
            if (res == -1)
            {
                cout<<"invalid"<<'\n';
            }
            else
            {
                cout<<numbers[res]<<'\n';
            }
        }
    }

    return 0;
}

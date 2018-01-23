//segment tree, finding # of elements below threshold queries, point increment updates
//http://www.spoj.com/problems/INVCNT/

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
        sz = s;
        elements.resize(2 * sz);
    }

    void modify(int p)
    {
        p += sz;
        elements[p]++;

        while (p >= 2)
        {
            elements[p >> 1] = elements[p] + elements[p ^ 1];
            p >>= 1;
        }
    }

    int query(int l, int r)
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
};

vector <int> sorted;

int mapping(int i)
{
    return lower_bound(sorted.begin(), sorted.end(), i) - sorted.begin();
}

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        vector <int> a(n);

        for (int i = 0; i < n; i++)
        {
            cin>>a[i];
        }
        sorted = a;
        sort(sorted.begin(), sorted.end());

        segmentTree st(n);
        long long res = 0;
        for (int i = 0; i < n; i++)
        {
            int pos = mapping(a[i]);
            st.modify(pos);
            res += st.query(pos + 1, n - 1);
        }
        cout<<res<<'\n';
    }
}

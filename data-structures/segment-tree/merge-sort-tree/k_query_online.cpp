//merge sort tree (static), find kth element in interval (online)
//http://www.spoj.com/problems/KQUERYO/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct segmentTree
{
    int sz;
    vector <vector<int>> elements;

    segmentTree(int s)
    {
        sz = s;
        elements.resize(2 * sz);
    }

    void initVal(int pos, int val)
    {
        elements[pos + sz] = {val};
    }

    void build()
    {
        for (int i = sz - 1; i >= 1; i--)
        {
            elements[i].resize(elements[i << 1].size() + elements[i << 1 | 1].size());
            merge(elements[i << 1].begin(), elements[i << 1].end(), elements[i << 1 | 1].begin(), elements[i << 1 | 1].end(), elements[i].begin());
        }
    }

    int numGreater(vector <int> &v, int k)
    {
        return (int) v.size() - (upper_bound(v.begin(), v.end(), k) - v.begin());
    }

    int query(int l, int r, int k)
    {
        int acc = 0;
        l += sz;
        r += sz;
        while (l <= r)
        {
            if (l & 1)
            {
                acc += numGreater(elements[l], k);
                l++;
            }
            if (!(r & 1))
            {
                acc += numGreater(elements[r], k);
                r--;
            }
            l >>= 1;
            r >>= 1;
        }

        return acc;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;

    segmentTree st(n);

    for (int i = 0; i < n; i++)
    {
        int num;
        cin>>num;
        st.initVal(i, num);
    }
    st.build();

    int q;
    cin>>q;

    int res = 0;
    for (int i = 0; i < q; i++)
    {
        int l, r, k;
        cin>>l>>r>>k;

        l ^= res; r ^= res; k ^= res;

        l = max(0, --l);
        r = min(n - 1, --r);

        if (l > r)
        {
            res = 0;
        }
        else
        {
            res = st.query(l, r, k);
        }

        cout<<res<<'\n';
    }

    return 0;
}
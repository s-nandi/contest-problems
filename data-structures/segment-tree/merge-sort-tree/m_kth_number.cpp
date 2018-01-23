//merge sort tree, binary search on answer, coordinate compression
//http://www.spoj.com/problems/MKTHNUM/

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

    int numLess(vector <int> &v, int k)
    {
        return lower_bound(v.begin(), v.end(), k) - v.begin();
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
                acc += numLess(elements[l], k);
                l++;
            }
            if (!(r & 1))
            {
                acc += numLess(elements[r], k);
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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin>>n>>m;

    vector <int> a(n);
    segmentTree st(n);

    for (int i = 0; i < n; i++)
    {
        cin>>a[i];
    }

    sorted = a;
    sort(sorted.begin(), sorted.end());

    for (int i = 0; i < n; i++)
    {
        st.initVal(i, mapping(a[i]));
    }
    st.build();

    for (int i = 0; i < m; i++)
    {
        int l, r, k;
        cin>>l>>r>>k;
        --l; --r; --k;

        int left = 0;
        int right = n - 1;

        while (left < right)
        {
            int mid = (left + right + 1) / 2;

            if (st.query(l, r, mid) <= k)
            {
                left = mid;
            }
            else
            {
                right = mid - 1;
            }
        }

        cout<<sorted[left]<<'\n';
    }

    return 0;
}

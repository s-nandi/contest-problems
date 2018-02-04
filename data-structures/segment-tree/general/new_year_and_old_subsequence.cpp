//segment tree (non-commutative operator), finite state automata
//http://codeforces.com/contest/750/problem/E

#include <iostream>
#include <vector>

using namespace std;

#define INF 1031231234

struct node
{
    int state[5][5];

    node()
    {
        for (int i = 0; i < 5; i++) for (int j = i; j < 5; j++)
        {
            state[i][j] = INF;
        }
    }

    node(char v) : node()
    {
        for (int i = 0; i < 5; i++) state[i][i] = 0;

        switch (v)
        {
            case '2':
                state[0][0] = 1;
                state[0][1] = 0;
                break;
            case '0':
                state[1][1] = 1;
                state[1][2] = 0;
                break;
            case '1':
                state[2][2] = 1;
                state[2][3] = 0;
                break;
            case '6':
                state[3][3] = 1;
                state[4][4] = 1;
                break;
            case '7':
                state[3][3] = 1;
                state[3][4] = 0;
                break;
        }
    }

    node combine(const node &o) const
    {
        node res;
        for (int k = 0; k < 5; k++)
        {
            for (int i = 0; i <= k; i++)
            {
                for (int j = k; j < 5; j++)
                {
                    res.state[i][j] = min(res.state[i][j], state[i][k] + o.state[k][j]);
                }
            }
        }
        return res;
    }
};

struct segmentTree
{
    int sz;
    vector <node> elements;

    segmentTree(int s)
    {
        sz = s;
        elements.resize(2 * sz);
    }

    node& operator [] (int i)
    {
        return elements[i + sz];
    }

    void build()
    {
        for (int i = sz - 1; i >= 1; i--)
        {
            elements[i] = elements[i << 1].combine(elements[i << 1 | 1]);
        }
    }

    int query(int l, int r)
    {
        node lacc, racc;
        lacc.state[0][0] = 0, racc.state[4][4] = 0;

        l += sz;
        r += sz;
        while (l <= r)
        {
            if (l & 1)
            {
                lacc = lacc.combine(elements[l]);
                l++;
            }
            if (!(r & 1))
            {
                racc = elements[r].combine(racc);
                r--;
            }
            l >>= 1;
            r >>= 1;
        }

        node res = lacc.combine(racc);
        return res.state[0][4] != INF ? res.state[0][4] : -1;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin>>n>>q;

    string s;
    cin>>s;

    segmentTree st(n);
    for (int i = 0; i < n; i++)
    {
        st[i] = node(s[i]);
    }
    st.build();

    for (int i = 0; i < q; i++)
    {
        int l, r;
        cin>>l>>r;
        cout<<st.query(--l, --r)<<'\n';
    }

    return 0;
}

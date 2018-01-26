//parallel binary search (simulation), segment tree (range increment updates, point value queries)
//http://www.spoj.com/problems/METEORS/

#include <iostream>
#include <vector>

using namespace std;

#define MAXV 1000000001

struct segmentTree
{
    int sz;
    vector <int> elements;

    segmentTree(int s)
    {
        sz = s;
        elements.resize(2 * sz);
    }

    void modify(int l, int r, int v)
    {
        l += sz, r += sz;
        while (l <= r)
        {
            if (l & 1)
            {
                elements[l] = min(MAXV, elements[l] + v);
                l++;
            }
            if (!(r & 1))
            {
                elements[r] = min(MAXV, elements[r] + v);
                r--;
            }
            l >>= 1;
            r >>= 1;
        }
    }

    int query(int p)
    {
        int acc = 0;
        p += sz;
        while (p >= 1)
        {
            acc = min(MAXV, acc + elements[p]);
            p >>= 1;
        }
        return acc;
    }
};

struct query
{
    int l, r, v;
};

int numSectors;
vector <vector<int>> territory;
vector <int> needed;
vector <query> queries;

vector <int> parallelBinarySearch(int n)
{
    vector <int> l(n, 0), r(n, queries.size()), sol(n, -1);

    bool solved = false;
    while (!solved)
    {
        vector <vector<int>> m(queries.size());
        segmentTree st(numSectors);
        solved = true;
        for (int i = 0; i < n; i++)
        {
            if (l[i] < r[i])
            {
                int mp = (l[i] + r[i]) / 2;
                m[mp].push_back(i);
                solved = false;
            }
        }
        for (int i = 0; i < queries.size(); i++)
        {
            if (queries[i].l > queries[i].r)
            {
                st.modify(queries[i].l, numSectors - 1, queries[i].v);
                st.modify(0, queries[i].r, queries[i].v);
            }
            else
            {
                st.modify(queries[i].l, queries[i].r, queries[i].v);
            }

            for (int member: m[i])
            {
                int achieved = 0;
                for (int sector: territory[member])
                {
                    achieved += st.query(sector);
                    if (achieved >= needed[member]) break;
                }

                if (achieved < needed[member])
                {
                    l[member] = i + 1;
                }
                else
                {
                    r[member] = i;
                    sol[member] = i;
                }
            }
        }
    }
    return sol;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n>>numSectors;

    territory.resize(n);
    needed.resize(n);

    for (int i = 0; i < numSectors; i++)
    {
        int member;
        cin>>member;
        territory[--member].push_back(i);
    }

    for(int i = 0; i < n; i++)
    {
        cin>>needed[i];
    }

    int q;
    cin>>q;

    queries.resize(q);

    for (int i = 0; i < q; i++)
    {
        int l, r, v;
        cin>>l>>r>>v;
        --l, --r;
        queries[i].l = l, queries[i].r = r, queries[i].v = v;
    }

    auto sol = parallelBinarySearch(n);

    for (int i: sol)
    {
        if (i == -1)
            cout<<"NIE"<<'\n';
        else
            cout<<i + 1<<'\n';
    }

    return 0;
}

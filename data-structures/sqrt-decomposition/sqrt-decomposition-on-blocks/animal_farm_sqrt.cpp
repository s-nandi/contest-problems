// dynamic programming with sqrt decomposition (on blocks), range maximum query, range increment update, binary search
// https://www.hackerrank.com/contests/world-codesprint-12/challenges/animal-transport/problem

#include <bits/stdc++.h>

using namespace std;

const int INF = 1231231234;

struct sqrt_block
{
    int delta = 0, mx = -INF;
    vector <pair<int, int>> elements;

    void modifyWhole(int v) {delta += v;}
    void modifyPartial(int l, int r, int v)
    {
        for (auto &elem: elements) if (l <= elem.second and elem.second <= r)
            elem.first += v, mx = max(mx, elem.first);
    }

    int queryWhole() {return mx + delta;}
    int queryPartial(int l, int r)
    {
        int res = -INF;
        for (auto &elem: elements) if (l <= elem.second and elem.second <= r)
            res = max(res, elem.first);
        return res + delta;
    }
};

struct block_decomposition
{
    int sz, bsz, nb;
    vector <sqrt_block> blocks;

    block_decomposition(){}
    block_decomposition(const vector <int> &v, int BLOCK_SIZE) : sz(v.size()), bsz(BLOCK_SIZE), nb(sz / BLOCK_SIZE + 1), blocks(nb)
    {
        for (int i = 0; i < v.size(); i++)
            blocks[i / bsz].elements.push_back({v[i], i});
    }

    int overlap(int i, int ql, int qr)
    {
        int lb = i * bsz, rb = (i + 1) * bsz - 1;
        if (ql <= lb and qr >= rb) return 2;
        else if (ql > rb or qr < lb) return 0;
        else return 1;
    } // 2: query covers block, 1: query overlaps block, 0: no overlap

    void modify(int l, int r, int v)
    {
        for (int i = 0; i < nb; i++)
        {
            auto o = overlap(i, l, r);
            if (o == 2)
                blocks[i].modifyWhole(v);
            else if (o == 1)
                blocks[i].modifyPartial(l, r, v);
        }
    }

    int query(int l, int r)
    {
        int acc = -INF;
        for (int i = 0; i < nb; i++)
        {
            auto o = overlap(i, l, r);
            if (o == 2)
                acc = max(acc, blocks[i].queryWhole()); // PS: might be + or min() instead of max()
            else if (o == 1)
                acc = max(acc, blocks[i].queryPartial(l, r)); // PS: same as above
        }
        return acc;
    }
};

struct segment
{
    int type, start, destination;
    bool operator < (segment o) const
    {
        return destination < o.destination;
    }
};

int main()
{
    int T;
    cin>>T;
    while (T--)
    {
        int n, m;
        cin >> m >> n;

        vector <segment> segments(n);
        for (int i = 0; i < n; i++)
        {
            char c;
            cin >> c;
            segments[i].type = (c == 'D' or c == 'M') ? 0 : 1;
        }
        for (int i = 0; i < n; i++)
        {
            cin >> segments[i].start;
            --segments[i].start;
        }
        for (int i = 0; i < n; i++)
        {
            cin>>segments[i].destination;
            --segments[i].destination;
        }
        sort(segments.begin(), segments.end());

        vector <int> dp(m);
        block_decomposition bd[2];
        for (int i = 0; i < 2; i++)
            bd[i] = block_decomposition(vector<int>(m), sqrt(m) + 5);

        int curr = 0;
        for (int i = 0; i < m; i++)
        {
            while (segments[curr].destination == i and curr < segments.size())
            {
                segment s = segments[curr++];
                if (s.destination < s.start) continue;
                bd[s.type].modify(0, s.start, 1);
            }
            dp[i] = max(bd[0].query(0, i), bd[1].query(0, i));
            bd[0].modify(i, i, dp[i]);
            bd[1].modify(i, i, dp[i]);
        }
        for (int i = 1; i <= n; i++)
        {
            int pos = lower_bound(dp.begin(), dp.end(), i) - dp.begin() + 1;
            if (pos <= m)
                cout << pos << " ";
            else
                cout << -1 << " ";
        }
        cout << '\n';
    }
}

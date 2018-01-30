//suffix array (range lcp queries), longest common substring, sparse table, 2-pointer method
//http://www.spoj.com/problems/LONGCS/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct sparseTable
{
    int sz, h = 0;
    vector <vector<int>> table;
    vector <int> log;

    void initialize(int s)
    {
        sz = s;
        while (1 << h < s) h++;
        table.resize(sz, vector<int>(h + 1, -1)), log.resize(sz + 1);
    }

    int& operator [] (int i)
    {
        return table[i][0];
    }

    void build()
    {
        for (int j = 1; j <= h; j++)
        {
            for (int i = 0; i + (1 << j) - 1 < sz; i++)
            {
                table[i][j] = min(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
            }
        }
        for (int i = 0; i < sz; i++) log[i + 1] = (i + 1) >> log[i] >= 2 ? log[i] + 1 : log[i];
    }

    int query(int l, int r)
    {
        int k = log[r - l + 1];
        return min(table[l][k], table[r - (1 << k) + 1][k]);
    }
};

struct element
{
    pair <int, int> ranking;
    int index;

    bool operator < (element o) const
    {
        return ranking != o.ranking ? ranking < o.ranking : index < o.index;
    }
};

struct suffixArray
{
    int sz, h = 0;
    vector <int> ranks, ordered;
    vector <element> suffix;
    sparseTable sp;

    suffixArray(string &s)
    {
        sz = s.length();
        while (1 << h < sz) h++;

        ranks.resize(sz), suffix.resize(sz), ordered.resize(sz);

        for (int i = 0; i < sz; i++)
        {
            ranks[i] = int(s[i]);
        }
        for (int k = 1, len = 1; k <= h; k++, len <<= 1)
        {
            for (int i = 0; i < sz; i++)
            {
                suffix[i] = {{ranks[i], i + len < sz ? ranks[i + len] : -1}, i};
            }
            sort(suffix.begin(), suffix.end());
            int numBuckets = 0;
            for (int i = 0; i < sz; i++)
            {
                ranks[suffix[i].index] = i > 0 and suffix[i].ranking == suffix[i - 1].ranking ? ranks[suffix[i - 1].index] : numBuckets++;
            }
            if (numBuckets == sz) break;
        }
        for (int i = 0; i < sz; i++)
        {
            ordered[ranks[i]] = i;
        }
        sp.initialize(sz);
        kasaiLCP(s);
        sp.build();
    }

    void kasaiLCP(string &s)
    {
        for(int i = 0, k = 0; i < sz; i++, k = max(0, k - 1))
        {
            if (ranks[i] == sz - 1)
            {
                k = 0;
                continue;
            }
            int j = ordered[ranks[i] + 1];
            while(i + k < sz and j + k < sz and s[i + k] == s[j + k]) k++;
            sp[ranks[i]] = k;
        }
    }

    int lcp(int l, int r)
    {
        return sp.query(l, --r);
    }
};

int longestCommonSubstring(vector <string> &v)
{
    int n = v.size();
    vector <int> partitions(n);

    string concat = "";
    for (int i = 0; i < n; i++)
    {
        concat += v[i] + "!";
        partitions[i] = v[i].size() + 1 + (i > 0 ? partitions[i - 1] : 0);
    }

    suffixArray sa(concat);
    vector <int> categories(concat.length());

    for (int i = 0; i < concat.length(); i++)
    {
        categories[i] = upper_bound(partitions.begin(), partitions.end(), i) - partitions.begin();
    }

    vector <int> counts(n);
    int active = 0, sol = -1;

    for (int l = 0, r = 0; l < concat.length(); l++)
    {
        while (r < concat.length() and (r <= l or active < n))
        {
            int rPartition = categories[sa.ordered[r]];
            if (++counts[rPartition] == 1) active++;
            r++;
        }
        if (active == n)
        {
            int possibleSol = sa.lcp(l, r - 1);
            sol = max(sol, possibleSol);
        }
        int lPartition = categories[sa.ordered[l]];
        if (--counts[lPartition] == 0) active--;
    }

    return sol;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin>>T;

    while(T--)
    {
        int n;
        cin>>n;
        vector <string> strings(n);
        for (int i = 0; i < n; i++)
        {
            cin>>strings[i];
        }
        cout<<longestCommonSubstring(strings)<<'\n';
    }

    return 0;
}

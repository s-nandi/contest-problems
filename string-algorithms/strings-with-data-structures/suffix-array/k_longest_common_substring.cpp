//suffix array (radix sort), kasai's algorithm (range lcp queries), longest common substring of k strings, sparse table, two pointer method
//http://www.spoj.com/problems/LONGCS/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MAXN 100010

struct sparseTable
{
    int sz, h = 0;
    vector <vector<int>> table;
    vector <int> log;

    void initialize(int s)
    {
        sz = s;
        while (1 << h < sz) h++;
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

typedef vector <int> intString;

struct element
{
    pair <int, int> ranking;
    int index;
};

vector <element> bucket[MAXN];
int numBuckets;
void countingSort(vector <element> &v, bool byFirst)
{
    for (int i = 0; i < v.size(); i++)
    {
        bucket[byFirst ? v[i].ranking.first + 1 : v[i].ranking.second + 1].push_back(v[i]);
    }
    for (int i = 0, pos = 0; i <= numBuckets; i++)
    {
        for (auto &elem: bucket[i]) v[pos++] = elem;
        bucket[i].clear();
    }
}

void radixSort(vector <element> &v)
{
    countingSort(v, false);
    countingSort(v, true);
}

struct suffixArray
{
    int sz, h = 0;
    vector <int> ranks, ordered;
    vector <element> suffix;
    sparseTable sp;

    suffixArray(intString &s)
    {
        sz = s.size();
        while (1 << h < sz) h++;
        numBuckets = 0;

        ranks.resize(sz), suffix.resize(sz), ordered.resize(sz);

        for (int i = 0; i < sz; i++)
        {
            ranks[i] = s[i];
            numBuckets = max(numBuckets, ranks[i] + 1);
        }
        for (int k = 1, len = 1; k <= h; k++, len <<= 1)
        {
            for (int i = 0; i < sz; i++)
            {
                suffix[i] = {{ranks[i], i + len < sz ? ranks[i + len] : -1}, i};
            }
            radixSort(suffix);
            numBuckets = 0;
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

    void kasaiLCP(intString &s)
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

    intString concat;
    for (int i = 0; i < n; i++)
    {
        for (char c: v[i])
        {
            concat.push_back(c);
        }
        concat.push_back(256 + i);
    }

    int m = concat.size();

    suffixArray sa(concat);
    vector <int> categories(m);

    for (int i = 1; i < m; i++)
    {
        categories[i] = (concat[i] < 256) ? categories[i - 1] : categories[i - 1] + 1;
    }

    vector <int> counts(n);
    int sol = -1;

    for (int l = 0, r = 0, active = 0; l < m; l++)
    {
        while (r < m and (r <= l or active < n))
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

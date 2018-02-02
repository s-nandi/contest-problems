//suffix array, kasai's algorithm, find # of distinct substrings
//http://www.spoj.com/problems/DISUBSTR/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MAXN 1005

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
    vector <int> ranks, ordered, lcp;
    vector <element> suffix;

    suffixArray(string &s)
    {
        sz = s.length();
        while (1 << h < sz) h++;

        ranks.resize(sz), suffix.resize(sz), ordered.resize(sz), lcp.resize(sz);

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
        kasaiLCP(s);
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
            lcp[ranks[i]] = k;
        }
    }
};

int main()
{
    int n;
    cin>>n;

    for (int i = 0; i < n; i++)
    {
        string s;
        cin>>s;

        suffixArray sa(s);

        int sol = 0;
        for (int i = 0; i < s.length(); i++)
        {
            sol += (s.length() - sa.ordered[i]) - sa.lcp[i];
        }
        cout<<sol<<'\n';
    }
}

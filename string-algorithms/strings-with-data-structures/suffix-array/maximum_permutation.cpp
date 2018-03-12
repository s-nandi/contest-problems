//suffix array, kasai's algorithm, frequency table for permutation, find minimum flagged substring of length k
//https://www.hackerrank.com/contests/university-codesprint-4/challenges/maximum-permutation/problem

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct element
{
    pair <int, int> ranking;
    int index;

    bool operator < (const element &o) const
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
            ranks[i] = s[i] - 'a';
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
    int T;
    cin>>T;
    while(T--)
    {
        string w, s;
        cin>>w>>s;

        vector <int> wTable(26), sTable(26);

        for (int i = 0; i < w.length(); i++)
        {
            wTable[w[i] - 'a']++;
            sTable[s[i] - 'a']++;
        }

        vector <int> matches(s.length());
        for (int i = 0; i <= s.length() - w.length(); i++)
        {
            if (sTable == wTable)
            {
                matches[i] = true;
            }
            if (i + w.length() < s.length())
            {
                sTable[s[i] - 'a']--;
                sTable[s[i + w.length()] - 'a']++;
            }
        }

        suffixArray sa(s);

        int sol = 0, pos = 0, curr = 0;
        for (int i = 0; i < s.length(); i++)
        {
            if (curr == 0)
            {
                if (matches[sa.ordered[i]]) curr = 1;
                else continue;
            }

            if (sa.lcp[i] >= w.length()) curr++;
            else
            {
                if (curr > sol)
                {
                    sol = curr;
                    pos = sa.ordered[i];
                }
                curr = 0;
            }
        }
        if (sol == 0)
        {
            cout<<-1<<'\n';
        }
        else
        {
            cout<<s.substr(pos, w.length())<<'\n';
        }
    }
}

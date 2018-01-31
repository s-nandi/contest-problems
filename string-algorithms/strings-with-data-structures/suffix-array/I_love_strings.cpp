//suffix array (early termination), string matching, binary search on answer
//https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&category=&problem=1620

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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
    vector <int> ranks;
    vector <element> suffix;
    int sz, h = 0;
    string str;

    suffixArray(string &s)
    {
        sz = s.length();
        while (1 << h < sz) h++;
        ranks.resize(sz), suffix.resize(sz);
        str = s;

        for (int i = 0; i < sz; i++)
        {
            ranks[i] = int(s[i]);
        }
        for (int k = 1; k <= h; k++)
        {
            int len = 1 << (k - 1);
            if (len >= 1000) break;

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
    }

    bool isSubstring(string &s)
    {
        int l = 0, r = sz - 1;
        while (l < r)
        {
            int m = (l + r) / 2;

            int res = str.compare(m, s.length(), s);
            if (res <= 0)
            {
                l = m;
            }
            else
            {
                r = m -1;
            }
        }
        return str.compare(l, s.length(), s) == 0;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin>>T;

    while(T--)
    {
        string s;
        cin>>s;

        suffixArray sa(s);

        int q;
        cin>>q;

        for (int i = 0; i < q; i++)
        {
            string t;
            cin>>t;

            cout<<(sa.isSubstring(t) ? "y" : "n")<<'\n';
        }
    }

    return 0;
}

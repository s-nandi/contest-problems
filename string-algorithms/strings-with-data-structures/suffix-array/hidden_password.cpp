//suffix array (string rotation)
//https://icpcarchive.ecs.baylor.edu/index.php?option=onlinejudge&page=show_problem&problem=756
//2003 Southeastern European Regional

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define LOGN 20
#define MAXN 100001

struct element
{
    pair <int, int> ranking;
    int index;
    bool operator < (element o) const
    {
        if (ranking != o.ranking)
            return ranking < o.ranking;
        else
            return index < o.index;
    }
};

int table[LOGN][MAXN];
int lr;
int minPrefix;

struct suffixArray
{
    suffixArray(string s)
    {
        int n = s.length();

        vector <element> prefix(n);

        for (int i = 0; i < n; i++)
        {
            table[0][i] = s[i] - 'a';
        }

        for (int k = 1; ; k++)
        {
            int len = 1 << (k - 1);
            if (len >= n) break;

            for (int i = 0; i < n; i++)
            {
                prefix[i] = {{table[k - 1][i], table[k - 1][(i + len) % n]}, i};
            }
            sort(prefix.begin(), prefix.end());

            minPrefix = prefix[0].index;

            for (int i = 0; i < n; i++)
            {
                table[k][prefix[i].index] = i > 0 and prefix[i].ranking == prefix[i - 1].ranking ? table[k][prefix[i - 1].index] : i;
            }

            lr = k;
        }
    }

    int& operator [](int i)
    {
        return table[lr][i];
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin>>T;

    for (int test = 0; test < T; test++)
    {
        int sz;
        cin>>sz;

        string s;
        cin>>s;

        suffixArray sa = suffixArray(s);

        cout<<minPrefix<<endl;
    }

    return 0;
}

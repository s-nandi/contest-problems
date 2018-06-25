//kmp prefix function (on string and its reverse), finding/merging partial prefix and suffix matches
//https://codeforces.com/contest/955/problem/D

#include <iostream>
#include <vector>

using namespace std;

const int INF = 1231231234;

vector <int> prefixFunction(string &s)
{
    vector <int> pf(s.length());
    for (int i = 1; i < s.length(); i++)
    {
        int j = pf[i - 1];
        while (j > 0 and s[i] != s[j]) j = pf[j - 1];
        if (s[i] == s[j]) pf[i] = j + 1;
        else pf[i] = 0;
    }
    return pf;
}

vector <int> kmpTable(string &text, string &s, const vector <int> &pfs)
{
    vector <int> table;
    for (int i = 0, j = 0; i < text.length(); i++)
    {
        while (j > 0 and text[i] != s[j]) j = pfs[j - 1];
        if (text[i] == s[j]) ++j;
        table.push_back(j);
    }
    return table;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m, k;
    cin>>n>>m>>k;

    string s, t;
    cin>>s>>t;

    string sRev(s.rbegin(), s.rend()), tRev(t.rbegin(), t.rend());

    vector <int> pf = prefixFunction(t), pfRev = prefixFunction(tRev);
    vector <int> table = kmpTable(s, t, pf), tableRev = kmpTable(sRev, tRev, pfRev);

    vector <int> firstleading(m + 1, INF);
    for (int i = k - 1; i + k - 1 < table.size(); i++)
    {
        int match = table[i];
        firstleading[match] = min(i, firstleading[match]);
    }
    for (int i = firstleading.size() - 1; i > 0; i--)
    {
        int contained = pf[i - 1];
        firstleading[contained] = min(firstleading[contained], firstleading[i]); // suffix of left match can be first occurence of shorter suffix of t
    }

    vector <int> lastending(m + 1, -INF);
    for (int i = k - 1; i + k - 1 < tableRev.size(); i++)
    {
        int match = tableRev[i];
        lastending[match] = max((int) tableRev.size() - i - 1, lastending[match]);
    }
    for (int i = lastending.size() - 1; i > 0; i--)
    {
        int contained = pf[i - 1];
        lastending[contained] = max(lastending[contained], lastending[i]); // prefix of right match can be last occurence of shorter prefix of t
    }

    int lcut = -1, rcut = -1;
    for (int i = 1; i < m; i++)
    {
        if (i > k or m - i > k) continue; // cannot get match greater than k

        int lpos = firstleading[i], rpos = lastending[m - i];
        if (lpos < rpos)
        {
            lcut = lpos - k + 1, rcut = rpos;
            break;
        }
    }

    if (lcut == -1 and rcut == -1)
    {
        if (s.substr(0, k).find(t) != string::npos) // match can be entirely in left cut
        {
            lcut = 0, rcut = k;
        }
        else if(s.substr(s.length() - k, k).find(t) != string::npos) //match can be entirely in right cut
        {
            lcut = 0, rcut = s.length() - k;
        }
        else
        {
            cout<<"No"<<'\n';
        }
    }
    if (lcut != -1 and rcut != -1)
    {
        cout<<"Yes"<<'\n';
        cout<<lcut + 1 <<" "<< rcut + 1<<'\n';
    }

    return 0;
}

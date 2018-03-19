//kmp string matching
//http://www.spoj.com/problems/NHAY/

#include <iostream>
#include <vector>

using namespace std;

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

vector <int> kmpMatch(string &text, string &s, const vector <int> &pfs)
{
    vector <int> matches;
    for (int i = 0, j = 0; i < text.length(); i++)
    {
        while (j > 0 and text[i] != s[j]) j = pfs[j - 1];
        if (text[i] == s[j] and ++j == s.length())
            matches.push_back(i + 1 - s.length());
    }
    return matches;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while (cin>>n)
    {
        string s, t;
        cin>>s>>t;

        for (int i: kmpMatch(t, s, prefixFunction(s)))
        {
            cout<<i<<'\n';
        }
        cout<<'\n';
    }

    return 0;
}

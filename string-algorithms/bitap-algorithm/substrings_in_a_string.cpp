//bitap (with updates), word matching queries
//http://codeforces.com/contest/914/problem/F

#include <iostream>
#include <vector>
#include <array>
#include <bitset>

using namespace std;

const int MAXN = 100001;
const int alpha = 26;

typedef array<bitset<MAXN>, alpha> mask;

int mapping(char c){return c - 'a';}
char invmap(int i){return i + 'a';}

mask buildMask(string &text)
{
    mask mk;
    for (int i = 0; i < text.length(); i++)
    {
        mk[mapping(text[i])][i] = 1;
    }
    return mk;
}

void modifyText(mask &mk, string &text, int p, char c)
{
    mk[mapping(text[p])][p] = 0;
    mk[mapping(c)][p] = 1;
    text[p] = c;
}

int bitapMatch(mask &mk, string &word, int l, int r)
{
    if (l + word.length() - 1 > r) return 0;
    bitset <MAXN> matches = bitset<MAXN>().set();
    for (int i = 0; i < word.length(); i++)
    {
        matches &= mk[word[i] - 'a'] >> i;
        if (matches.none()) return 0;
    }
    return (matches >> l).count() - (matches >> r - word.length() + 2).count();
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string text;
    cin>>text;
    auto mk = buildMask(text);

    int q;
    cin>>q;
    for (int i = 0; i < q; i++)
    {
        int type;
        cin>>type;
        if (type == 1)
        {
            int i; char c;
            cin>>i>>c;
            modifyText(mk, text, --i, c);
        }
        else
        {
            int l, r; string s;
            cin>>l>>r>>s;
            cout<<bitapMatch(mk, s, --l, --r)<<'\n';
        }
    }

    return 0;
}

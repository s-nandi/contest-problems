//bitap, string matching queries
//http://www.spoj.com/problems/STRMATCH/

#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

#define MAXN 3001

string text;
bitset <MAXN> mask[26];

void buildMask()
{
    for (int i = 0; i < text.length(); i++)
    {
        mask[text[i] - 'a'][i] = 1;
    }
}

int bitap(string &word)
{
    bitset <MAXN> matches = bitset<MAXN>().set();
    for (int i = 0; i < word.length(); i++)
    {
        matches &= mask[word[i] - 'a'] >> i;
        if (matches.none()) return 0;
    }
    return matches.count();
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin>>n>>q;
    cin>>text;

    buildMask();

    for (int i = 0; i < q; i++)
    {
        string word;
        cin>>word;
        cout<<bitap(word)<<'\n';
    }

    return 0;
}

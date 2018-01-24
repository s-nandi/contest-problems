//bitap, modifying character updates, word matching queries

#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

#define MAXN 100001

string text;
bitset <MAXN> mask[26];

void buildMask()
{
    for (int i = 0; i < text.length(); i++)
    {
        mask[text[i] - 'a'][i] = 1;
    }
}

void modifyText(int p, char c)
{
    mask[text[p] - 'a'][p] = 0;
    mask[c - 'a'][p] = 1;
    text[p] = c;
}

int bitap(string &word, int l, int r)
{
    if (l + word.length() - 1 > r) return 0;

    bitset <MAXN> matches = bitset<MAXN>().set();
    for (int i = 0; i < word.length(); i++)
    {
        matches &= mask[word[i] - 'a'] >> i;
        if (matches.none()) return 0;
    }
    return (matches >> l).count() - (matches >> r - word.length() + 2).count();
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>text;
    buildMask();

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
            modifyText(--i, c);
        }
        else
        {
            int l, r; string word;
            cin>>l>>r>>word;
            cout<<bitap(word, --l, --r)<<'\n';
        }
    }

    return 0;
}

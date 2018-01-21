//tries, querying # of words with given prefix
//http://codeforces.com/gym/100579

#include <iostream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

struct counts{
    int pc = 0;
};

void addWord(map <pair <char, int>, int> &t, string s, int &nn, map <int, counts> &tc)
{
    int v = 0;
    for (char ch: s)
    {
        if (t.count({ch, v}) == 0)
        {
            t[{ch, v}] = ++nn;
        }
        v = t[{ch, v}];
        tc[v].pc += 1;
    }
}

int searchTill(map <pair<char, int>, int> &t, string s, map <int, counts> &tc)
{
    int v = 0;
    int counter = 0;
    for (char ch: s)
    {
        if (tc[v].pc == 1)
        {
            return counter;
        }
        v = t[{ch, v}];
        counter += 1;
    }
    return counter;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t, n;
    cin>>t;
    for (int loop = 0; loop < t; loop++)
    {
        cin>>n;
        string word;
        map <pair<char, int>, int> trie;
        map <int, counts> totalCounts;
        int numNodes = 0;
        int ans = 0;
        int diff;
        for (int i = 0; i < n; i++)
        {
            cin>>word;
            addWord(trie, word, numNodes, totalCounts);
            diff=searchTill(trie, word, totalCounts);
            ans += diff;
        }

        cout<<"Case #"<<loop + 1<<": "<<ans<<'\n';
    }


    return 0;
}

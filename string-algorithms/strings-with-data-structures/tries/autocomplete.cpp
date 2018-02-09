//tries, querying # of words with given prefix
//http://codeforces.com/gym/100579

#include <iostream>
#include <cstring>

using namespace std;

#define MAXN 1000005

struct trie
{
    int elements[MAXN][26];
    int numNodes;

    trie()
    {
        numNodes = 0;
        memset(elements, -1, sizeof(elements));
    }

    int addWord(string &s)
    {
        int curr = 0;
        int cost = 0;
        bool foundBranch = false;
        for (char c: s)
        {
            if (!foundBranch) cost++;
            if (elements[curr][c - 'a'] == -1)
            {
                elements[curr][c - 'a'] = ++numNodes;
                foundBranch = true;
            }
            curr = elements[curr][c - 'a'];
        }
        return cost;
    }
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int tests, n;
    cin>>tests;
    for (int loop = 1; loop <= tests; loop++)
    {
        cin>>n;

        trie tr;
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            string word;
            cin>>word;
            ans += tr.addWord(word);
        }
        cout<<"Case #"<<loop<<": "<<ans<<'\n';
    }

    return 0;
}

//tries, querying # of words with given prefix
//http://codeforces.com/gym/100579
//2015 facebook hacker cup round 1

#include <iostream>
#include <cstring>

using namespace std;

#define MAXN 1000005
#define alpha 26

int mapping(char c)
{
    return c - 'a';
}

struct node
{
    int to[alpha];

    node()
    {
        memset(to, -1, sizeof(to));
    }
};

struct trie
{
    node elements[MAXN];
    int numNodes = 1;

    int addWord(string &s)
    {
        int curr = 0, cost = 0;
        bool branch = false;
        for (char c: s)
        {
            int mc = mapping(c);
            if (!branch) cost++;
            if (elements[curr].to[mc] == -1)
            {
                elements[curr].to[mc] = numNodes++;
                branch = true;
            }
            curr = elements[curr].to[mc];
        }
        return cost;
    }
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T, n;
    cin>>T;
    for (int test = 1; test <= T; test++)
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
        cout<<"Case #"<<test<<": "<<ans<<'\n';
    }

    return 0;
}

//tries, detecting repeated strings
//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&page=show_problem&problem=1528
//2005 CERC Regional

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

#define MAXN 400001

int mapping(char c)
{
    if (c == 'A') return 0;
    else if(c == 'G') return 1;
    else if (c == 'T') return 2;
    else return 3;
}

struct trie
{
    int elements[MAXN][4];
    int counts[MAXN];
    int numNodes;

    trie()
    {
        numNodes = 0;
        memset(elements, -1, sizeof(elements));
        memset(counts, 0, sizeof(counts));
    }

    void addWord(string &s, vector <int> &tally)
    {
        int curr = 0;
        for (char c: s)
        {
            int mc = mapping(c);
            if (elements[curr][mc] == -1)
            {
                elements[curr][mc] = ++numNodes;
            }
            curr = elements[curr][mc];
        }

        tally[counts[curr]]--;
        tally[++counts[curr]]++;
    }
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    while (true)
    {
        int n, m;
        cin>>n>>m;

        if (n == 0 and m == 0) break;

        trie tr;

        vector <int> tally(n + 1);
        tally[0] = n;

        for (int i = 0; i < n; i++)
        {
            string s;
            cin>>s;

            tr.addWord(s, tally);
        }

        for (int i = 1; i <= n; i++)
        {
            cout<<tally[i]<<'\n';
        }
    }

    return 0;
}

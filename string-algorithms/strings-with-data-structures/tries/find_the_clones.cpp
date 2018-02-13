//tries, detecting repeated strings
//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&page=show_problem&problem=1528
//2005 CERC Regional

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

#define MAXN 400001
#define alpha 4

int mapping(char c)
{
    if (c == 'A') return 0;
    else if(c == 'G') return 1;
    else if (c == 'T') return 2;
    else return 3;
}

struct node
{
    int to[alpha];
    int countEnd;

    node()
    {
        memset(to, -1, sizeof(to));
        countEnd = 0;
    }
};

struct trie
{
    vector <node> elements;
    int numNodes;

    vector <int> tally;

    trie(int numWords)
    {
        elements.resize(MAXN);
        numNodes = 1;

        tally.resize(numWords + 1);
        tally[0] = numWords;
    }

    void addWord(string &s)
    {
        int curr = 0;
        for (char c: s)
        {
            int mc = mapping(c);
            if (elements[curr].to[mc] == -1)
            {
                elements[curr].to[mc] = numNodes++;
            }
            curr = elements[curr].to[mc];
        }

        tally[elements[curr].countEnd]--;
        tally[++elements[curr].countEnd]++;
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

        trie tr(n);

        for (int i = 0; i < n; i++)
        {
            string s;
            cin>>s;

            tr.addWord(s);
        }

        for (int i = 1; i <= n; i++)
        {
            cout<<tr.tally[i]<<'\n';
        }
    }

    return 0;
}

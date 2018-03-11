//binary trie, find maximal xor pairing
//http://codeforces.com/contest/948/problem/D

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int alpha = 2;
const int MAXL = 30;
const int MAXN = 300000 * MAXL + 5;

int mapping(char c)
{
    return c - '0';
}

string toString(int n)
{
    string res = "";
    for (int i = MAXL - 1; i >= 0; i--)
    {
        res += n & (1 << i) ? '1' : '0';
    }
    return res;
}

int toInt(string &s)
{
    int res = 0;
    for (int i = 0; i < MAXL; i++)
    {
        res = (res << 1) + (s[i] - '0');
    }
    return res;
}

struct node
{
    int to[alpha], counts[alpha];

    node()
    {
        memset(to, -1, sizeof(to));
        memset(counts, 0, sizeof(counts));
    }
};

struct trie
{
    vector <node> elements;
    int numNodes;

    trie()
    {
        elements.resize(MAXN);
        numNodes = 1;
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
            elements[curr].counts[mc]++;
            curr = elements[curr].to[mc];
        }
    }

    void removeWord(string &s)
    {
        int curr = 0;
        for (char c: s)
        {
            int mc = mapping(c);
            elements[curr].counts[mc]--;
            curr = elements[curr].to[mc];
        }
    }

    string findMatch(string &s)
    {
        string sol = "";
        int curr = 0;
        for (char c: s)
        {
            int mc = mapping(c);
            if (elements[curr].counts[mc] > 0)
            {
                curr = elements[curr].to[mc];
                sol += '0' + mc;
            }
            else
            {
                curr = elements[curr].to[1 - mc];
                sol += '0' + (1 - mc);
            }
        }
        removeWord(sol);
        return sol;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;

    vector <int> a(n), p(n);

    for (int i = 0; i < n; i++)
    {
        cin>>a[i];
    }

    for (int i = 0; i < n; i++)
    {
        cin>>p[i];
    }

    trie tr;

    for (int i = 0; i < n; i++)
    {
        string s = toString(p[i]);
        tr.addWord(s);
    }

    for (int i = 0; i < n; i++)
    {
        string s = toString(a[i]);
        string match = tr.findMatch(s);
        int res = toInt(match) ^ a[i];
        cout<<res<<" ";
    }
    cout<<'\n';

    return 0;
}

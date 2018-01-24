//rolling hash (rabin-karp), backtrack
//http://codeforces.com/problemset/problem/291/E

#include <iostream>
#include <vector>

using namespace std;

#define ll long long
#define MAXN 1000005

vector <vector <int>> graph;
vector <string> edges;
string currString;
int pos;

vector <ll> mods = {1000000007, 1000000009};
vector <int> alpha = {37, 37};
vector <ll> powAlpha[2];

void precompute()
{
    for (int t = 0; t < 2; t++)
    {
        powAlpha[t].resize(MAXN);
        powAlpha[t][0] = 1;
        for (int i = 1; i < MAXN; i++)
        {
            powAlpha[t][i] = (powAlpha[t][i - 1] * alpha[t]) % mods[t];
            if (powAlpha[t][i] < 0)
            {
                powAlpha[t][i] += mods[t];
            }

        }
    }
}

struct hashString
{
    ll hashVal[2];
    int len;

    hashString()
    {
        len = 0;

        for (int t = 0; t < 2; t++)
        {
            ll curr = 1;
            hashVal[t] = 0;
        }
    }

    void addLast(char c)
    {
        for (int t = 0; t < 2; t++)
        {
            hashVal[t] = (hashVal[t] * alpha[t] + c) % mods[t];
            if (hashVal[t] < 0)
            {
                hashVal[t] += mods[t];
            }

        }
        len++;

    }

    void removeFirst(char c)
    {
        for (int t = 0; t < 2; t++)
        {
            hashVal[t] = (mods[t] + hashVal[t] - powAlpha[t][len - 1] * c) % mods[t];
            if (hashVal[t] < 0)
            {
                hashVal[t] += mods[t];
            }
        }
        len--;
    }

    bool operator == (hashString o)
    {
        return len == o.len and hashVal[0] == o.hashVal[0] and hashVal[1] == o.hashVal[1];
    }
};


int dfs(int curr, hashString h, hashString &s)
{
    int res = 0;
    int backupPos = pos;

    for (char c: edges[curr])
    {
        h.addLast(c);
        currString += c;

        if (h.len == s.len)
        {
            if (h == s)
            {
                res++;
            }
            h.removeFirst(currString[pos]);
            pos++;
        }
    }

    for (int neighbor: graph[curr])
    {
        res += dfs(neighbor, h, s);
    }

    for (int i = 0; i < edges[curr].length(); i++)
    {
        currString.pop_back();
    }
    pos = backupPos;

    return res;
}

int main()
{
    precompute();

    int n;
    cin>>n;

    graph.resize(n);
    edges.resize(n);
    edges[0] = "";

    for (int i = 1; i <= n - 1; i++)
    {
        int p;
        string s;
        cin>>p>>s;
        --p;
        graph[p].push_back(i);
        edges[i] = s;
    }

    string needle;
    cin>>needle;

    hashString s;
    for (char c: needle)
    {
        s.addLast(c);
    }

    hashString h;

    cout<<dfs(0, h, s)<<'\n';

    return 0;

}

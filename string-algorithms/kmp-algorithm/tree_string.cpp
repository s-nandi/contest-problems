//kmp automata, dfs - string matching on graph
//http://codeforces.com/contest/291/problem/E

#include <iostream>
#include <vector>

using namespace std;

const int alpha = 26;

struct edge{int to; string str;};
typedef vector <vector<edge>> graph;

vector <int> prefixFunction(string &s)
{
    vector <int> pf(s.length());
    for (int i = 1; i < s.length(); i++)
    {
        int j = pf[i - 1];
        while (j > 0 and s[i] != s[j]) j = pf[j - 1];
        if (s[i] == s[j]) pf[i] = j + 1;
        else pf[i] = 0;
    }
    return pf;
}

int mapping(char c){return c - 'a';}
char invmap(int i){return i + 'a';}

vector <vector<int>> kmpAutomata(string &s)
{
    int n = s.length();
    auto pf = prefixFunction(s);
    vector <vector<int>> automata(n + 1, vector<int>(alpha));
    for (int i = 0; i <= n; i++) for (int c = 0; c < alpha; c++)
    {
        if (i > 0 and invmap(c) != s[i]) automata[i][c] = automata[pf[i - 1]][c];
        else automata[i][c] = i + (invmap(c) == s[i]);
    }
    return automata;
}

int target;
int dfs(graph &g, int curr, vector<vector<int>> &automata, int state)
{
    int sol = 0;
    for (edge e: g[curr])
    {
        int st = state;
        for (char c: e.str)
        {
            st = automata[st][mapping(c)];
            if (st == target) sol++;
        }
        sol += dfs(g, e.to, automata, st);
    }
    return sol;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;

    graph g(n);
    for (int i = 1; i < n; i++)
    {
        int a; string s;
        cin>>a>>s;
        g[--a].push_back({i, s});
    }
    string t;
    cin>>t;

    target = t.length();
    auto automata = kmpAutomata(t);

    cout<<dfs(g, 0, automata, 0)<<'\n';

    return 0;
}

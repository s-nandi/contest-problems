//aho corasick (find first match - can't just pick earliest state, length matters), bucketing to reduce memory usage
//http://acm.timus.ru/problem.aspx?space=1&num=1269

#include <bits/stdc++.h>

using namespace std;

const int INF = 1231231234;

struct node
{
    map <int, int> next;
    int terminalIdx = -1, prefixLink = -1, matchLink = -1;
    int par, pch, len, longestMatch = -1;

    node(int p = -1, int ch = '$', int l = 0) : par(p), pch(ch), len(l) {}
};

struct ahoCorasick
{
    int sz;
    vector <node> elements;

    ahoCorasick(){sz = 1, elements.resize(1);}

    int mapping(unsigned char c){return c;}
    int next(int v, int t){return elements[v].next.count(t) ? elements[v].next[t] : -1;}

    void addWord(string const &s, int idx = -2)
    {
        int v = 0;
        for (char ch : s)
        {
            int c = mapping(ch);
            if (next(v, c) == -1)
            {
                elements[v].next[c] = sz++;
                elements.emplace_back(v, c, elements[v].len + 1);
            }
            v = next(v, c);
        }
        elements[v].terminalIdx = idx;
    }

    int getLink(int v)
    {
        if (elements[v].prefixLink == -1)
        {
            elements[v].prefixLink = elements[v].par <= 0 ? 0 : nextState(getLink(elements[v].par), elements[v].pch);
            getLink(elements[v].prefixLink);

            int link = elements[v].prefixLink;
            elements[v].matchLink = (elements[link].terminalIdx != -1) ? link: elements[link].matchLink;
        }
        return elements[v].prefixLink;
    }

    int nextState(int v, int c)
    {
        if (next(v, c) != -1)
            return next(v, c);
        else
            return v == 0 ? 0 : nextState(getLink(v), c);
    }

    int findLongestMatch(int v)
    {
        if (elements[v].longestMatch == -1)
        {
            getLink(v);
            elements[v].longestMatch = elements[v].terminalIdx != -1 ? elements[v].len : 0;
            elements[v].longestMatch = max(elements[v].longestMatch, elements[v].matchLink != -1 ? findLongestMatch(elements[v].matchLink) : 0);
        }
        return elements[v].longestMatch;
    }

    int findFirstMatch(const string &s)
    {
        int res = INF;
        for (int i = 0, state = 0; i < s.length(); i++)
        {
            state = nextState(state, mapping(s[i]));
            if (findLongestMatch(state) != 0)
                res = min(res, i - findLongestMatch(state) + 1);
        }
        return res;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;
    cin.ignore();

    vector <string> s(n);
    for (int i = 0; i < n; i++)
    {
        getline(cin, s[i]);
    }

    int m;
    cin>>m;
    cin.ignore();

    vector <string> lines(m);
    for (int i = 0; i < m; i++) getline(cin, lines[i]);

    int buckets = 2;
    pair <int, int> best = {INF, INF};
    vector <pair <int, int>> sol(buckets, {INF, INF});
    for (int t = 0; t < buckets; t++)
    {
        ahoCorasick ac;

        for (int i = t; i < n; i += buckets)
            ac.addWord(s[i]);

        for (int i = 0; i < m; i++)
        {
            int res = ac.findFirstMatch(lines[i]);
            if (res != INF)
            {
                sol[t] = {i + 1, res + 1};
                break;
            }
        }
        best = min(best, sol[t]);
    }

    if (best.first != INF) cout<<best.first<<" "<<best.second<<'\n';
    else cout<<"Passed"<<'\n';
}

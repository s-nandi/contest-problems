// dp with aho-corasick (dp on digits style), feed characters into automata states
// https://codeforces.com/gym/101174 (problem E)
// 2016 Southwest European Regional

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2000;
const int MAXS = 20;
const int MOD = 1000003;

const int alpha = 256;
struct node
{
    map <int, int> next; // PS: next/go can be any combination of map/array
    array <int, alpha> go;
    int terminalIdx = -1, prefixLink = -1, matchLink = -1; // iff terminalIdx != -1, it denotes the index of the string ending at this node
    int par, pch;

    node(int p = -1, int ch = -1) : par(p), pch(ch) {fill(go.begin(), go.end(), -1);}
};

struct ahoCorasick
{
    int sz;
    vector <node> elements;

    ahoCorasick(){sz = 1, elements.resize(1);}

    int mapping(unsigned char c){return c;}
    int next(int v, int t){return elements[v].next.count(t) ? elements[v].next[t] : -1;}
    int go(int v, int t){return elements[v].go[t];}

    void addWord(string const &s, int idx = -2)
    {
        int v = 0;
        for (char ch : s)
        {
            int c = mapping(ch);
            if (next(v, c) == -1)
            {
                elements[v].next[c] = sz++;
                elements.emplace_back(v, c);
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
        if (go(v, c) == -1)
        {
            if (next(v, c) != -1)
                elements[v].go[c] = next(v, c);
            else
                elements[v].go[c] = v == 0 ? 0 : nextState(getLink(v), c);
        }
        return go(v, c);
    }

    bool isTerminal(int v)
    {
        getLink(v);
        return elements[v].terminalIdx != -1 or (elements[v].matchLink != -1 and isTerminal(elements[v].matchLink));
    }
};

int dp[MAXS + 5][MAXN + 5][2][2][2]; // dp[len][aho corasick state][has lower][has upper][has digit]

map <char, char> leet = {{'0', 'o'}, {'1', 'i'}, {'3', 'e'}, {'5', 's'}, {'7', 't'}};
char canonical(char c)
{
    if (isalpha(c))
        return tolower(c);
    else
        return leet.count(c) ? leet[c] : c;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int a, b, n;
    cin >> a >> b >> n;

    ahoCorasick ac;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        ac.addWord(s);
    }

    memset(dp, 0, sizeof dp);
    dp[0][0][0][0][0] = 1;

    for (int i = 0; i < b; i++)
    {
        for (int state = 0; state < ac.sz; state++)
        {
            for (int hasLower = 0; hasLower < 2; hasLower++)
            {
                for (int hasUpper = 0; hasUpper < 2; hasUpper++)
                {
                    for (int hasDigit = 0; hasDigit < 2; hasDigit++)
                    {
                        for (int ch = 0; ch < 128; ch++)
                        {
                            char c = ch;
                            if (!isalnum(c))
                                continue;

                            int resState = ac.nextState(state, ac.mapping(canonical(c)));
                            bool resLower = hasLower or islower(c);
                            bool resUpper = hasUpper or isupper(c);
                            bool resDigit = hasDigit or isdigit(c);

                            if (ac.isTerminal(resState))
                                continue;

                            dp[i + 1][resState][resLower][resUpper][resDigit] += dp[i][state][hasLower][hasUpper][hasDigit];
                            dp[i + 1][resState][resLower][resUpper][resDigit] %= MOD;
                        }
                    }
                }
            }
        }
    }

    int sol = 0;
    for (int i = a; i <= b; i++)
    {
        for (int state = 0; state < ac.sz; state++)
        {
            sol += dp[i][state][1][1][1];
            sol %= MOD;
        }
    }
    cout << sol << '\n';
}

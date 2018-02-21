//suffix automata, finding longest common substring of two strings
//http://www.spoj.com/problems/LCS/

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

#define ll long long
#define MAXN 250001

const int alpha = 26;

int mapping(unsigned char c)
{
    return c - 'a';
}

struct node
{
    int to[alpha];
    int len, suffixLink;

    node()
    {
        memset(to, -1, sizeof(to));
        len = 0, suffixLink = 0;
    }
};

struct suffixAutomata
{
    vector <node> elements;
    int last, numNodes;

    vector <int> numSubstr;

    suffixAutomata()
    {
        last = 0, numNodes = 1;
        elements.resize(2 * MAXN);
        elements[0].suffixLink = -1;
    }

    suffixAutomata(string &s) : suffixAutomata()
    {
        for (char c: s) addChar(c);
    }

    void addChar(char c)
    {
        int mc = mapping(c);
        int curr = numNodes++;
        elements[curr].len = elements[last].len + 1;

        for (int p = last; p != -1; p = elements[p].suffixLink)
        {
            int q = next(p, mc);
            if (q != -1)
            {
                if (elements[p].len + 1 == elements[q].len)
                {
                    elements[curr].suffixLink = q;
                }
                else
                {
                    int q2 = numNodes++;
                    elements[q2] = elements[q];
                    elements[q2].len = elements[p].len + 1;

                    elements[q].suffixLink = q2, elements[curr].suffixLink = q2;
                    for (int p2 = p; p2 != -1 and next(p2, mc) == q; p2 = elements[p2].suffixLink)
                    {
                        elements[p2].to[mc] = q2;
                    }
                }
                break;
            }
            else
            {
                elements[p].to[mc] = curr;
            }
        }
        last = curr;
    }

    int next(int curr, int transition)
    {
        return elements[curr].to[transition];
    }

    string longestCommonSubstring(string &s)
    {
        int curr = 0, len = 0;
        pair <int, int> sol = {0, 0}; //longest, pos
        for (int i = 0; i < s.length(); i++)
        {
            int mc = mapping(s[i]);
            while (curr != -1 and next(curr, mc) == -1)
            {
                curr = elements[curr].suffixLink;
                len = curr != -1 ? elements[curr].len : 0;
            }
            if (curr != -1)
            {
                if (++len > sol.first) sol.first = len, sol.second = i;
                curr = next(curr, mc);
            }
            if (curr == -1) curr = 0;
        }
        return s.substr(sol.second - sol.first + 1, sol.first);
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin>>s;

    suffixAutomata su(s);

    string t;
    cin>>t;

    cout<<(su.longestCommonSubstring(t)).length()<<'\n';

    return 0;
}

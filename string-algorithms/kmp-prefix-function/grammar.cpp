//kmp automaton (recursive string), big integer (adding)
//http://acm.sgu.ru/problem.php?contest=0&problem=284

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

typedef vector<int> bigInt;
const int base = 10;

void Print(bigInt a)
{
    if (a.size() == 0) cout<<0;
    else for (int i = a.size() - 1; i >= 0; i--) cout<<a[i];
}

bigInt Integer(int x)
{
    bigInt res;
    while (x)
    {
        res.push_back(x % base);
        x /= base;
    }
    return res;
}

bigInt operator + (bigInt a, bigInt b)
{
    bigInt res;
    int carry = 0;
    for (int i = 0; i < max(a.size(), b.size()); i++)
    {
        if (i < a.size()) carry += a[i];
        if (i < b.size()) carry += b[i];
        res.push_back(carry % base);
        carry /= base;
    }
    if (carry) res.push_back(carry);
    return res;
}

const int alpha = 2;

vector <int> prefixFunction(string &s)
{
    int n = s.length();
    vector <int> pf(n);

    for (int i = 1; i < n; i++)
    {
        int j = pf[i - 1];
        while (j > 0 and s[i] != s[j])
        {
            j = pf[j - 1];
        }
        if (s[i] == s[j]) pf[i] = j + 1;
        else pf[i] = 0;
    }

    return pf;
}

vector <vector<int>> kmpAutomata(string &s)
{
    int n = s.length();
    auto pf = prefixFunction(s);

    vector <vector<int>> automata(n + 1, vector<int>(alpha));

    for (int i = 0; i <= n; i++)
    {
        for (int c = 0; c < alpha; c++)
        {
            if (i > 0 and c + 'a' != s[i])
            {
                automata[i][c] = automata[pf[i - 1]][c];
            }
            else
            {
                automata[i][c] = i + (c + 'a' == s[i]);
            }
        }
    }

    return automata;
}

bigInt recursiveAutomata(string &s, vector <vector<int>> &rule)
{
    int n = s.length(), m = rule.size();
    auto automata = kmpAutomata(s);

    vector <vector<int>> ruleAutomata(n + 1, vector<int>(m));
    vector <vector<bigInt>> ruleValue(n + 1, vector<bigInt>(m));

    for (int c = 0; c < m; c++)
    {
        for (int i = 0; i <= n; i++)
        {
            int state = i;
            bigInt value = Integer(0);
            for (int event: rule[c])
            {
                if (event < alpha)
                {
                    state = automata[state][event];
                    if (state == n) value = value + Integer(1);
                }
                else
                {
                    event -= alpha;
                    value = value + ruleValue[state][event];
                    state = ruleAutomata[state][event];
                }
            }
            ruleAutomata[i][c] = state;
            ruleValue[i][c] = value;
        }
    }

    return ruleValue[0][m - 1];
}

int mapping(string &event)
{
    if (event.size() == 1 and (event[0] == 'a' or event[0] == 'b'))
    {
        return event[0] - 'a';
    }
    else
    {
        int res;
        istringstream iss(event);
        iss >> res;
        return res - 1 + alpha;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;

    string s;
    cin>>s;

    vector <vector<int>> rule(n);

    for (int i = 0; i < n; i++)
    {
        int numElements;
        cin>>numElements;

        for (int j = 0; j < numElements; j++)
        {
            string event;
            cin>>event;

            rule[i].push_back(mapping(event));
        }
    }

    Print(recursiveAutomata(s, rule)); cout<<'\n';

    return 0;
}

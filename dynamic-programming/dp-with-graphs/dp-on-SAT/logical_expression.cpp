//dp on satisfiability, dijkstra, bitmask
//http://codeforces.com/contest/913/problem/E

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

#define INF 1231231234

struct expression
{
    string s;
    int type;
    int mask;

    int length() const { return s.length() != 0 ? s.length() : INF;}

    bool operator > (expression o) const
    {
        if (length() != o.length()) return length() > o.length();
        else return tie(s, type, mask) > tie(o.s, o.type, o.mask);
    }

    bool operator < (expression o) const
    {
        return o > *this;
    }

    expression AND (expression o) { return {s + "&" + o.s, 1, mask & o.mask}; }
    expression OR (expression o) { return {s + "|" + o.s, 2, mask | o.mask}; }
    expression NOT () { return {"!" + s, 0, ((1 << 8) - 1) & (~mask)}; }
    expression BRACKET () { return {"(" + s + ")", 0, mask}; }
    expression MOVEUP (){ return {s, type + 1, mask}; }
};

vector <vector<expression>> dp(3, vector<expression>(1 << 8, {"", -1, -1}));
vector <expression> marked[3];

priority_queue <expression, vector<expression>, greater<expression>> pq;

void addExpression(expression e)
{
    if (e < dp[e.type][e.mask])
    {
        dp[e.type][e.mask] = e;
        pq.push(e);
    }
}

int mapping(string s)
{
    int val = 0;
    for (int i = 0; i < 8; i++)
    {
        val += (s[i] - '0') * (1 << i);
    }
    return val;
}

void dijkstra()
{
    addExpression({"x", 0, mapping("00001111")});
    addExpression({"y", 0, mapping("00110011")});
    addExpression({"z", 0, mapping("01010101")});

    while (!pq.empty())
    {
        expression curr = pq.top();
        pq.pop();

        if (curr > dp[curr.type][curr.mask]) continue;
        marked[curr.type].push_back(curr);

        if (curr.type == 0) //F
        {
            addExpression(curr.NOT());
            addExpression(curr.MOVEUP());
            for (expression e: marked[1])
            {
                addExpression(e.AND(curr));
            }
        }
        else if(curr.type == 1) //T
        {
            addExpression(curr.MOVEUP());
            for (expression e: marked[0])
            {
                addExpression(curr.AND(e));
            }
            for (expression e: marked[2])
            {
                addExpression(e.OR(curr));
            }
        }
        else //E
        {
            addExpression(curr.BRACKET());
            for (expression e: marked[1])
            {
                addExpression(curr.OR(e));
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;

    dijkstra();
    for (int i = 0; i < n; i++)
    {
        string str;
        cin>>str;
        cout<<dp[2][mapping(str)].s<<'\n';
    }

    return 0;
}

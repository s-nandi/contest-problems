//dp on satisfiability, bfs, hashing
//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&page=show_problem&problem=5948
//2016 South Pacific Regional

#include <iostream>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

vector <vector<int>> BIT_AND = {{0, 0, 0}, {0, 1, 1}, {0, 1, 2}};
vector <vector<int>> BIT_OR = {{0, 1, 2}, {1, 1, 2}, {2, 2, 2}};
vector <vector<int>> BIT_IMPLIES = {{2, 2, 2}, {1, 2, 2}, {0, 1, 2}};
vector <vector<int>> BIT_EQUALS = {{2, 0, 0}, {0, 2, 0}, {0, 0, 2}};

int XVAL[9] = {0, 0, 0, 1, 1, 1, 2, 2, 2};
int YVAL[9] = {0, 1, 2, 0, 1, 2, 0, 1, 2};

int chToInt(char c)
{
    if (c == 'F') return 0;
    else if (c == 'U') return 1;
    else return 2;
}

struct expression
{
    int bits[9];

    int hashing()
    {
        int val = 0;
        for (int i = 0; i < 9; i++)
        {
            val = 3 * val + bits[i];
        }
        return val;
    }

    expression OPERATION(vector <vector<int>> &BIT_OP, expression &o)
    {
        expression res;
        for (int i = 0; i < 9; i++)
        {
            res.bits[i] = BIT_OP[bits[i]][o.bits[i]];
        }
        return res;
    }

    expression AND (expression &o) { return OPERATION(BIT_AND, o); }
    expression OR (expression &o) { return OPERATION(BIT_OR, o); }
    expression IMPLIES (expression &o) { return OPERATION(BIT_IMPLIES, o); }
    expression EQUALS (expression &o) { return OPERATION(BIT_EQUALS, o); }
};

vector <expression> setExpressions;
vector <bool> visited(19683);
queue <expression> q;

void addExpression(expression e)
{
    int h = e.hashing();
    if (!visited[h])
    {
        visited[h] = true;
        q.push(e);
    }
}

void bfs()
{
    expression X, Y;
    memcpy(X.bits, XVAL, sizeof(XVAL));
    memcpy(Y.bits, YVAL, sizeof(YVAL));
    addExpression(X);
    addExpression(Y);

    while(!q.empty())
    {
        expression curr = q.front();
        q.pop();

        setExpressions.push_back(curr);

        for (expression e: setExpressions)
        {
            addExpression(curr.AND(e));
            addExpression(curr.OR(e));
            addExpression(curr.IMPLIES(e));
            addExpression(e.IMPLIES(curr));
            addExpression(e.EQUALS(curr));
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    bfs();

    int n;
    while(cin>>n)
    {
        for (int i = 0; i < n; i++)
        {
            int query = 0;
            for (int j = 0; j < 9; j++)
            {
                char c;
                cin>>c;
                query = 3 * query + chToInt(c);
            }

            if (visited[query])
            {
                cout<<"definable"<<'\n';
            }
            else
            {
                cout<<"undefinable"<<'\n';
            }
        }
    }

    return 0;
}

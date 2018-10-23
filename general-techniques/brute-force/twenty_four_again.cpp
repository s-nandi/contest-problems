// expression parsing (mult, div, add, sub), generating permutations while keeping track of inversions, enumerating paranthesizations of expression, backtracking
// https://open.kattis.com/problems/twentyfour
// 2017 East Central NA Regional

#include <bits/stdc++.h>

using namespace std;

char op[4] = {'*', '+', '/', '-'};
const int INF = 1031231234;
const int TARGET = 24;

int result(int lhs, int rhs, char op)
{
    switch(op)
    {
        case '*':
            return lhs * rhs;
        case '/':
            return (rhs != 0 and lhs % rhs == 0) ? lhs / rhs : INF;
        case '+':
            return lhs + rhs;
        case '-':
            return lhs - rhs;
    }
    assert(false);
}

int evaluate(vector <int> v, vector <char> o)
{
    vector <char> op2;
    for (int i = 0, j = 0; i < o.size(); i++)
    {
        if (o[i] == '*' or o[i] == '/')
        {
            v[j] = result(v[j], v[j + 1], o[i]);
            if (v[j] == INF)
                return INF;
            v.erase(v.begin() + j + 1);
        }
        else
        {
            op2.push_back(o[i]);
            j++;
        }
    }

    int res = v[0];
    for (int i = 0; i < op2.size(); i++)
        res = result(res, v[i + 1], op2[i]);
    return res;
}

int grouping(vector <int> values, vector <char> ops, int cost = 0)
{
    if (evaluate(values, ops) == TARGET)
        return cost;
    else if(ops.size() == 1)
        return INF;
    else
    {
        int best = INF;
        for (int i = 0; i <= values.size(); i++)
        {
            for (int j = 0; j <= values.size(); j++) if (j - i < values.size() and j - i >= 2)
            {
                vector <int> evalFirst(values.begin() + i, values.begin() + j);
                vector <char> opFirst(ops.begin() + i, ops.begin() + j - 1);
                int e = evaluate(evalFirst, opFirst);
                if (e == INF)
                    continue;

                vector <int> newv;
                vector <char> newo;
                for (int i2 = 0; i2 < i; i2++)
                {
                    newv.push_back(values[i2]);
                    newo.push_back(ops[i2]);
                }
                newv.push_back(e);
                for(int i2 = j; i2 < values.size(); i2++)
                {
                    newv.push_back(values[i2]);
                    newo.push_back(ops[i2 - 1]);
                }
                int possible = grouping(newv, newo, cost + 1);
                best = min(best, possible);
            }
        }
        return best;
    }
}

int solve(vector <int> &values, vector <char> &ops)
{
    int res = INF;
    if (ops.size() == values.size() - 1)
        res = min(res, grouping(values, ops));
    else
    {
        for (int i = 0; i < 4; i++)
        {
            ops.push_back(op[i]);
            res = min(res, solve(values, ops));
            ops.pop_back();
        }
    }
    return res;
}

typedef vector<pair<vector<int>, int>> permutations;
permutations orderings(vector <int> &values)
{
    if (values.size() == 1)
        return {{{values[0]}, 0}};

    permutations result;
    vector <int> exclude(values.begin() + 1, values.end());
    auto rem = orderings(exclude);
    for (auto permutation: rem)
    {
        for (int i = 0; i <= permutation.first.size(); i++)
        {
            auto nw = permutation.first;
            nw.insert(nw.begin() + i, values[0]);
            result.push_back({nw, permutation.second + i});
        }
    }
    return result;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    vector <int> values(4);
    for (int i = 0; i < 4; i++)
    {
        cin >> values[i];
    }

    int best = INF;
    for (auto permutation: orderings(values))
    {
        vector <char> op;
        int parenthesisCost = solve(permutation.first, op);
        int possible = parenthesisCost + 2 * permutation.second;
        best = min(best, possible);
    }

    if (best == INF)
        cout << "impossible" << '\n';
    else
        cout << best << '\n';
}

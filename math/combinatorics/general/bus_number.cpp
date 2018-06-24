//combinatorics (combinations with repeated elements), permutation generator
//http://codeforces.com/contest/991/problem/E

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

vector <ll> fac;
vector <int> validpos;

void getFactorial(int to)
{
    fac.resize(to + 1);
    fac[0] = 1LL;
    for (int i = 1; i <= to; i++)
    {
        fac[i] = fac[i - 1] * (ll) i;
    }
}

bool getNext(vector <int> &curr, vector <int> &lim, int &pos)
{
    if (curr[pos] < lim[pos])
    {
        curr[pos]++;
    }
    else if(pos == validpos.back())
    {
        return false;
    }
    else
    {
        auto nextit = upper_bound(validpos.begin(), validpos.end(), pos);
        if (nextit == validpos.end()) return false;

        int nextpos = *nextit;
        for (int p: validpos)
        {
            if (p >= nextpos) break;
            curr[p] = 1;
        }
        if (curr[nextpos] < lim[nextpos])
        {
            curr[nextpos]++;
            pos = validpos[0];
        }
        else
        {
            pos = nextpos;
            return getNext(curr, lim, pos);
        }
    }

    return true;
}

ll solve(vector <int> &curr, vector <int> &lim, bool checkleading = true)
{
    ll leadingzero = 0;
    if (checkleading and curr[0] > 0)
    {
        vector <int> without(curr);
        without[0]--;
        leadingzero = solve(without, lim, false);
    }
    int total = 0;
    ll denom = 1LL;
    for (int i = 0; i < curr.size(); i++)
    {
        total += curr[i];
        denom *= fac[curr[i]];
    }
    ll res = fac[total] / denom - leadingzero;
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getFactorial(19);
    string n;
    cin>>n;

    vector <int> lim(10);
    for (char c: n)
    {
        lim[c - '0']++;
    }

    for (int i = 0; i < 10; i++)
    {
        if (lim[i] > 0)
        {
            validpos.push_back(i);
        }
    }

    vector <int> curr(10);
    for (int p: validpos)
    {
        curr[p] = 1;
    }

    ll sol = 0;
    int pos = 0;

    while (true)
    {
        sol += solve(curr, lim);
        if (!getNext(curr, lim, pos)) break;
    }
    cout<<sol<<'\n';

    return 0;
}

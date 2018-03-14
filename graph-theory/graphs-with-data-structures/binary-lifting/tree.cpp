//online binary lift, getting maximum and sum along lifts
//http://codeforces.com/contest/932/problem/D

#include <iostream>
#include <vector>

using namespace std;

#define ll long long

const ll INF = 123123123123123123;
const int MAXN = 400001;

vector <int> values;

struct binaryLift
{
    int sz, h = 0;
    vector <vector<int>> table;
    vector <vector<ll>> sums;

    binaryLift(int s)
    {
        sz = s, calcHeight(), table.resize(sz, vector<int>(h, -1));
        sums.resize(sz, vector<ll>(h, 0));
    }
    void calcHeight(){while (1 << h < sz) h++;}

    void addEdge(int par, int curr, ll weight)
    {
        int link;
        if (values[par] >= weight) link = par;
        else
        {
            link = par;
            for (int i = h - 1; i >= 0; i--) if (table[link][i] != -1)
            {
                if (values[table[link][i]] < weight)
                {
                    link = table[link][i];
                }
            }
            link = table[link][0];
        }

        table[curr][0] = link;
        if (link != -1) sums[curr][0] = values[link];

        for (int i = 1; i < h; i++) if (table[curr][i - 1] != -1)
        {
            table[curr][i] = table[table[curr][i - 1]][i - 1];
            sums[curr][i] = sums[curr][i - 1] + sums[table[curr][i - 1]][i - 1];
        }
    }

    int query(int curr, ll limit)
    {
        if (values[curr] > limit) return 0;

        ll amt = values[curr];
        int dist = 1;
        for (int i = h - 1; i >= 0; i--) if (table[curr][i] != -1)
        {
            if (amt + sums[curr][i] <= limit)
            {
                amt += sums[curr][i];
                curr = table[curr][i];
                dist += (1 << i);
            }
        }
        return dist;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    binaryLift bl(MAXN);
    values.resize(MAXN);

    int q;
    cin>>q;

    ll last = 0;
    int numNodes = 1;
    for (int i =  0; i < q; i++)
    {
        int type;
        ll p, q;
        cin>>type>>p>>q;

        p ^= last, q ^= last;
        --p;

        if (type == 1)
        {
            values[numNodes] = q;
            bl.addEdge(p, numNodes, q);
            numNodes++;
        }
        else
        {
            last = bl.query(p, q);
            cout<<last<<'\n';
        }
    }

    return 0;
}

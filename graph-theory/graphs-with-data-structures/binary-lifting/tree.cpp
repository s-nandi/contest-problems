//binary lift, storing maximum and sum along lifts
//http://codeforces.com/contest/932/problem/D

#include <iostream>
#include <vector>

using namespace std;

#define ll long long
#define MAXN 400001

const ll INF = 123123123123123123;

vector <int> values;

struct binaryLift
{
    int sz, h = 0, type;
    vector <vector<int>> table; vector <vector<ll>> acc;

    binaryLift(int s, int t)
    {
        sz = s, type = t;
        while (1 << h < sz) h++;

        table.resize(sz, vector<int>(h, -1)), acc.resize(sz, vector<ll>(h, type == 0 ? 0 : INF));
    }

    void addEdge(int p, int c, ll w)
    {
        if (p == -1) return;

        table[c][0] = p;
        acc[c][0] = values[p];

        for (int i = 1; i < h; i++)
        {
            table[c][i] = table[c][i - 1] != -1 ? table[table[c][i - 1]][i - 1] : -1;
            if (table[c][i] != -1)
            {
                if (type == 0) acc[c][i] = max(acc[c][i - 1], acc[table[c][i - 1]][i - 1]);
                else acc[c][i] = acc[c][i - 1] + acc[table[c][i - 1]][i - 1];
            }
        }
    }

    int query(int curr, ll limit)
    {
        if (type == 0)
        {
            for (int i = h - 1; i >= 0; i--)
            {
                if (table[curr][i] != -1 and acc[curr][i] < limit)
                {
                    curr = table[curr][i];
                }
            }
            return table[curr][0];
        }
        else
        {
            if (values[curr] > limit) return 0;

            ll amt = values[curr];
            int dist = 0;
            for (int i = h - 1; i >= 0; i--)
            {
                if (table[curr][i] != -1 and amt + acc[curr][i] <= limit)
                {
                    amt += acc[curr][i];
                    curr = table[curr][i];
                    dist += (1 << i);
                }
            }
            return dist + 1;
        }
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    binaryLift bl[2] = {binaryLift(MAXN, 0), binaryLift(MAXN, 1)};
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
            bl[0].addEdge(p, numNodes, q);
            bl[1].addEdge(bl[0].query(numNodes, q), numNodes, q);
            numNodes++;
        }
        else
        {
            last = bl[1].query(p, q);
            cout<<last<<'\n';
        }
    }

    return 0;
}

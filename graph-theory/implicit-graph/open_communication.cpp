//implicit graph construction
//http://codeforces.com/contest/994/problem/D

#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct edge {int to, common = -1;};
typedef vector<vector<edge>> graph;

typedef pair<int, int> ii;
typedef vector<int> vi;

struct node
{
    pair <int, int> transmit;
    int index;

    node(){}
    node(int a, int b, int ind)
    {
        transmit.first = min(a, b);
        transmit.second = max(a, b);
        index = ind;
    }

    int hasCommon(const node &o)
    {
        if (transmit == o.transmit) return -1;
        else if(transmit.first == o.transmit.first or transmit.first == o.transmit.second) return transmit.first;
        else if(transmit.second == o.transmit.second or transmit.second == o.transmit.first) return transmit.second;
        else return -1;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin>>n>>m;

    vector <node> nodesA(n), nodesB(m);
    for(int i = 0; i < n; i++)
    {
        int a, b;
        cin>>a>>b;
        nodesA[i] = {a, b, i};
    }
    for(int i = 0; i < m; i++)
    {
        int a, b;
        cin>>a>>b;
        nodesB[i] = {a, b, (i + n)};
    }
    int total = n + m;
    graph g(total);
    set <int> possible;
    for (int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            int ind1 = nodesA[i].index, ind2 = nodesB[j].index;
            int com = nodesA[i].hasCommon(nodesB[j]);
            if (com != -1)
            {
                g[ind1].push_back({ind2, com});
                g[ind2].push_back({ind1, com});
                possible.insert(com);
            }
        }
    }

    if (possible.size() == 1)
    {
        cout<<*possible.begin()<<'\n';
    }
    else
    {
        bool branch = false;
        for (int i = 0; i < total; i++)
        {
            set <int> possibleChild;
            for (edge e: g[i])
            {
                possibleChild.insert(e.common);
            }
            if (possibleChild.size() > 1)
            {
                branch = true;
                break;
            }
        }
        if (branch)
        {
            cout<<-1<<'\n';
        }
        else
        {
            cout<<0<<'\n';
        }
    }

    return 0;
}

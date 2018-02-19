//detecting and finding euler tour
//http://www.spoj.com/problems/WORDS1/

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

struct edge
{
    int to, id;
};

typedef vector<vector<edge>> graph;

void dfs(graph &g, int curr, vector <bool> &used, deque <int> &tour)
{
    for (edge e: g[curr]) if (!used[e.id])
    {
        used[e.id] = true;
        dfs(g, e.to, used, tour);
    }
    tour.push_front(curr);
}

deque <int> eulerTour(graph &g, int start, int m)
{
    vector <bool> used(m);
    deque <int> tour;
    dfs(g, start, used, tour);
    return tour;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin>>T;

    while(T--)
    {
        int n;
        cin>>n;

        graph g(26);
        vector <int> inDegree(26), outDegree(26);

        for (int i = 0; i < n; i++)
        {
            string s;
            cin>>s;

            int in = s[0] - 'a', out = s[s.length() - 1] - 'a';
            g[in].push_back({out, i});
            inDegree[out]++, outDegree[in]++;
        }

        bool fail = false;
        int numDiff = 0, start = -1;
        for (int i = 0; i < 26; i++)
        {
            int diff = inDegree[i] - outDegree[i];
            if (diff != 0)
            {
                if (diff == 1 or diff == -1)
                {
                    numDiff++;
                    if (diff == -1) start = i;
                }
                else
                {
                    fail = true;
                    break;
                }
            }
            else if(start == -1)
            {
                start = i;
            }
        }

        if (numDiff != 2 and numDiff != 0)
        {
            fail = true;
        }

        if (fail)
        {
            cout<<"The door cannot be opened."<<'\n';
            continue;
        }

        auto tour = eulerTour(g, start, n);

        if (tour.size() == n + 1)
        {
            cout<<"Ordering is possible."<<'\n';
        }
        else
        {
            cout<<"The door cannot be opened."<<'\n';
        }
    }

    return 0;
}

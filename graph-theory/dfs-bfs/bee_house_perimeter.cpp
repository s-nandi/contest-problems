// dfs (finding perimeter w/ flood fill + counting outer to inner edges)
// https://open.kattis.com/problems/beehouseperimeter
// 2018 Singapore Preliminary

#include <iostream>
#include <vector>

using namespace std;

struct edge{int to;};
typedef vector<vector<edge>> graph;

vector <int> dx = {0, -1, -1, 0, 1, 1};
vector <int> dy_top = {-1, -1, 0, 1, 1, 0};
vector <int> dy_mid = {-1, -1, 0, 1, 0, -1};
vector <int> dy_bottom = {-1, 0, 1, 1, 0, -1};

void dfs(graph &g, int curr, vector <int> &outer, vector <bool> &house)
{
    if (outer[curr])
        return;
    outer[curr] = true;
    for (edge e: g[curr]) if (!house[e.to])
        dfs(g, e.to, outer, house);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int r, k;
    cin>>r>>k;

    int sz = r * r * r - (r - 1) * (r - 1) * (r - 1);
    int exterior = sz;
    graph g(sz + 1);

    int it = 0;
    vector <vector<int>> honeycomb(2 * r - 1);
    for (int i = 0, len = r; i < 2 * r - 1; i++)
    {
        for (int j = 0; j < len; j++)
        {
            honeycomb[i].push_back(it++);
        }
        if (i + 1 < r)
            len++;
        else
            len--;
    }

    for (int i = 0; i < 2 * r - 1; i++)
    {
        for (int j = 0; j < honeycomb[i].size(); j++)
        {
            int curr = honeycomb[i][j];
            for (int k = 0; k < 6; k++)
            {
                int nx = i + dx[k];
                int ny;
                if (i + 1 == r)
                    ny = j + dy_mid[k];
                else if(i + 1 < r)
                    ny = j + dy_top[k];
                else
                    ny = j + dy_bottom[k];

                if (nx < 0 or nx >= 2 * r - 1 or ny < 0 or ny >= honeycomb[nx].size())
                {
                    g[curr].push_back({exterior});
                    g[exterior].push_back({curr});
                }
                else
                {
                    int neighbor = honeycomb[nx][ny];
                    g[curr].push_back({neighbor});
                }
            }
        }
    }

    vector <bool> house(sz + 1);
    for (int i = 0; i < k; i++)
    {
        int p;
        cin>>p;
        house[--p] = true;
    }

    vector <int> outer(sz + 1);
    dfs(g, exterior, outer, house);

    int sol = 0;
    for (int i = 0; i < g.size(); i++) if (outer[i] == 1)
    {
        for (edge e: g[i]) if (house[e.to])
        {
            sol++;
        }
    }
    cout<<sol<<'\n';
}

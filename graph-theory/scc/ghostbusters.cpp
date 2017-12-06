//SCC (Kosaraju), 2-SAT, binary search
//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=5719
//2016 Mid-Atlantic Regional

#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

#define INF 123123123

struct distPair
{
    int d;
    int i;
    int j;
    int t;

    distPair(int a, int b, int c, int ty)
    {
        d = a;
        i = b;
        j = c;
        t = ty;
    }

    bool operator < (distPair b) const
    {
        return d < b.d;
    }
};

struct pt
{
    int x, y;
    int dist(pt b)
    {
        if (x == b.x)
        {
            return abs(b.y - y);
        }
        if(y == b.y)
        {
            return abs(b.x - x);
        }
        return INF;
    }
};

stack <int> order;
vector <int> visited;

vector <int> components;
int curr_component = 0;

void dfsOrder(vector <vector<int>> &graph, int curr)
{
    visited[curr] = 1;

    for (int neighbor: graph[curr])
    {
        if (!visited[neighbor])
        {
            dfsOrder(graph, neighbor);
        }
    }

    order.push(curr);
}

void dfsReverse(vector <vector<int>> &graph, int curr)
{
    visited[curr] = 0;
    components[curr] = curr_component;

    for (int neighbor: graph[curr])
    {
        if (visited[neighbor])
        {
            dfsReverse(graph, neighbor);
        }
    }
}

void scc(vector <vector<int>> &g, vector <vector<int>> &tg)
{
    visited.resize(g.size(), 0);
    components.resize(g.size(), -1);

    for (int i = 0; i < g.size(); i++)
    {
        if (visited[i]) continue;

        dfsOrder(g, i);
    }

    while (!order.empty())
    {
          int start = order.top();
          order.pop();

          if (!visited[start]) continue;

          dfsReverse(tg, start);
          curr_component++;
    }
}

bool check(vector <distPair> &ds, int upTo, int sz)
{

    vector <vector<int> > graph (sz, vector<int>());
    vector <vector<int> > transpose(sz, vector<int>());

    for (distPair dp: ds)
    {
        int distBet = dp.d;
        int i = dp.i;
        int j = dp.j;
        int type = dp.t;

        if (distBet > 2 * upTo)
        {
            break;
        }

        if (type == -1)
        {
            graph[2 * i].push_back(2 * j + 1);
            graph[2 * j].push_back(2 * i + 1);
            transpose[2 * j + 1].push_back(2 * i);
            transpose[2 * i + 1].push_back(2 * j);
        }
        else
        {
            graph[2 * i + 1].push_back(2 * j);
            graph[2 * j + 1].push_back(2 * i);
            transpose[2 * j].push_back(2 * i + 1);
            transpose[2 * i].push_back(2 * j + 1);
        }
    }

    scc(graph, transpose);

    for (int i = 0; i < graph.size(); i++)
    {
        if (components[i] == components[i^1])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int n;
    while(cin>>n)
    {
        vector <pt> points(n);
        vector <distPair> distSet;

        for (int i = 0; i < n; i++)
        {
            cin>>points[i].x>>points[i].y;
        }

        for (int i = 0; i < n; i++)
        {

            for (int j = i + 1; j < n; j++)
            {
                int distBetween = points[j].dist(points[i]);

                if (distBetween  < INF)
                {
                    int typePt = 0;
                    if (points[i].x == points[j].x)
                        typePt = 1;
                    else
                        typePt = -1;
                    distSet.push_back(distPair(distBetween,i, j, typePt));
                }
            }
        }

        sort(distSet.begin(), distSet.end());

        int left = 0;
        int right = 1000001;

        while (left < right)
        {
            int mid = (left + right + 1) / 2;

            bool val = check(distSet, mid, 2 * n);

            if (val)
            {
                left = mid;
            }
            else
            {
                right = mid - 1;
            }
        }
        if (left == 1000001 and check(distSet, left, 2 * n))
        {
            cout<<"UNLIMITED"<<'\n';
        }
        else
        {
            cout<<left<<'\n';
        }
    }

    return 0;
}

//strongly connected components (kosaraju), 2-SAT, binary search on solution
//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=5719
//2016 Mid-Atlantic Regional

#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

#define INF 1231231234

struct pt
{
    int x, y;
};

typedef vector <vector<int>> graph;

void ordering(graph &g, int curr, vector <int> &visited, deque <int> &ordered)
{
    if (visited[curr]) return;
    visited[curr] = 1;
    for (int neighbor: g[curr]) if (!visited[neighbor])
    {
        ordering(g, neighbor, visited, ordered);
    }
    ordered.push_front(curr);
}

void categorize(graph &t, int curr, vector <int> &visited, vector <vector<int>> &components)
{
    if (visited[curr]) return;
    visited[curr] = 1;
    components.rbegin() -> push_back(curr);
    for (int neighbor: t[curr]) if (!visited[neighbor])
    {
        categorize(t, neighbor, visited, components);
    }
}

vector <vector<int>> kosarajuSCC(graph &g)
{
    int n = g.size();
    graph t(n);
    vector <int> visited(n);
    deque <int> ordered;
    vector <vector<int>> components;

    for (int i = 0; i < n; i++)
    {
        for (int j: g[i])
        {
            t[j].push_back(i);
        }
    }

    for (int i = 0; i < n; i++) if (!visited[i])
    {
        ordering(g, i, visited, ordered);
    }

    fill(visited.begin(), visited.end(), 0);

    for (int i: ordered) if (!visited[i])
    {
          components.push_back({});
          categorize(t, i, visited, components);
    }

    return components;
}

bool check(vector <pt> &points, int power)
{
    int n = points.size();
    graph g(2 * n);

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (points[i].x == points[j].x and abs(points[i].y - points[j].y) <= 2 * power)
            {
                g[2 * i + 1].push_back(2 * j);
                g[2 * j + 1].push_back(2 * i);
            }
            else if(points[i].y == points[j].y and abs(points[i].x - points[j].x) <= 2 * power)
            {
                g[2 * i].push_back(2 * j + 1);
                g[2 * j].push_back(2 * i + 1);
            }
        }
    }

    auto components = kosarajuSCC(g);
    vector <int> numComponent(2 * n);

    for (int i = 0; i < components.size(); i++)
    {
        for (int j: components[i])
        {
            numComponent[j] = i;
        }
    }

    for (int i = 0; i < 2 * n; i += 2)
    {
        if (numComponent[i] == numComponent[i + 1])
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

        for (int i = 0; i < n; i++)
        {
            cin>>points[i].x>>points[i].y;
        }

        int left = 0;
        int right = 1000001;

        while (left < right)
        {
            int mid = (left + right + 1) / 2;
            bool val = check(points, mid);

            if (val)
            {
                left = mid;
            }
            else
            {
                right = mid - 1;
            }
        }
        if (left == 1000001)
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

//strongly connected component (kosaraju), 2-SAT, binary search on solution
//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=5719
//2016 Mid-Atlantic Regional

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

#define INF 123123123

struct pt
{
    int x;
    int y;
};

int n;
vector <pt> points;

vector <vector<int>> graph, transpose;
stack <int> order;
vector <int> visited, components;
int scc_sz = 0;

void ordering(int curr)
{
    visited[curr] = 1;
    for (int neighbor: graph[curr])
    {
        if (!visited[neighbor])
        {
            ordering(neighbor);
        }
    }
    order.push(curr);
}

void categorize(int curr)
{
    visited[curr] = 0;
    components[curr] = scc_sz;
    for (int neighbor: transpose[curr])
    {
        if (visited[neighbor])
        {
            categorize(neighbor);
        }
    }
}

void kosarajuSCC()
{
    int n = graph.size();
    visited.resize(n, 0);
    components.resize(n, -1);

    for (int i = 0; i < n; i++)
    {
        if (visited[i]) continue;

        ordering(i);
    }

    while (!order.empty())
    {
          int curr = order.top();
          order.pop();

          if (!visited[curr]) continue;

          categorize(curr);
          scc_sz++;
    }
}

void add_edge(int i, int j)
{
    graph[i].push_back(j);
    transpose[j].push_back(i);
}

bool check(int power)
{
    graph.clear(); transpose.clear();
    graph.resize(2 * n);
    transpose.resize(2 * n);

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (points[i].x == points[j].x and abs(points[i].y - points[j].y) <= 2 * power)
            {
                add_edge(2 * i + 1, 2 * j);
                add_edge(2 * j + 1, 2 * i);
            }
            else if(points[i].y == points[j].y and abs(points[i].x - points[j].x) <= 2 * power)
            {
                add_edge(2 * i, 2 * j + 1);
                add_edge(2 * j, 2 * i + 1);
            }
        }
    }

    kosarajuSCC();

    for (int i = 0; i < graph.size(); i += 2)
    {
        if (components[i] == components[i + 1])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    while(cin>>n)
    {
        points.resize(n);

        for (int i = 0; i < n; i++)
        {
            cin>>points[i].x>>points[i].y;
        }

        int left = 0;
        int right = 1000001;

        while (left < right)
        {
            int mid = (left + right + 1) / 2;

            bool val = check(mid);

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

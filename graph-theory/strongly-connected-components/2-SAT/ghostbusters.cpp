//strongly connected components (kosaraju), 2-SAT, binary search on solution
//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=5719
//2016 Mid-Atlantic Regional

#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

const int INF = 1231231234;
const int MAXP = 1000000;

struct edge{int to;};
typedef vector <vector<edge>> graph;

graph getTranspose(graph &g)
{
    graph t(g.size());
    for (int i = 0; i < g.size(); i++) for (edge e: g[i])
    {
        t[e.to].push_back({i});
    }
    return t;
}

struct kosarajuSCC
{
    int n, sz = 0;
    graph g, t;
    vector <bool> visited; deque <int> ordered;
    vector <int> category;

    kosarajuSCC(graph &gr)
    {
        g = gr, t = getTranspose(gr), n = g.size();
        visited.resize(n), category.resize(n);
        getScc();
    }

    void getScc()
    {
        for (int i = 0; i < n; i++) if (!visited[i])
            ordering(i);
        for (int i: ordered) if (visited[i])
            categorize(i), ++sz;
    }

    void ordering(int curr)
    {
        if (visited[curr]) return;
        visited[curr] = true;
        for (edge e: g[curr]) if (!visited[e.to])
            ordering(e.to);
        ordered.push_front(curr);
    }

    void categorize(int curr)
    {
        if (!visited[curr]) return;
        visited[curr] = false;
        category[curr] = sz;
        for (edge e: t[curr]) if (visited[e.to])
            categorize(e.to);
    }
};

struct pt{int x, y;};

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
                g[2 * i + 1].push_back({2 * j});
                g[2 * j + 1].push_back({2 * i});
            }
            else if(points[i].y == points[j].y and abs(points[i].x - points[j].x) <= 2 * power)
            {
                g[2 * i].push_back({2 * j + 1});
                g[2 * j].push_back({2 * i + 1});
            }
        }
    }

    auto scc = kosarajuSCC(g);
    for (int i = 0; i < 2 * n; i += 2)
    {
        if (scc.category[i] == scc.category[i + 1]) return false;
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    while(cin>>n)
    {
        vector <pt> points(n);

        for (int i = 0; i < n; i++)
        {
            cin>>points[i].x>>points[i].y;
        }

        int l = 0, r = MAXP + 1;
        while (l < r)
        {
            int m = (l + r + 1) / 2;
            if (check(points, m)) l = m;
            else r = m - 1;
        }
        if (l > MAXP) cout<<"UNLIMITED"<<'\n';
        else cout<<l<<'\n';
    }

    return 0;
}

//network flow (dinic, minimum vertex cover on bipartite, recovering mvc/min cut), union of rectangles (recovering points), segment tree (lazy propagation)
//https://www.hackerrank.com/contests/university-codesprint-4/challenges/drawing-rectangles

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

using namespace std;

typedef pair<int, int> ii;
const int MAXN = 300001;
const int INF = 1231231234;

struct edge
{
    int to, id;
};

typedef vector<vector<edge>> graph;

vector <int> residual, level, startEdge, created(2 * MAXN);
void addEdge(graph &g, int from, int to, int capacity)
{
    g[from].push_back({to, (int) residual.size()});
    residual.push_back(capacity);
    g[to].push_back({from, (int) residual.size()});
    residual.push_back(0);
}

bool buildLevelGraph(graph &g, int source, int sink)
{
    queue <int> q;
    q.push(source);
    fill(level.begin(), level.end(), -1);
    level[source] = 0;
    while (!q.empty())
    {
        int curr = q.front();
        q.pop();
        for (edge e: g[curr]) if (level[e.to] == -1 and residual[e.id] > 0)
        {
            q.push(e.to);
            level[e.to] = level[curr] + 1;
        }
    }
    return level[sink] != -1;
}

int blockingFlow(graph &g, int curr, int sink, int flow = INF)
{
    if (curr == sink) return flow;
    for (; startEdge[curr] < g[curr].size(); startEdge[curr]++)
    {
        edge e = g[curr][startEdge[curr]];
        if (level[e.to] == level[curr] + 1 and residual[e.id] > 0)
        {
            int augment = blockingFlow(g, e.to, sink, min(flow, residual[e.id]));
            if (augment > 0)
            {
                residual[e.id] -= augment;
                residual[e.id ^ 1] += augment;
                return augment;
            }
        }
    }
    return 0;
}

int dinic(graph &g, int source, int sink)
{
    int res = 0;
    level.resize(g.size()), startEdge.resize(g.size());
    while (buildLevelGraph(g, source, sink))
    {
        fill(startEdge.begin(), startEdge.end(), 0);
        while (int delta = blockingFlow(g, source, sink)) res += delta;
    }
    return res;
}

vector <int> minimumSTCut(graph &g, int source, int sink)
{
    vector <int> cut(g.size());
    function <void (int)> findCut = [&](int curr)
    {
        if (cut[curr]) return;
        cut[curr] = true;
        for (edge e: g[curr]) if(!cut[e.to] and residual[e.id] > 0)
        {
            findCut(e.to);
        }
    };
    findCut(source);
    return cut;
}

struct node
{
    int maxVal, lazy, isLazy;
    node *l, *r;

    node(){maxVal = -INF, lazy = isLazy = 0, l = NULL, r = NULL;}
    void init(int i){maxVal = i;}

    node* refresh()
    {
        maxVal = max(l -> maxVal, r -> maxVal);
        return this;
    }

    void pushLazy(int lb, int rb)
    {
        if (isLazy)
        {
            maxVal += lazy;
            if (lb != rb)
            {
                l -> setLazy(lazy), r -> setLazy(lazy);
            }
            resetLazy();
        }
    }
    void setLazy(int v){lazy += v, isLazy = true;}
    void resetLazy(){lazy = 0, isLazy = false;}
};

struct segmentTree
{
    int sz;
    node* root;

    segmentTree(int s)
    {
        root = new node();
        sz = s;
        build(root, 0, sz - 1);
    }

    node combine(node a, node b)
    {
        node acc;
        acc.l = &a, acc.r = &b;
        return *(acc.refresh());
    }

    void build(node* &curr, int l, int r)
    {
        if (l == r) { curr -> init(0); return; }
        int m = (l + r) >> 1;
        curr -> l = new node(), curr -> r = new node();
        build(curr -> l, l, m);
        build(curr -> r, m + 1, r);
        curr -> refresh();
    }

    int query(int l, int r) {return query(root, 0, sz - 1, l, r).maxVal;}
    node query(node* &curr, int l, int r, int ql, int qr)
    {
        curr -> pushLazy(l, r);
        if (l > qr or r < ql) return node();
        if (l >= ql and r <= qr) return *curr;
        int m = (l + r) >> 1;
        return combine(query(curr -> l, l, m, ql, qr), query(curr -> r, m + 1, r, ql, qr));
    }

    void modify(int l, int r, int v) {modify(root, 0, sz - 1, v, l, r);}
    void modify(node* &curr, int l, int r, int v, int ql, int qr)
    {
        curr -> pushLazy(l, r);
        if (l > qr or r < ql) return;
        if (l >= ql and r <= qr)
        {
            curr -> setLazy(v);
            curr -> pushLazy(l, r);
            return;
        }
        int m = (l + r) >> 1;
        modify(curr -> l, l, m, v, ql, qr), modify(curr -> r, m + 1, r, v, ql, qr);
        curr -> refresh();
    }

    vector <int> findNonZeros()
    {
        vector <int> nonZeros;
        findNonZeros(root, 0, sz - 1, nonZeros);
        return nonZeros;
    }
    void findNonZeros(node* &curr, int l, int r, vector <int> &nonZeros)
    {
        curr -> pushLazy(l, r);
        if (curr -> maxVal == 0) return;
        if (l == r) {nonZeros.push_back(l); return;}
        int m = (l + r) >> 1;
        findNonZeros(curr -> l, l, m, nonZeros), findNonZeros(curr -> r, m + 1, r, nonZeros);
    }
};

struct event
{
    int x, y1, y2, isStart;
    bool operator < (const event &o) const
    {
        if (x != o.x) return x < o.x;
        return make_pair(isStart, make_pair(y1, y2)) < make_pair(o.isStart, make_pair(o.y1, o.y2));
    }
};

vector <event> rectangleToEvent(int x1, int y1, int x2, int y2)
{
    return {{x1, y1, y2, true}, {x2 + 1, y1, y2, false}};
}

vector <ii> unionRectangles(vector <event> &events)
{
    segmentTree st(MAXN);
    vector <ii> points;
    sort(events.begin(), events.end());
    for (int i = 0, curr = 0; i < MAXN; i++)
    {
        while(events[curr].x == i)
        {
            st.modify(events[curr].y1, events[curr].y2, events[curr].isStart ? 1 : -1);
            curr++;
        }
        auto nz = st.findNonZeros();
        for (int j: nz) points.push_back({i, j});
    }
    return points;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin>>n;

    vector <event> events;
    for (int i = 0; i < n; i++)
    {
        int x1, y1, x2, y2;
        cin>>x1>>y1>>x2>>y2;
        for (event e: rectangleToEvent(x1, y1, x2, y2)) events.push_back(e);
    }
    auto points = unionRectangles(events);

    graph g(2 * MAXN + 2);
    int s = 2 * MAXN, t = 2 * MAXN + 1;

    for (ii p: points)
    {
        int v = 2 * p.first + 1, h = 2 * p.second;
        if (!created[v]){addEdge(g, s, v, 1), created[v] = true;}
        if (!created[h]){addEdge(g, h, t, 1), created[h] = true;}
        addEdge(g, v, h, 1);
    }

    int sol = dinic(g, s, t);
    auto cut = minimumSTCut(g, s, t);

    vector <int> vertical, horizontal;
    for (int i = 0; i < 2 * MAXN; i++) if (created[i])
    {
        if (i & 1 and !cut[i]) vertical.push_back(i / 2);
        else if(!(i & 1) and cut[i]) horizontal.push_back(i / 2);
    }

    cout<<sol<<'\n';
    cout<<vertical.size()<<'\n';
    for (int i: vertical) cout<<i<<" ";
    cout<<'\n';
    cout<<horizontal.size()<<'\n';
    for (int i: horizontal) cout<<i<<" ";
    cout<<'\n';

    return 0;
}

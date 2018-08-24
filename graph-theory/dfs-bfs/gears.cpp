// dfs (graph coloring to check if bipartite), simplified fraction class, checking if circles are tangent
// https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&category=712&page=show_problem&problem=5401
// 2015 Southeast USA Regional

#include <bits/stdc++.h>

using namespace std;

typedef long long fracT;

fracT gcd(fracT a, fracT b)
{
    while (b != 0)
        tie(a, b) = make_tuple(b, a % b);
    return a;
}

struct fraction
{
    fracT num = 0, denom = 1;

    fraction(){}
    fraction(fracT a, fracT b, bool simplify = true)
    {
        if (a < 0)
            a = -a, b = -b;
        fracT g = simplify ? gcd(abs(a), abs(b)) : 1;
        num = a / g, denom = b / g;
    }
};

fraction reciprocal(const fraction &f)
{
    return {f.denom, f.num};
}

fraction operator * (const fraction &a, const fraction &b)
{
    return {a.num * b.num, a.denom * b.denom};
}

struct edge{int to; fraction radius_ratio;};
typedef vector<vector<edge>> graph;

struct gear
{
    int x, y, r;
};

bool tangent(gear g1, gear g2)
{
    long long dx = abs(g1.x - g2.x);
    long long dy = abs(g1.y - g2.y);
    long long hypot = g1.r + g2.r;
    return dx * dx + dy * dy <= hypot * hypot;
}

vector <fraction> ratios;
vector <bool> reached, colors;
bool dfs(graph &g, int curr, bool color, const fraction &ratio_to_source)
{
    if (reached[curr])
        return color == colors[curr];

    reached[curr] = true;
    colors[curr] = color;
    ratios[curr] = ratio_to_source;

    for (edge e: g[curr])
    {
        bool viable = dfs(g, e.to, 1 - color, ratio_to_source * e.radius_ratio);
        if (!viable)
            return false;
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    while (cin >> n)
    {
        vector <gear> gears(n);
        for (int i = 0; i < n; i++)
        {
            cin>>gears[i].x>>gears[i].y>>gears[i].r;
        }
        graph g(n);
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (tangent(gears[i], gears[j]))
                {
                    fraction rat = {gears[j].r, -gears[i].r};
                    g[i].push_back({j, rat});
                    g[j].push_back({i, reciprocal(rat)});
                }
            }
        }
        reached.assign(n, 0);
        colors.assign(n, false);
        ratios.assign(n, fraction());
        bool viable = dfs(g, 0, 0, {1, 1});
        if (!viable)
            cout<<-1<<'\n';
        else if(!reached[n - 1])
            cout<<0<<'\n';
        else
        {
            fraction sol = ratios[n - 1];
            cout<<sol.num<<" "<<sol.denom<<'\n';
        }
    }

    return 0;
}

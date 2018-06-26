//randomization (hard to construct counter case), greedy, geometry
//https://codeforces.com/contest/996/problem/E

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

typedef long long ll;

typedef ll ptT;
struct pt
{
    ptT x, y;
    int index;

    pt operator + (const pt &o) const {return {x + o.x, y + o.y};}
    pt operator - (const pt &o) const {return {x - o.x, y - o.y};}
    ptT operator * (const pt &o) const {return x * o.x + y * o.y;}
    ptT norm2() const {return *this * *this;}
};

bool solvable(vector <pt> &vec, ll threshold, vector <int> &sol)
{
    pt p = {0, 0};
    for (pt v: vec)
    {
        pt fwd = p + v, bck = p - v;
        if (fwd.norm2() < bck.norm2())
        {
            p = fwd;
            sol[v.index] = 1;
        }
        else
        {
            p = bck;
            sol[v.index] = -1;
        }
    }
    return p.norm2() <= threshold * threshold;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin>>n;

    vector <pt> vec(n);
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin>>a>>b;
        vec[i] = {a, b, i};
    }
    vector <int> sol(n);
    while (!solvable(vec, 1500000, sol))
    {
        random_shuffle(vec.begin(), vec.end());
    }
    for (int i: sol)
    {
        cout<<i<<" ";
    }
    cout<<'\n';

    return 0;
}

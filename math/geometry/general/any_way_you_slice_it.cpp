// simulation, line segment intersection, vector operations (rotation)
// https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&category=576&page=show_problem&problem=4107
// 2012 Mid-Central Regional

#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-9;
const double PI = 3.14159;

typedef long double ptT;
struct pt
{
    ptT x, y;

    pt(){}
    pt(ptT a, ptT b){x = a, y = b;}

    pt operator + (const pt &o) const {return {x + o.x, y + o.y};}
    pt operator - (const pt &o) const {return {x - o.x, y - o.y};}

    ptT operator ^ (const pt &o) const {return x * o.y - y * o.x;}
    pt rotateCcw(double theta) {return {cos(theta) * x - sin(theta) * y, sin(theta) * x + cos(theta) * y};}
};
pt operator * (ptT k, const pt &p) {return {k * p.x, k * p.y};}

int orientation(const pt &o, const pt &a, const pt &b)
{
    auto cp = (b - o) ^ (a - o);
    return cp > EPS ? 1 : (cp < EPS ? -1 : 0);
} //cw: 1, ccw: -1, col: 0

struct line_segment
{
    pt a, b;

    bool intersects(const line_segment &o) const
    {
        if (orientation(a, b, o.a) == orientation(a, b, o.b))
            return false;
        if (orientation(o.a, o.b, a) == orientation(o.a, o.b, b))
            return false;
        return true;
    }
};

double degreeToRadians(double degree)
{
    return degree * PI / 180.0;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    while (true)
    {
        int n;
        cin>>n;
        if (n == 0) break;

        vector <line_segment> lines(n);

        pt prev = {0, 0};
        int curr_rot = 0;
        for (int i = 0; i < n; i++)
        {
            int rot, dist;
            cin>>rot>>dist;
            curr_rot += rot;

            double rad = degreeToRadians(curr_rot);
            pt curr = dist * pt(0, 1).rotateCcw(rad) + prev;
            lines[i] = {prev, curr};

            prev = curr;
        }

        int sol = -1;
        for (int i = 0; i < n; i++)
        {
            bool hasIntersection = false;
            for (int j = i - 2; j >= 0; j--)
            {
                if (lines[i].intersects(lines[j]))
                    hasIntersection = true;
            }
            if (hasIntersection)
            {
                sol = i;
                break;
            }
        }
        if (sol != -1) cout<<sol + 1<<'\n';
        else cout<<"SAFE"<<'\n';
    }

    return 0;
}

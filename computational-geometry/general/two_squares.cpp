//triangle (point) inclusion checking
//http://codeforces.com/contest/994/problem/C

#include <iostream>
#include <vector>

using namespace std;

const int INF = 1231231234;

typedef int ptT;
struct pt
{
    ptT x, y;

    bool operator < (const pt &o) const {return make_pair(y, x) < make_pair(o.y, o.x);}
    bool operator == (const pt &o) const {return abs(x - o.x) == 0 and abs(y - o.y) == 0;}

    pt operator - (const pt &o) const {return {x - o.x, y - o.y};}

    ptT operator ^ (const pt &o) const {return x * o.y - y * o.x;}
    ptT operator * (const pt &o) const {return x * o.x + y * o.y;}

    ptT norm2() const {return *this * *this;}
    ptT dist2(const pt &o) const {return (*this - o).norm2();}
};

int orientation(const pt &o, const pt &a, const pt &b)
{
    auto cp = (b - o) ^ (a - o);
    return cp > 0 ? 1 : (cp < 0 ? -1 : 0);
} //cw: 1, ccw: -1, col: 0

typedef vector <pt> polygon;
int prev(int i, int n, int st = 1){return (i - st + n) % n;}
int next(int i, int n, int st = 1){return (i + st) % n;};

int pointInTriangle(polygon &triangle, pt &p)
{
    int orient[3];
    for (int i = 0; i < 3; i++)
        orient[i] = orientation(triangle[i], triangle[next(i, 3)], p);
    if (orient[0] == orient[1] and orient[1] == orient[2]) return -1;
    for (int i = 0; i < 3; i++) if (orient[i] * orient[next(i, 3)] == -1) return 1;
    return 0;
} //inside: -1, outside: 1, on: 0

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    polygon A(4), B(4);

    for (int i = 0; i < 4; i++)
    {
        int a, b;
        cin>>a>>b;
        A[i] = {a, b};
    }
    for (int i = 0; i < 4; i++)
    {
        int a, b;
        cin>>a>>b;
        B[i] = {a, b};
    }

    polygon triangles[2][2];
    triangles[0][0] = {A[0], A[1], A[2]};
    triangles[0][1] = {A[2], A[3], A[0]};
    triangles[1][0] = {B[0], B[1], B[2]};
    triangles[1][1] = {B[2], B[3], B[0]};

    bool intersect = false;
    for (int x = -100; x <= 100; x++)
    {
        for (int y = -100; y <= 100; y++)
        {
            bool inA = false, inB = false;
            pt p = {x, y};
            for (int t = 0; t < 2; t++)
            {
                if (pointInTriangle(triangles[0][t], p) != 1)
                {
                    inA = true;
                }
            }
            for (int t = 0; t < 2; t++)
            {
                if (pointInTriangle(triangles[1][t], p) != 1)
                {
                    inB = true;
                }
            }
            if (inA and inB)
            {
                intersect = true;
                break;
            }
        }
        if (intersect) break;
    }

    if (intersect)
    {
        cout<<"Yes"<<'\n';
    }
    else
    {
        cout<<"No"<<'\n';
    }

    return 0;
}

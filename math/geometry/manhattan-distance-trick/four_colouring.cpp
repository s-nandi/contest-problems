//manhattan distance trick, constructive algorithm (partitioning area)
//https://code-festival-2017-quala.contest.atcoder.jp/tasks/code_festival_2017_quala_d

#include <iostream>
#include <vector>

using namespace std;

const int INF = 1231231234;

struct pt
{
    int x, y;
};

pt toChebyshev(pt p)
{
    return {p.x + p.y, p.x - p.y};
}

char getColor(pt p, int minx, int miny, int d)
{
    int xPartition = (p.x - minx) / d, yPartition = (p.y - miny) / d;
    if (xPartition & 1)
    {
        return yPartition & 1 ? 'R' : 'B';
    }
    else
    {
        return yPartition & 1 ? 'G' : 'Y';
    }
}

int main()
{
    int h, w, d;
    cin>>h>>w>>d;

    vector <pt> corners = {{0, 0}, {h, 0}, {0, w}, {h, w}};
    int minX = INF, minY = INF;
    for (int i = 0; i < 4; i++)
    {
        pt p = toChebyshev(corners[i]);
        minX = min(minX, p.x);
        minY = min(minY, p.y);
    }

    char grid[h][w];
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            pt p = toChebyshev({i, j});
            grid[i][j] = getColor(p, minX, minY, d);
        }
    }

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            cout<<grid[i][j];
        }
        cout<<'\n';
    }

    return 0;
}

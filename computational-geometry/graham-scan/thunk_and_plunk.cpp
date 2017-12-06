//graham scan, vector calculations: addition/norm/perpendicular, polygon containment
//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3958
//2011 Mid-Atlantic Regional

#include <stack>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;


struct pt
{
    double x, y;

    bool operator < (pt b) const
    {
        if (y < b.y)
        {
            return true;
        }
        else if(y == b.y)
        {
            if (x < b.x)
            {
                return true;
            }

        }
        return false;
    }
};

bool onSegment(pt p, pt q, pt r)
{
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
            q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
        return true;
    return false;
}

int orientation(pt a, pt b, pt c)
{
    double  val1 = (double) (b.y - a.y) * (c.x - b.x);
    double val2 = (double) (b.x - a.x) * (c.y - b.y);

    if (val1 < val2)
    {
        return -1; //counterclockwise
    }
    else if (val1 > val2)
    {
        return 1; //clockwise
    }
    else
    {
        return 0; //collinear
    }
}

bool onLine(pt a, pt b, pt c) //true if b is on ac
{
    if (orientation(a, b, c) != 0)
    {
        return false;
    }
    return onSegment(a, b, c);

}

bool inTriangle (pt a, pt b, pt c, pt p)
{
    int orientAB = orientation(a, b, p);
    int orientBC = orientation(b, c, p);
    int orientCA = orientation(c, a, p);
    if (orientAB == 0 and onLine(a, p, b))
    {
        return true;
    }
    if (orientBC == 0 and onLine(b, p, c))
    {
        return true;
    }
    if (orientCA == 0 and onLine(c, p, a))
    {
        return true;

    }

    if (orientAB == orientBC and orientAB == orientCA)
    {
        return true;
    }

    return false;
}

vector <pt> grahamScan(vector <pt> points) //creates clockwise convex polygon
{
    pt bottom = points[0];

    for (int i = 1; i < points.size(); i++)
    {
        if (points[i].y == bottom.y)
        {
            if (points[i].x < bottom.x)
            {
                bottom = points[i];
            }
        }
        else if(points[i].y < bottom.y)
        {
            bottom = points[i];
        }
    }

    sort(points.begin(), points.end(),
         [bottom](pt a, pt b)
    {
        if (a.x == bottom.x and a.y == bottom.y)
        {
            return true;
        }
        if (b.x == bottom.x and b.y == bottom.y)
        {
            return false;
        }
        int orient = orientation(bottom, a, b);
        if (orient == 0)
        {
            double dista = abs((double) a.x - bottom.x);
            double distb = abs((double) b.x - bottom.x);

            if (dista == distb)
            {
                return b < a;
            }
            return dista > distb;
        }
        return orient == 1;
    });

    bool includeNext = true;


    vector <pt> vPoints = {points[0]};
    vector <pt> skipped;
    for (int i = 1; i < points.size(); i++)
    {
        if (includeNext)
        {
            vPoints.push_back(points[i]);
        }
        else
        {
            skipped.push_back(points[i]);
        }

        includeNext = true;
        if(orientation(points[0], points[i], points[i + 1]) == 0)
        {
            includeNext = false;
        }
    }

    vector <pt> hull;
    hull.push_back(vPoints[0]);
    hull.push_back(vPoints[1]);
    hull.push_back(vPoints[2]);

    for (int i = 3; i < vPoints.size(); i++)
    {
        while (orientation(hull[hull.size() - 2], hull[hull.size() - 1], vPoints[i]) != 1) // != 1 if you don't want points on hull, == -1 if include points on hull
        {
            hull.pop_back();
        }
        hull.push_back(vPoints[i]);
    }

    return hull;
}

double dist(pt a, pt b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return dx * dx + dy * dy;
}

pt getVector(pt a, pt b)
{
    pt temp;
    temp.x = b.x - a.x;
    temp.y = b.y - a.y;
    return temp;
}

pt normed(pt v)
{
    pt o;
    o.x = 0.0;
    o.y = 0.0;
    double len = dist(o, v);
    pt res;
    res.x = v.x / sqrt(len);
    res.y = v.y / sqrt(len);

    return res;
}

pt perp(pt sl)
{
    pt p;
    p.x = sl.y;
    p.y = sl.x * -1;
    return p;
}

pt addPt(pt a, pt b)
{
    pt result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}


vector <pt> getRectangle(pt a, pt b)
{
    pt vec = getVector(a, b);
    pt per = perp(vec);
    pt normedVec = normed(per);

    vector <pt> rectangle(4);

    rectangle[0] = a;
    rectangle[1] = b;
    rectangle[2] = addPt(b, normedVec);
    rectangle[3] = addPt(a, normedVec);

    return rectangle;
}

bool inHull(vector <pt> hull, pt p)
{
    if (hull.size() == 3)
    {
        return inTriangle(hull[0], hull[1], hull[2], p);
    }
    bool isIn;
    for (int i = 1; i < hull.size() - 1; i++)
    {
        isIn = inTriangle(hull[0], hull[i], hull[i+1], p);
        if (isIn)
        {
            return true;
        }
    }
    return false;
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;

    while(cin>>n)
    {
        if (n == 0)
        {
            break;
        }

        vector <pt> water;
        vector <pt> land;
        double x, y;
        char type;

        for (int i = 0; i < n; i++)
        {
            cin>>x>>y>>type;

            pt temp;
            temp.x = x;
            temp.y = y;
            if (type == 'T')
            {
                land.push_back(temp);
            }
            else
            {
                water.push_back(temp);
            }
        }

        bool isIsland = false;
        if (water.size() == 2)
        {
            for (pt p: land)
            {
                vector <pt> rectOne = getRectangle(water[0], water[1]);
                vector <pt> rectTwo = getRectangle(water[1], water[0]);
                if (!inHull(rectOne, p) and !inHull(rectTwo, p))
                {
                    isIsland = true;
                }
            }
            if (isIsland)
                cout<<"There must be an island."<<'\n';
            else
                cout<<"There might not be an island."<<'\n';


        }

        else
        {
            vector <pt> waterArea = grahamScan(water);

            stack <pt> conflictPoints;
            for (pt p: land)
            {
                if (inHull(waterArea, p))
                {
                    conflictPoints.push(p);
                }
            }
            while(!conflictPoints.empty())
            {
                pt curr = conflictPoints.top();
                conflictPoints.pop();
                bool safe = false;

                for (int i = 0; i < waterArea.size(); i++)
                {
                    pt ptA = waterArea[i];
                    pt ptB = waterArea[(i + 1) % waterArea.size()];

                    vector <pt> rect = getRectangle(ptA, ptB);

                    if (inHull(rect, curr))
                    {
                        safe = true;
                    }
                }

                if (!safe)
                {
                    isIsland = true;
                }

            }

            if (isIsland)
            {
                cout<<"There must be an island."<<'\n';
            }
            else
            {
                cout<<"There might not be an island."<<'\n';
            }
        }
    }
    return 0;
}

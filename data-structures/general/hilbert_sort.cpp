// quadtree, hilbert sorting integer points
// https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&category=712&page=show_problem&problem=5397
// 2015 Pacific Northwest Regional

#include <bits/stdc++.h>

using namespace std;

typedef tuple<double, double, double, double> box;

struct pt
{
    double x, y;
    int index;

    pt operator + (pt &o)
    {
        return {x + o.x, y + o.y};
    }

    pt div2()
    {
        return {x / 2, y / 2};
    }

    bool operator == (pt &o)
    {
        return x == o.x and y == o.y;
    }
};

box findBounds(pt c[4])
{
    double mxx, mxy, mnx, mny;
    mxx = mnx = c[0].x;
    mxy = mny = c[0].y;
    for (int i = 1; i < 4; i++)
    {
        mxx = max(mxx, c[i].x);
        mxy = max(mxy, c[i].y);
        mnx = min(mnx, c[i].x);
        mny = min(mny, c[i].y);
    }
    return box{mnx, mny, mxx, mxy};
}

bool contained(box &b, pt p)
{
    double mxx, mxy, mnx, mny;
    tie(mnx, mny, mxx, mxy) = b;
    return p.x >= mnx and p.x <= mxx and p.y >= mny and p.y <= mxy;
}

struct hilberttree
{
    pt corners[4];
    vector <pt> belongs;
    hilberttree* children[4];
    box bb;

    hilberttree(const vector <pt> &c, int quadtrant = -1)
    {
        for (int i = 0; i < 4; i++)
            corners[i] = c[i], children[i] = NULL;
        if (quadtrant == 1)
            swap(corners[1], corners[3]);
        else if(quadtrant == 4)
            swap(corners[0], corners[2]);
        bb = findBounds(corners);
    }

    void makeChildren()
    {
        pt center = (corners[0] + corners[2]).div2();
        pt nextMid[4];
        for (int i = 0; i < 4; i++)
            nextMid[i] = (corners[i] + corners[(i + 1) % 4]).div2();
        children[0] = new hilberttree({corners[0], nextMid[0], center, nextMid[3]}, 1);
        children[1] = new hilberttree({nextMid[0], corners[1], nextMid[1], center}, 2);
        children[2] = new hilberttree({center, nextMid[1], corners[2], nextMid[2]}, 3);
        children[3] = new hilberttree({nextMid[3], center, nextMid[2], corners[3]}, 4);
    }

    void store(vector <pt> &points)
    {
        if (points.size() == 0) return;
        else if (points.size() == 1)
            belongs = points;
        else
        {
            makeChildren();
            vector <pt> storage[4];
            for (pt p: points)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (contained(children[i] -> bb, p))
                        storage[i].push_back(p);
                }
            }
            for (int i = 0; i < 4; i++)
                children[i] -> store(storage[i]);
        }
    }

    vector <pt> output()
    {
        if (children[0])
        {
            vector <pt> res;
            for (int i = 0; i < 4; i++)
            {
                auto child = children[i] -> output();
                res.insert(res.end(), child.begin(), child.end());
            }
            return res;
        }
        else
            return belongs;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n; double s;
    while (cin >> n >> s)
    {
        vector <pt> init = {{0, 0, -1}, {0, s, -1}, {s, s, -1}, {s, 0, -1}};
        vector <pt> positions(n);
        vector <string> names(n);
        for (int i = 0; i < n; i++)
        {
            cin>>positions[i].x>>positions[i].y>>names[i];
            positions[i].index = i;
        }
        hilberttree ht(init);
        ht.store(positions);
        for (pt p: ht.output())
            cout<<names[p.index]<<'\n';
    }

    return 0;
}

//trigonometry, permutations
//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=5972
//2016 Mid-Atlantic Regional

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

#define EPS .0001

const double PI = 3.1415;

struct pt
{
    double x;
    double y;

    pt operator + (pt b)
    {
        return {x + b.x, y + b.y};
    }

    pt operator - (pt b)
    {
        return {x - b.x, y - b.y};
    }

    pt operator * (double c)
    {
        return {x * c, y * c};
    }

    pt operator / (double c)
    {
        return {x / c, y / c};
    }

    pt normalize()
    {
        double n = norm();
        return *this / n;
    }

    pt rotateCw(double theta)
    {
        return {cos(theta) * x + sin(theta) * y, - sin(theta) * x + cos(theta) * y};
    }

    pt rotateCcw(double theta)
    {
        return {cos(theta) * x - sin(theta) * y, sin(theta) * x + cos(theta) * y};
    }

    double dist(pt o)
    {
        return sqrt((o.x - x) * (o.x - x) + (o.y - y) * (o.y - y));
    }

    double norm()
    {
        return dist({0, 0});
    }
};

struct line
{
    pt first;
    pt second;

    line correct()
    {
        if (first.y > second.y + EPS or (abs(first.y - second.y) < EPS and first.x + EPS < second.x))
        {
            return {second, first};
        }
        else
        {
            return {first, second};
        }
    }
};


line createLine(line l, int d1, int d2, int d3)
{
    l = l.correct();

    pt A = l.first;
    pt B = l.second;

    double a = d1;
    double b = d2;
    double c = d3;

    line candidate;
    line best;

    for (int i = 0; i < 2; i++)
    {
        double cosGamma = (c * c - a * a - b * b) / (-2 * a * b);
        double gamma = acos(cosGamma);

        double cosAlpha = (a * a - c * c - b * b) / (-2 * c * b);
        double alpha = acos(cosAlpha);

        pt AB = B - A;
        pt ABnorm = AB.normalize();
        pt ACnorm = ABnorm.rotateCw(alpha);
        pt AC = ACnorm * b;
        pt C = A + AC;

        if (abs(C.dist(B) - d1) < abs(C.dist(A) - d1))
        {
            candidate = {C, B};
        }
        else
        {
            candidate = {C, A};
        }

        if (i == 0)
        {
            best = candidate;
        }
        else if(candidate.first.x > best.first.x)
        {
            best = candidate;
        }

        swap(a, b);
    }

    return best;
}

double solve(vector <int> &lines)
{
    line l = {{0, 0}, {0, double(lines[0])}};

    double maxDist = 0.0;
    int dist3 = lines[0];

    for (int i = 1; i + 1 < lines.size(); i += 2)
    {
        int dist1 = lines[i];
        int dist2 = lines[i + 1];

        if (dist3 >= dist1 + dist2 or dist1 >= dist3 + dist2 or dist2 >= dist3 + dist1)
        {
            return maxDist;
        }

        l = createLine(l, dist1, dist2, dist3);

        maxDist = max(l.first.x, maxDist);
        dist3 = dist1;
    }

    return maxDist;
}

int main()
{
    int n;
    while (cin >> n)
    {
        vector <int> lines(n);

        for (int i = 0; i < n; i++)
        {
            cin>>lines[n - i - 1];
        }

        double maxLen = -1;

        while(next_permutation(lines.begin(), lines.end()))
        {
            double len = solve(lines);
            maxLen = max(len, maxLen);
        }

        cout<<fixed<<setprecision(2)<<maxLen<<'\n';
    }

    return 0;
}

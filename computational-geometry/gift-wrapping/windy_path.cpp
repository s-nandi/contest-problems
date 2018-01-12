//gift wrapping (alternating), greedy
//http://codeforces.com/gym/101201/attachments
//2016 Pacific Northwest Regional

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct pt
{
    int x, y;
    int index;
};

int orientation(pt a, pt b, pt c)
{
    long long v1 = (b.y - a.y) * (c.x - b.x);
    long long v2 = (b.x - a.x) * (c.y - b.y);

    if (v1 < v2) return -1; //ccw
    else if(v1 > v2) return 1; //cw
    else return 0; //col
}

pt curr;
vector <pt> points;
vector <int> sol;

void add_last()
{
    curr = *(--points.end());
    points.pop_back();
    sol.push_back(curr.index);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;
    points.resize(n);

    for (int i = 0; i < n; i++)
    {
        cin>>points[i].x>>points[i].y;
        points[i].index = i;
    }

    string s;
    cin>>s;

    sort(points.begin(), points.end(), [](pt a, pt b)
    {
        return a.y != b.y ? a.y < b.y : a.x < b.x;
    });
    add_last();

    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == 'R')
        {
            sort(points.begin(), points.end(), [](pt a, pt b)
            {
                return orientation(curr, a, b) == -1;
            });
        }
        else
        {
            sort(points.begin(), points.end(), [](pt a, pt b)
            {
                return orientation(curr, a, b) == 1;
            });
        }
        add_last();
    }

    add_last();

    for (int i: sol)
    {
        cout<<i + 1<<" ";
    }
    cout<<'\n';

    return 0;
}

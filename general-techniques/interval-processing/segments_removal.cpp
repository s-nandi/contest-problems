//interval processing (parallel sets), binary search
//http://codeforces.com/contest/899/problem/E

#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct segment
{
    int pos;
    int len;
    int type;
};

struct lengthComparator
{
    bool operator () (const segment &a, const segment &b) const
    {
        if (a.len != b.len) return a.len > b.len;
        else return a.pos < b.pos;
    }
};

struct positionComparator
{
    bool operator () (const segment &a, const segment &b) const
    {
        return a.pos < b.pos;
    }
};

set <segment, lengthComparator> lengthSet;
set <segment, positionComparator> positionSet;

void add_segment(segment s)
{
    lengthSet.insert({s});
    positionSet.insert({s});
}

void remove_segment(segment s)
{
    lengthSet.erase({s});
    positionSet.erase({s});
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;

    vector <int> a(n);

    for (int i = 0; i < n; i++)
    {
        cin>>a[i];
    }
    a.push_back(-1);

    int start = 0;
    for (int i = 0; i < a.size(); i++)
    {
        if (i > 0 and a[i] != a[i - 1])
        {
            segment s = {start, (i - 1) - start + 1, a[i - 1]};
            lengthSet.insert(s);
            positionSet.insert(s);
            start = i;
        }
    }

    int sol = 0;
    while (!lengthSet.empty())
    {
        segment s = *lengthSet.begin();

        segment left, right;
        bool leftExists = false, rightExists = false;

        auto lbIterator = positionSet.find(s);
        if (lbIterator != positionSet.begin())
        {
            left = *(--lbIterator);
            leftExists = true;
        }

        auto ubIterator = positionSet.find(s);
        if (++ubIterator != positionSet.end())
        {
            right = *ubIterator;
            rightExists = true;
        }

        if (leftExists and rightExists and left.type == right.type)
        {
            segment merged = {left.pos, left.len + right.len, left.type};
            remove_segment(left);
            remove_segment(right);
            add_segment(merged);
        }

        remove_segment(s);
        sol++;
    }

    cout<<sol<<'\n';

    return 0;
}

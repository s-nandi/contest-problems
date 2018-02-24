//binary search on answer (bounding feasibility)
//http://codeforces.com/problemset/problem/940/D

#include <iostream>
#include <vector>

using namespace std;

const int INF = 1000000000;

int valid(vector <int> &a, string &b, int m, bool leftPointer)
{
    if (leftPointer)
    {
        for (int i = 4; i < a.size(); i++)
        {
            bool allLess = true;
            for (int j = 0; j < 5; j++)
            {
                if (a[i - j] >= m) allLess = false;
            }
            bool allZero = true;
            for (int j = 1; j < 5; j++)
            {
                if (b[i - j] != '0') allZero = false;
            }
            if (allLess and allZero and b[i] == '0')
            {
                return -1;
            }
            else if (allZero and b[i] == '1' and !allLess)
            {
                return 1;
            }
        }
    }
    else
    {
        for (int i = 4; i < a.size(); i++)
        {
            bool allGreater = true;
            for (int j = 0; j < 5; j++)
            {
                if (a[i - j] <= m) allGreater = false;
            }
            bool allOne = true;
            for (int j = 1; j < 5; j++)
            {
                if (b[i - j] != '1') allOne = false;
            }
            if (allGreater and allOne and b[i] == '1')
            {
                return 1;
            }
            else if(allOne and b[i] == '0' and !allGreater)
            {
                return -1;
            }
        }
    }
    return 0;
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

    string s;
    cin>>s;

    int sol[2];
    for (int i = 0; i < 2; i++)
    {
        int l, r;
        bool leftPointer;

        if (i == 0) l = -INF, r = INF, leftPointer = true;
        else l = sol[0], r = INF, leftPointer = false;

        while (l < r)
        {
            int m = l + (r - l) / 2;
            bool fail = false;
            for (int i = 4; i < n; i++)
            {
                int shift = valid(a, s, m, leftPointer);
                if (shift == 1)
                {
                    l = m + 1;
                    fail = true;
                    break;
                }
                else if(shift == -1)
                {
                    r = m - 1;
                    fail = true;
                    break;
                }
            }
            if (!fail)
            {
                 r = m;
            }
        }
        sol[i] = l;
    }

    cout<<sol[0]<<" "<<sol[1]<<'\n';

    return 0;
}

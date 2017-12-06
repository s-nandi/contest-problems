//binary search
//http://codeforces.com/problemset/problem/551/C

#include <iostream>
#include <vector>

#define ll long long

using namespace std;

bool moveBox(ll t, vector <int> b, int ns, int p)
{
    ll save = t - 1;
    ll saveTime;
    int current = 0;
    while (ns--)
    {
        t = save - current;

        while (t > 0)
        {
            if (current > p - 1)
            {
                return true;
            }
            if (b[current] == 0)
            {
                current++;
                t--;
            }
            else
            {
                if (t < b[current])
                {
                    saveTime = t;
                }
                else
                {
                    saveTime = b[current];
                }
                b[current] -= saveTime;
                t = t - saveTime;
            }

        }
    }

    for (int i = current; i < p; i++)
    {
        if (b[i] != 0)
        {
            return false;
        }
    }

    return true;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin>>n>>m;
    vector <int> boxes(n);
    for (int i = 0; i < n; i++)
    {
        cin>>boxes[i];
    }

    ll lower = 1;
    ll upper = 110000000000000;

    while (lower < upper)
    {
        ll mid = (lower + upper) / 2;

        if (moveBox(mid, boxes, m, n))
        {
            upper = mid;
        }
        else
        {
            lower = mid + 1;
        }
    }

    cout<<lower<<'\n';


    return 0;

}

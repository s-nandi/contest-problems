//greedy (comparator)
//http://codeforces.com/contest/922/problem/D

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define ll long long

using namespace std;

struct shush
{
    ll s, h, sh;

    shush(){}
    shush(string &str)
    {
        s = 0, h = 0, sh = 0;

        ll numS = 0;
        for (char c: str)
        {
            if (c == 'h')
            {
                h++;
                sh += s;
            }
            else
            {
                s++;
            }
        }
    }

    ll before(const shush &o) const
    {
        return sh + o.sh + s * o.h;
    }

    bool operator < (const shush &o) const
    {
        ll res = before(o) - o.before(*this);
        if (res > 0)
        {
            return true;
        }
        else if (res == 0)
        {
            return s > o.s;
        }
        else
        {
            return false;
        }
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;

    vector <shush> shushes(n);
    string str;
    for (int i = 0; i < n; i++)
    {
        cin>>str;
        shushes[i] = shush(str);
    }
    sort(shushes.begin(), shushes.end());

    ll numS = 0, numSh = 0;
    for (shush obj: shushes)
    {
        numSh += obj.sh + numS * obj.h;
        numS += obj.s;
    }
    cout<<numSh<<'\n';

    return 0;
}

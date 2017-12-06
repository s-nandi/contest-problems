//ad-hoc, math
//https://open.kattis.com/problems/stararrangements (2017 Mid-Atlantic Regional)

#include <iostream>
#include <set>

using namespace std;

struct elem
{
    int a;
    int b;
    bool operator < (elem o) const
    {
        return a < o.a or (a == o.a and b < o.b);
    }
};

int main()
{
    int n;
    cin>>n;

    set <elem> valid;

    for (int i = 1; i < n; i++)
    {
        if (n % i == 0 and (n / i) / 2 > 0)
        {
            valid.insert({i, i});

            if ((n / i) % 2 == 1)
            {
                valid.insert({(n / i) / 2 + 1, (n / i) / 2});
            }
        }

        if ((n - i - 1) % (2 * i + 1) == 0 and i + 1 < n)
        {
            valid.insert({i + 1, i});
        }

    }

    cout<<n<<":"<<'\n';
    for (elem e: valid)
    {
        if (e.a > 1 and e.a < n)
            cout<<e.a<<","<<e.b<<'\n';
    }

    return 0;
}

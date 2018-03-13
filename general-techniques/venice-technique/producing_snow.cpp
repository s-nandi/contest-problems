//interval processing, venice technique (multiset)
//http://codeforces.com/problemset/problem/948/C

#include <iostream>
#include <vector>
#include <set>

using namespace std;

#define ll long long

template <class T>
struct veniceSet
{
    multiset <T> elements;
    T level = 0;

    void addElement(T v)
    {
       elements.insert(v + level);
    }

    void removeElement(T v)
    {
        elements.erase(elements.find(v + level));
    }

    void decreaseAll(T v)
    {
        level += v;
    }

    T getMin()
    {
        return (*elements.begin()) - level;
    }

    int size()
    {
        return elements.size();
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;

    vector <int> v(n), t(n);
    for (int i = 0; i < n; i++)
    {
       cin>>v[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin>>t[i];
    }

    veniceSet <ll> piles;
    for (int i = 0; i < n; i++)
    {
        piles.addElement(v[i]);
        piles.decreaseAll(t[i]);

        ll sol = piles.size() * (ll) t[i];

        while(piles.size() > 0 and piles.getMin() < 0)
        {
            ll lowest = piles.getMin();
            piles.removeElement(lowest);
            sol += lowest;
        }
        cout<<sol<<" ";
    }
    cout<<'\n';

    return 0;
}

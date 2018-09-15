// line sweep, priority queue, amortized complexity (you can non-trivially mod a value V at most log(v) times)
// http://codeforces.com/gym/101201
// 2016 Pacific NW Regional

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef long long ll;

struct person
{
    ll value;
    int ind;

    bool operator < (const person &o) const
    {
        return make_pair(value, ind) < make_pair(o.value, o.ind);
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    vector <ll> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    vector <ll> sol(q);
    vector <int> endTime(q);
    vector <vector<person>> startEvent(n);
    for (int i = 0; i < q; i++)
    {
        ll v; int l, r;
        cin >> v >> l >> r;
        --l, --r;

        sol[i] = v;
        endTime[i] = r;
        startEvent[l].push_back({v, i});
    }

    priority_queue <person, vector<person>, less<person>> pq;
    for (int i = 0; i < n; i++)
    {
        for (person p: startEvent[i])
            pq.push(p);
        while (!pq.empty() and pq.top().value >= a[i])
        {
            person p = pq.top();
            pq.pop();

            if (endTime[p.ind] < i)
                continue;

            p.value %= a[i];
            pq.push(p);

            sol[p.ind] = p.value;
        }
    }

    for (int i = 0; i < q; i++)
    {
        cout << sol[i] << '\n';
    }
}

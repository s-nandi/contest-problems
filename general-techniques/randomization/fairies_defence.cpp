// monte carlo simulation, find probability that a point in point set is the nearest neighbor to uniformly rng points
// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3261

#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

const ld INF = 1e20;

typedef ld ptT;
struct pt
{
    ptT x, y, z;

    pt operator - (const pt &o) const {return {x - o.x, y - o.y, z - o.z};}

    ptT norm2() const {return x * x + y * y + z * z;}
    ptT dist2(const pt &o) const {return (*this - o).norm2();}
};

struct random_generator
{
    mt19937 gen;
    uniform_real_distribution <ld> dist;

    random_generator() : gen(time(0)) {dist = uniform_real_distribution<ld>(0.0, 1.0);}

    ld get(ld l, ld r){return (r - l) * dist(gen) + l;}
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(3);

    int n;
    for(int test = 1; cin >> n and n != 0; test++)
    {
        int a, b, c;
        cin >> a >> b >> c;

        vector <pt> points(n);
        for (int i = 0; i < n; i++)
        {
            int x, y, z;
            cin >> x >> y >> z;
            points[i] = {x, y, z};
        }

        int iterations = 6e5;
        random_generator rng;
        vector <int> numHits(n);
        for (int iter = 0; iter < iterations; iter++)
        {
            pt p = {rng.get(0, a), rng.get(0, b), rng.get(0, c)};

            ld closest_dist = INF;
            int closest = -1;
            for (int i = 0; i < n; i++)
            {
                auto dist = points[i].dist2(p);
                if (dist < closest_dist)
                    closest_dist = dist, closest = i;
            }
            numHits[closest]++;
        }

        cout << "Case " << test << ": ";
        for (auto hits: numHits)
            cout << (long double) hits / iterations << " ";
        cout << '\n';
    }
}

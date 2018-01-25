//finding maximum area in histogram (stacks), invariant maintenance
//http://www.spoj.com/problems/HISTOGRA/

#include <iostream>
#include <vector>

using namespace std;

#define ll long long

struct bar
{
    int height, pos;
};

vector <bar> bars, candidates;

ll update(int rightBound)
{
    int leftBound = candidates.size() > 1 ? candidates.rbegin()[1].pos + 1: 0;
    return (ll) (rightBound - leftBound + 1) * candidates.back().height;
}

int main()
{
    int n;
    while (cin >> n)
    {
        if (n == 0) break;

        bars.clear(), candidates.clear();
        bars.resize(n);
        for (int i = 0; i < n; i++)
        {
            cin>>bars[i].height;
            bars[i].pos = i;
        }
        bars.push_back({-1, n});

        ll best = -1;
        for (int i = 0; i < bars.size(); i++)
        {
            while (candidates.size() > 0 and bars[i].height < candidates.back().height)
            {
                ll possible = update(i - 1);
                best = max(best, possible);
                candidates.pop_back();
            }
            candidates.push_back(bars[i]);
        }
        cout<<best<<'\n';
    }

    return 0;
}

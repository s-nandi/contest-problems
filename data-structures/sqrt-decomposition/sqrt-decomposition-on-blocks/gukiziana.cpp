//sqrt decomposition (sorted blocks), venice technique
//http://codeforces.com/contest/551/problem/E

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int sq = 2400;
const int INF = 1031231234;

typedef pair<int, int> ii;

struct block : vector<ii>
{
    int inc = 0;
    bool invalid = false;
};

void modifyPartial(block &b, int l, int r, int x)
{
    if (b.invalid) return;
    for (int i = 0; i < b.size(); i++)
    {
        if (b[i].second >= l and b[i].second <= r)
            b[i].first += x;
    }
    sort(b.begin(), b.end());
}

int findnum(block &b, int n, bool findFirst)
{
    int pos = -1, val = -1;
    if (!b.invalid)
    {
        n -= b.inc;
        if (findFirst)
        {
            auto it = lower_bound(b.begin(), b.end(), make_pair(n, -INF));
            if (it != b.end())
                pos = it -> second, val = it -> first;
        }
        else
        {
            auto it = upper_bound(b.begin(), b.end(), make_pair(n, INF));
            if (it != b.begin())
                --it, pos = it -> second, val = it -> first;
        }
    }
    if (pos != -1 and val == n) return pos;
    else return findFirst ? INF : -INF;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin>>n>>q;

    int nb = n / sq + 1;
    vector <block> blocks(nb);
    for (int i = 0; i < n; i++)
    {
        int a; cin>>a;
        blocks[i / sq].push_back({a, i});
    }

    for (int i = 0; i < nb; i++)
        sort(blocks[i].begin(), blocks[i].end());

    for (int i = 0; i < q; i++)
    {
        int type;
        cin>>type;
        if (type == 1)
        {
            int l, r, x;
            cin>>l>>r>>x;
            --l, --r;

            int lb = l / sq, rb = r / sq;
            if (lb == rb) modifyPartial(blocks[lb], l, r, x);
            else
            {
                modifyPartial(blocks[lb], l, (lb + 1) * sq - 1, x), lb++;
                modifyPartial(blocks[rb], rb * sq, r, x), rb--;
                for (int i = lb; i <= rb; i++) if (!blocks[i].invalid)
                {
                    blocks[i].inc += x;
                    if (blocks[i].inc > INF) blocks[i].invalid = true;
                }
            }
        }
        else
        {
            int y;
            cin>>y;

            int first = INF, last = -INF;
            for (int i = 0; i < nb; i++)
            {
                first = min(first, findnum(blocks[i], y, true));
                last = max(last, findnum(blocks[i], y, false));
            }
            if (first == INF or last == -INF) cout<<-1<<'\n';
            else cout<<last - first<<'\n';
        }
    }

    return 0;
}

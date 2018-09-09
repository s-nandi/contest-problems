// Matrix exponentiation, calculating recurrence transition via bitmask, trimming unused states
// http://codeforces.com/gym/100827/attachments
// 2014 Pacific NW Regional

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 1000000009;

typedef int matT;
struct matrix : vector<vector<matT>>
{
    matrix(int r, int c, int v = 0){resize(r, vector<matT>(c, v));}
};

matrix operator * (const matrix &a, const matrix &b)
{
    matrix c(a.size(), b[0].size());
    for (int i = 0; i < a.size(); ++i)
        for (int k = 0; k < b.size(); ++k)
            for (int j = 0; j < b[0].size(); ++j)
                c[i][j] = (c[i][j] + (ll) a[i][k] * b[k][j]) % MOD;
    return c;
}

matrix operator ^ (const matrix &a, ll p)
{
    matrix acc(a.size(), a.size()), res = a;
    for (int i = 0; i < a.size(); i++) acc[i][i] = 1;
    for (; p; p >>= 1)
    {
        if (p & 1) acc = acc * res;
        res = res * res;
    }
    return acc;
}

vector <int> dx = {-2, -1, 1, 2};
vector <int> dy = {-1, -2, -2, -1};

bool inBounds(int i, int j, int r, int c)
{
    return i >= 0 and j >= 0 and i < r and j < c;
}

// column ordered
int position(int i, int j, int r, int c)
{
    return j * r + i;
}

int n, m;
bool valid(int bm1, int bm2)
{
    for (int i = 0, j = 2; i < n; i++)
    {
        if (!(bm2 & (1 << i)))
            continue;
        for (int k = 0; k < 4; k++)
        {
            int nx = i + dx[k], ny = j + dy[k];
            if (!inBounds(nx, ny, n, 2))
                continue;

            int pos = position(nx, ny, n, 2);
            if (bm1 & (1 << pos))
                return false;
        }
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin>>T;
    while(T--)
    {
        cin>>n>>m;

        int block = 2 * n;
        int LOW = (1 << n) - 1;
        int HIGH = LOW << n;

        vector <int> states;
        // bits 0 to n - 1 are left column, n to 2n - 1 are right column
        for (int bm = 0; bm < (1 << block); bm++)
        {
            if (valid((bm & LOW) << n, (bm & HIGH) >> n))
                states.push_back(bm);
        }

        matrix transitions(states.size(), states.size());
        for (int i = 0; i < states.size(); i++)
        {
            for (int j = 0; j < states.size(); j++)
            {
                int bm = states[i], bm2 = states[j];
                if (((bm & HIGH) >> n) != (bm2 & LOW))
                    continue;
                if (valid(bm, (bm2 & HIGH) >> n))
                {
                    transitions[i][j] = 1;
                }
            }
        }

        matrix base(states.size(), 1, 1);
        matrix res = (transitions ^ m) * base;

        cout<<res[0][0]<<'\n';
    }

    return 0;
}

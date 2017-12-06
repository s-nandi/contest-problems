//segment tree, find kth >=, prefix sums for table

#include <iostream>
#include <vector>

using namespace std;

struct st
{
    int sz;
    vector <int> elem;

    st(int s)
    {
        sz = s;
        elem.resize(2 * sz);
    }

    void initVal(int pos, int val)
    {
        if (0 <= pos <= sz - 1)
        {
            elem[pos + sz] = val;
        }
    }

    void build()
    {
        for (int i = sz - 1; i >= 1; i--)
        {
            elem[i] = max(elem[i << 1], elem[i << 1 | 1]);
        }
    }

    void modify(int p, int val)
    {
        p += sz;
        elem[p] = val;

        while (p >= 2)
        {
            elem[p >> 1] = max(elem[p], elem[p ^ 1]);
            p >>= 1;
        }
    }

    int query(int l, int r)
    {
        int acc = 0;
        l += sz;
        r += sz;
        while (l <= r)
        {
            if (l & 1) //if l is odd
            {
                acc = max(acc, elem[l]);
                l++;
            }
            if (!(r & 1)) //if r is even
            {
                acc = max(acc, elem[r]);
                r--;
            }
            l >>= 1;
            r >>= 1;
        }

        return acc;
    }

    int findGreaterThan(int k, int start, bool fromFront)
    {
        int left, right;
        if (fromFront)
        {
            left = start;
            right = sz - 1;
        }
        else
        {
            left = 0;
            right = start;
        }


        if (query(left, right) < k)
        {
            return -1;
        }

        while(left < right)
        {
            int mid = (left + right) / 2;
            if (fromFront)
            {
                if (query(left, mid) >= k)
                {
                    right = mid;
                }
                else
                {
                    left = mid + 1;
                }
            }
            else
            {
                if (query(mid + 1, right) >= k)
                {
                    left = mid + 1;
                }
                else
                {
                    right = mid;
                }
            }
        }
        return left;
    }
};


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, r, k, p;
    while (cin>>n)
    {
        cin>>m>>r>>k>>p;
        if (n == 0)
        {
            break;
        }

        int h[n][m];
        vector <st> rows(n, st(m));
        vector <st> columns(m, st(n));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cin>>h[i][j];
                rows[i].initVal(j, h[i][j]);
                columns[j].initVal(i, h[i][j]);
            }
        }

        for (int i = 0; i < n; i++)
        {
            rows[i].build();
        }

        for (int i = 0; i < m; i++)
        {
            columns[i].build();
        }

        char dir;
        int allignment, height;

        for (int i = 0; i < k; i++)
        {
            cin>>dir>>allignment>>height;
            allignment--;

            int numHit = 0;
            int prev;
            if (dir == 'N' || dir == 'W')
            {
                prev = 0;
            }
            else
            {
                if (dir == 'E')
                {
                    prev = m - 1;
                }
                else
                {
                    prev = n - 1;
                }
            }

            while(numHit < r)
            {
                int pos;
                if (dir == 'N' || dir == 'W')
                {

                    if (dir == 'N')
                    {
                        pos = columns[allignment].findGreaterThan(height, prev, true);
                    }
                    else
                    {
                        pos = rows[allignment].findGreaterThan(height, prev, true);
                    }

                    prev = pos + 1;
                }
                else
                {
                    if (dir == 'S')
                    {
                        pos = columns[allignment].findGreaterThan(height, prev, false);
                    }
                    else
                    {
                        pos = rows[allignment].findGreaterThan(height, prev, false);
                    }
                    prev = pos - 1;
                }

                if (pos == -1)
                {
                    break;
                }
                int x, y;
                if (dir == 'E' || dir == 'W')
                {
                    x = allignment;
                    y = pos;
                }
                else
                {
                    x = pos;
                    y = allignment;
                }

                h[x][y]--;
                rows[x].modify(y, h[x][y]);
                columns[y].modify(x, h[x][y]);

                numHit++;
            }

        }

        vector <vector <int> > cumul(n, vector <int>(m));
        vector <vector <int> > colSum(n, vector <int>(m));

        for (int i = 0; i + p - 1 < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                int sum = 0;
                if (i == 0)
                {
                    for (int i2 = 0; i2 < p; i2++)
                    {
                        sum += h[i2][j];
                    }
                    colSum[i][j] = sum;
                }
                else
                {
                    sum = colSum[i - 1][j] - h[i - 1][j] + h[i + p - 1][j];
                    colSum[i][j] = sum;
                }

                if (j > 0)
                {
                    sum += cumul[i][j - 1];
                }

                cumul[i][j] = sum;
            }
        }

        int maxFound = -1;

        for (int i = 0; i + p - 1 < n; i++)
        {
            for (int j = 0; j + p - 1 < m; j++)
            {
                maxFound = max(maxFound, cumul[i][j + p - 1] - cumul[i][j - 1]);
            }
        }

        cout<<maxFound<<'\n';
    }

    return 0;
}

//segment tree, find kth above/below threshold, binary search with queries
//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&page=show_problem&problem=4869
//2014 Southeastern Europe Regional

#include <iostream>
#include <vector>

using namespace std;

struct segmentTree
{
    int sz;
    vector <int> elements;

    segmentTree(int s)
    {
        sz = s;
        elements.resize(2 * sz);
    }

    int& operator [] (int i)
    {
        return elements[i + sz];
    }

    void build()
    {
        for (int i = sz - 1; i >= 1; i--)
        {
            elements[i] = max(elements[i << 1], elements[i << 1 | 1]);
        }
    }

    void modify(int p, int val)
    {
        p += sz;
        elements[p] = val;
        while (p >= 2)
        {
            elements[p >> 1] = max(elements[p], elements[p ^ 1]);
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
            if (l & 1)
            {
                acc = max(acc, elements[l]);
                l++;
            }
            if (!(r & 1))
            {
                acc = max(acc, elements[r]);
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
    while (cin>>n>>m>>r>>k>>p)
    {
        int h[n][m];
        vector <segmentTree> rows(n, segmentTree(m));
        vector <segmentTree> columns(m, segmentTree(n));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cin>>h[i][j];
                rows[i][j] = h[i][j];
                columns[j][i] = h[i][j];
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

        for (int i = 0; i < k; i++)
        {
            char dir;
            int allignment, height;
            cin>>dir>>allignment>>height;
            --allignment;

            int prev;
            if (dir == 'N' || dir == 'W')
            {
                prev = 0;
            }
            else if(dir == 'E')
            {
                prev = m - 1;
            }
            else
            {
                prev = n -1;
            }

            for (int numHit = 0; numHit < r; numHit++)
            {
                int pos;
                if (dir == 'N')
                {
                    pos = columns[allignment].findGreaterThan(height, prev, true);
                    prev = pos + 1;
                }
                else if(dir == 'W')
                {
                    pos = rows[allignment].findGreaterThan(height, prev, true);
                    prev = pos + 1;
                }
                else if(dir == 'E')
                {
                    pos = rows[allignment].findGreaterThan(height, prev, false);
                    prev = pos - 1;
                }
                else
                {
                    pos = columns[allignment].findGreaterThan(height, prev, false);
                    prev = pos - 1;
                }
                if (pos == -1) break;

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
            }
        }

        int maxFound = -1;

        for (int i = 0; i + p - 1 < n; i++)
        {
            for (int j = 0; j + p - 1 < m; j++)
            {
                int total = 0;
                for (int i2 = 0; i2 < p; i2++)
                {
                    for (int j2 = 0; j2 < p; j2++)
                    {
                        total += h[i + i2][j + j2];
                    }
                }
                maxFound = max(maxFound, total);
            }
        }

        cout<<maxFound<<'\n';
    }

    return 0;
}

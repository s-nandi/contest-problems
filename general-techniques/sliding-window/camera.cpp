// sliding window
// http://codeforces.com/gym/101201
// 2016 Pacific NW Regional

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n, k, r;
    cin >> n >> k >> r;

    vector <int> a(n);
    for (int i = 0; i < k; i++)
    {
        int p;
        cin >> p;
        a[--p] = true;
    }

    int numCameras = 0;
    int sol = 0;
    for (int i = 0; i < n; i++)
    {
        numCameras += a[i];
        if (i >= r - 1)
        {
            if (numCameras < 2)
            {
                for (int j = i; j >= 0; j--) if (!a[j])
                {
                    a[j] = true;
                    sol++;
                    if (++numCameras == 2)
                        break;
                }
            }
            numCameras -= a[i - r + 1];
        }
    }
    cout<<sol<<'\n';
}

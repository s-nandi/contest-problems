// sliding window (window size lower bounded -> find min number of non-overlapping windows to cover range)
// http://codeforces.com/contest/1040/problem/B

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin>>n>>k;

    if (n <= 2 * k + 1)
    {
        cout<<1<<'\n';
        int sol = (n + 1) / 2;
        cout<<sol<<'\n';
    }
    else
    {
        vector <int> cuts;
        int rem = n % (2 * k + 1);
        if (rem != 0)
        {
            if (rem < k + 1)
                rem = k + 1;
            cuts.push_back(rem);
            n -= rem;
        }
        while (n)
        {
            if (n >= 2 * k + 1)
            {
                cuts.push_back(2 * k + 1);
                n -= 2 * k + 1;
            }
            else
            {
                cuts.push_back(n);
                break;
            }
        }

        int prev = 1;
        bool first = true;
        vector <int> sol;
        for (int cut: cuts)
        {
            if(first)
            {
                int pos = cut - k;
                sol.push_back(pos);
            }
            else
            {
                int pos = prev + k;
                sol.push_back(pos);
            }
            prev += cut;
            first = false;
        }
        cout<<sol.size()<<'\n';
        for (int elem: sol)
            cout<<elem<<" ";
        cout<<'\n';
    }

    return 0;
}

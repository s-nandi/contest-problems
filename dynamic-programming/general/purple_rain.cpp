//dynamic programming, kadane's algorithm
//https://open.kattis.com/problems/purplerain

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int n;

struct sol
{
    int val;
    int l;
    int r;
    bool operator < (sol b) const
    {
        if (val != b.val)
        {
            return val > b.val;
        }
        else
        {
            return make_pair(l, r) < make_pair(b.l, b.r);
        }
    }
};

sol kadane(vector <int> &arr)
{
    int curr = 0;
    sol maxSol = {-1, -1, -1};
    int left = 0;
    int right = -1;
    for (int i = 0; i < n; i++)
    {
        if (curr + arr[i] >= arr[i])
        {
            curr += arr[i];
            right++;
        }
        else
        {
            curr = arr[i];
            left = i;
            right = i;
        }
        sol currSol = {curr, left, right};
        if (currSol < maxSol)
        {
            maxSol = currSol;
        }
    }
    return maxSol;
}

int main()
{
    string s;
    cin>>s;
    n = s.length();

    vector <int> norm(n);
    vector <int> inv(n);

    for (int i = 0; i < n; i++)
    {
        char c = s[i];
        if (c == 'R')
        {
            norm[i] = 1;
            inv[i] = -1;
        }
        else
        {
            norm[i] = -1;
            inv[i] = 1;
        }
    }

    sol sol1= kadane(norm);
    sol sol2 = kadane(inv);

    if (sol1 < sol2)
    {
        cout<<sol1.l + 1<<" "<<sol1.r + 1<<'\n';
    }
    else
    {
        cout<<sol2.l + 1<<" "<<sol2.r + 1<<'\n';
    }

   return 0;
}

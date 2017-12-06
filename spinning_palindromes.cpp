//Saujas Nandi
#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>

using namespace std;

#define INF 12312312;

int matchCost(vector <int> &v)
{
    int n = v.size();
    int counter = 0;
    for (int i = 0; i < n/2; i++)
    {
        counter += abs(v[i] - v[n - i - 1]);
    }

    return counter;
}

void increment(vector <int> &v, int pos)
{
    bool operate = true;
    while (pos < v.size() and operate)
    {
        if (v[pos] != 9)
        {
            v[pos]++;
            operate = false;
        }
        else
        {
            v[pos] = 0;
        }
        pos++;
    }
}


int main()
{
    string s;
    cin>>s;

    vector <int> orig(s.length());
    for (int i = 0; i < s.length(); i++)
    {
        orig[s.length() - i - 1] = s[i] - '0';
    }

    int power = (1 << ((s.length() + 1)/2));
    int sol = INF;
    int lmid, rmid;

    if (s.length() & 1)
    {
        rmid = s.length()/2 - 1;
        lmid = s.length()/2 + 1;
    }
    else
    {
        rmid = s.length()/2 - 1;
        lmid = s.length()/2;
    }

    for (int bm = 0; bm < power; bm++)
    {
        int overflowCost = 0;
        vector <int> start(orig);

        for (int i = 0; i < s.length()/2; i++)
        {
            if ((1 << i) & bm)
            {
                int leftInd = lmid + i;
                int rightInd = rmid - i;
                int leftVal = start[leftInd];
                int rightVal = start[rightInd];
                if (leftVal > rightVal)
                {
                    overflowCost += 10 - leftVal;
                    start[leftInd] = 0;
                    increment(start, leftInd + 1);

                }
                else if (rightVal > leftVal)
                {
                    overflowCost += 10 - rightVal;
                    start[rightInd] = 0;
                    increment(start, rightInd + 1);
                }
            }
        }

        int res = matchCost(start) + overflowCost;

        sol = min(sol, res);
    }
    cout<<sol<<'\n';
}

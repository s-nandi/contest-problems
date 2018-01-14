//calendar, bitmask
//http://codeforces.com/contest/899/problem/B

#include <iostream>
#include <vector>

using namespace std;

vector <int> months[2];

int main()
{
    int n;
    cin>>n;

    vector <int> expected(n);
    for (int i = 0; i < n; i++)
    {
        cin>>expected[i];
    }

    months[0] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    months[1] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    vector <int> masks = {0, 1, 2, 4};

    for (int m: masks)
    {
        vector <int> solMonths[3];
        for (int i = 0; i < 3; i++)
        {
            solMonths[i] = months[(m & (1 << i)) != 0];
        }

        for (int i = 0; i < 12; i++)
        {
            bool fail = false;
            for (int j = i; j < i + n; j++)
            {
                if (solMonths[j / 12][j % 12] != expected[j - i])
                {
                    fail = true;
                    break;
                }
            }
            if (!fail)
            {
                cout<<"Yes"<<'\n';
                return 0;
            }
        }
    }

    cout<<"No"<<'\n';

    return 0;
}

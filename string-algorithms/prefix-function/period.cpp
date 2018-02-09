//prefix function, detecting periodic prefixes
//http://www.spoj.com/problems/PERIOD/

#include <iostream>
#include <vector>

using namespace std;

vector <int> prefixFunction(string &s)
{
    int n = s.length();
    vector <int> pf(n);

    for (int i = 1; i < n; i++)
    {
        int j = pf[i - 1];
        while (j > 0 and s[i] != s[j])
        {
            j = pf[j - 1];
        }
        if (s[i] == s[j]) pf[i] = j + 1;
        else pf[i] = 0;
    }

    return pf;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin>>T;

    for (int test = 1; test <= T; test++)
    {
        int n;
        cin>>n;

        string s;
        cin>>s;

        auto pf = prefixFunction(s);
        vector <int> cycleLength[n + 1];

        for (int i = 1; i <= n; i++)
        {
            cycleLength[i].push_back(i - 1);
        }

        cout<<"Test case #"<<test<<'\n';
        for (int i = 0; i < n; i++)
        {
            if (pf[i] != 0)
            {
                int len = i + 1 - pf[i];
                if (cycleLength[len].rbegin()[0] == pf[i] - 1)
                {
                    cout<<i + 1<<" "<<(i + 1) / len<<'\n';
                    cycleLength[len].push_back(i);
                }
            }
        }
    }

    return 0;
}

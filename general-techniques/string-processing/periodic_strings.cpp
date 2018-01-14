//string rotation
//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&page=show_problem&problem=5970
//2016 Mid-Atlantic Regional

#include <iostream>

using namespace std;

bool check(string &prev, string &curr)
{
    for (int i = 0; i < prev.length(); i++)
    {
        if (prev[i] != curr[(i + 1) % prev.length()])
        {
            return false;
        }
    }
    return true;
}

bool solve(string &s, int k)
{
    string prev = s.substr(0, k);

    for (int i = k; i < s.length(); i += k)
    {
        string curr = s.substr(i, k);

        if (!check(prev, curr))
        {
            return false;
        }

        prev = curr;
    }
    return true;
}

int main()
{
    string s;

    while(cin>>s)
    {
        for (int i = 1; i <= s.length(); i++)
        {
            if (s.length() % i != 0) continue;

            if(solve(s, i))
            {
                cout<<i<<'\n';
                break;
            }
        }
    }

    return 0;
}

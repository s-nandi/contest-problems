//interval processing (amortized runtime - sum of step costs bounded by # of points)
//https://codeforces.com/contest/909/problem/D

#include <iostream>
#include <vector>

using namespace std;

const int INF = 1231231234;

struct block
{
    char c;
    int len;
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string s;
    cin>>s;

    s += 'A';

    vector <block> blocks;

    char curr = s[0];
    int currLen = 1;
    for (int i = 1; i < s.length(); i++)
    {
        if (s[i] == curr)
        {
            currLen++;
        }
        else
        {
            blocks.push_back({curr, currLen});
            curr = s[i], currLen = 1;
        }
    }

    int sol = 0;
    while (blocks.size() > 1)
    {
        int steps = INF;
        for (int i = 0; i < blocks.size(); i++)
        {
            int needed;
            if (i == 0 or i + 1 == blocks.size())
            {
                needed = blocks[i].len;
            }
            else
            {
                needed = (blocks[i].len + 1) / 2;
            }
            steps = min(steps, needed);
        }

        sol += steps;
        for (int i = 0; i < blocks.size(); i++)
        {
            blocks[i].len -= (i == 0 or i + 1 == blocks.size()) ? steps : 2 * steps;
        }

        vector <block> nonempty;
        for (int i = 0; i < blocks.size(); i++)
        {
            if (blocks[i].len > 0)
                nonempty.push_back(blocks[i]);
        }

        blocks.clear();
        for (int i = 0; i < nonempty.size(); i++)
        {
            if (i == 0)
            {
                blocks.push_back(nonempty[0]);
            }
            else
            {
                if (blocks.back().c == nonempty[i].c)
                {
                    blocks.back().len += nonempty[i].len;
                }
                else
                {
                    blocks.push_back(nonempty[i]);
                }
            }
        }
    }

    cout<<sol<<'\n';

    return 0;
}

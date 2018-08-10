// traversal on filled binary tree
// https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=5385
// 2015 Greater NY Regional

#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin>>T;
    for (int test = 1; test <= T; test++)
    {
        int k, a, b;
        char slash;
        cin>>k>>a>>slash>>b;

        vector <int> sequence;
        int depth = 0;
        while (a != 1 or b != 1)
        {
            if (a > b)
            {
                sequence.push_back(1);
                a -= b;
            }
            else
            {
                sequence.push_back(0);
                b -= a;
            }
            depth++;
        }
        reverse(sequence.begin(), sequence.end());

        int pos = 1;
        for (int i = 0; i < depth; i++)
        {
            if (sequence[i] == 1)
                pos = pos * 2 + 1;
            else
                pos = 2 * pos;
        }
        cout<<k<<" "<<pos<<'\n';
    }

    return 0;
}

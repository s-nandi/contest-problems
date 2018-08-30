// Simulation (queue)
// https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=5998
// 2016 East Central Regional

#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    while (cin >> n)
    {
        vector <string> names(n);
        for (int i = 0; i < n; i++)
        {
            cin>>names[i];
        }
        string results;
        cin>>results;
        results += 'Q'; // sentinel to avoid edge case

        int sides[2][2] = {{0, 2}, {1, 3}};
        int times[2][2] = {{0, 1}, {0, 1}};
        queue <int> q;
        for (int i = 4; i < n; i++)
        {
            q.push(i);
        }

        int timer = 2;
        int longest = 0, currLength = 0;
        int prevWinner = -1;
        pair <int, int> currWinners = {-1, -1};
        vector <pair<int, int>> sol;
        for (char c: results)
        {
            int winner = c == 'B';
            if (c == 'Q' or winner != prevWinner)
            {
                if (currLength > longest)
                {
                    longest = currLength;
                    sol = {currWinners};
                }
                else if(currLength == longest)
                {
                    sol.push_back(currWinners);
                }

                if (c == 'Q')
                    continue;

                currLength = 1;
                prevWinner = winner;
                if (times[winner][0] < times[winner][1])
                    currWinners = {sides[winner][0], sides[winner][1]};
                else
                    currWinners = {sides[winner][1], sides[winner][0]};
            }
            else
            {
                currLength++;
            }

            for (int i = 0; i < 2; i++)
            {
                swap(sides[i][0], sides[i][1]);
                swap(times[i][0], times[i][1]);
            }
            int removed = sides[1 - winner][0];
            sides[1 - winner][0] = q.front();
            times[1 - winner][0] = timer++;
            q.pop();
            q.push(removed);
        }
        for (auto p: sol)
        {
            cout<<names[p.first]<<" "<<names[p.second]<<'\n';
        }
    }

    return 0;
}

// simulation (traversing grid w/ rotation and forward instruction)
// https://open.kattis.com/problems/glitchbot
// 2017 North American Qualifier

#include <bits/stdc++.h>

using namespace std;

vector <int> dx = {0, -1, 0, 1};
vector <int> dy = {-1, 0, 1, 0};

map <string, int> mapping = {{"Left", 0}, {"Forward", 1}, {"Right", 2}};
vector <string> invmapping = {"Left", "Forward", "Right"};

struct state
{
    int x, y, dir;

    state feed(int command) // 0 is left, 1 is forward, 2 is right
    {
        state res = *this;
        if (command == 0)
            res.dir = (res.dir + 3) % 4;
        else if (command == 1)
            res.x += dx[dir], res.y += dy[dir];
        else
            res.dir = (res.dir + 1) % 4;
        return res;
    }
};

bool simulate(int tx, int ty, vector <int> &commands)
{
    state curr = {0, 0, 2};
    for (int command: commands)
        curr = curr.feed(command);
    return curr.x == tx and curr.y == ty;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int x, y;
    cin >> x >> y;

    int n;
    cin >> n;

    vector <int> commands(n);
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        commands[i] = mapping[s];
    }

    int pos = -1, dir = -1;
    for (int i = 0; i < n; i++)
    {
        int old = commands[i];
        for (int change = 0; change < 3; change++) if (change != old)
        {
            commands[i] = change;
            if (simulate(x, y, commands))
            {
                pos = i + 1;
                dir = change;
                break;
            }
            commands[i] = old;
        }
        if (pos != -1)
            break;
    }

    cout << pos << " " << invmapping[dir] << '\n';

    return 0;
}

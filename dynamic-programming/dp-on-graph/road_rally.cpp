//dynamic programming (grid), BFS
//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3962
//2011 Mid-Atlantic Regional

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <utility>

using namespace std;

#define INF 123123123

int H, W;

struct pt
{
    int x;
    int y;
    bool operator < (pt o) const
    {
        return x < o.x or (x == o.x and y < o.y);
    }
};

struct state
{
    int x;
    int y;
    int dx;
    int dy;
    int goal;

    int t;
};

bool isValid(pt p, vector <vector<char>> &grid)
{
    if (p.x >= H or p.x < 0 or p.y >= W or p.y < 0) return false;
    char c = grid[p.x][p.y];

    return !(c == 'x' or c == 'X');
}

const int dxarr[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
const int dyarr[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

int bfs(int start, vector <vector <char>> &grid, vector <pt> &checkpoints, int last)
{
    queue <state> q;

    pt currPos = checkpoints[start];

    map <pt, int> d[40][40][11];

    q.push({currPos.x, currPos.y, 0, 0, 1, 0});
    pt temp = {0, 0};
    d[currPos.x][currPos.y][1][temp] = 0;

    while (!q.empty())
    {
        state curr = q.front();
        q.pop();

        int newGoal = curr.goal;
        if (curr.x == checkpoints[curr.goal].x and curr.y == checkpoints[curr.goal].y)
        {
            if (curr.goal == last)
            {
                return curr.t;
            }
            else
            {
                newGoal++;
            }
        }

        pt p = {curr.x + curr.dx, curr.y + curr.dy};

        for (int i = 0; i < 9; i++)
        {
            pt newPoint = {p.x + dxarr[i], p.y + dyarr[i]};
            pt newDyDx = {newPoint.x - curr.x, newPoint.y - curr.y};
            int newT = curr.t + 1;

            state newState = {newPoint.x, newPoint.y, newDyDx.x, newDyDx.y, newGoal, newT};

            if (isValid(newPoint, grid) and d[newPoint.x][newPoint.y][newGoal].count(newDyDx) == 0)
            {
                d[newPoint.x][newPoint.y][newGoal][newDyDx] = newT;
                q.push(newState);
            }
        }
    }

    return -1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while(cin>>W>>H)
    {
        if (W == 0 and H == 0)
        {
            break;
        }

        int maxCheckpoint = -1;
        vector <pt> checkpoints(10);
        vector <vector<char> > grid(H, vector<char>(W));

        cin.ignore();

        for (int i = 0; i < H; i++)
        {
            string s;
            getline(cin, s);

            for (int j = 0; j < W; j++)
            {
                char c = s[j];
                grid[i][j] = c;
                if (c != 'x' and c != 'X' and c != ' ')
                {
                    checkpoints[c - '0'] = {i, j};
                    maxCheckpoint = max(maxCheckpoint, c - '0');
                }
            }
        }

        int sol = bfs(0, grid, checkpoints, maxCheckpoint);

        cout<<sol<<'\n';
    }

    return 0;
}

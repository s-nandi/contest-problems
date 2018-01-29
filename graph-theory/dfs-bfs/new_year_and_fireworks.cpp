//dfs, multi-dimensional state
//http://codeforces.com/problemset/problem/750/D

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

#define MAXN 302

vector <int> dx = {-1, -1, 0, 1, 1, 1, 0, -1};
vector <int> dy = {0, -1, -1, -1, 0, 1, 1, 1};

struct state
{
    int x;
    int y;
    int direction;
    int remaining;
    int level;
};

vector <int> range;
bool visited[MAXN][MAXN][9][6][31];
int marked[MAXN][MAXN];

void dfs(state curr)
{
    if (visited[curr.x][curr.y][curr.direction][curr.remaining][curr.level]) return;
    visited[curr.x][curr.y][curr.direction][curr.remaining][curr.level] = true;
    marked[curr.x][curr.y] = 1;

    if (curr.remaining > 0)
    {
        state next = {curr.x + dx[curr.direction], curr.y + dy[curr.direction], curr.direction, curr.remaining - 1, curr.level};
        dfs(next);
    }
    else
    {
        if (curr.level + 1 == range.size()) return;
        int leftDirection = (curr.direction - 1 + 8) % 8;
        int rightDirection = (curr.direction + 1) % 8;

        state rightState = {curr.x + dx[rightDirection], curr.y + dy[rightDirection], rightDirection, range[curr.level + 1] - 1, curr.level + 1};
        state leftState = {curr.x + dx[leftDirection], curr.y + dy[leftDirection], leftDirection, range[curr.level + 1] - 1, curr.level + 1};
        dfs(rightState);
        dfs(leftState);
    }
}


int main()
{
    int n;
    cin>>n;

    memset(visited, false, sizeof(visited));
    memset(marked, 0, sizeof(marked));
    range.resize(n);

    for (int i = 0; i < n; i++)
    {
        cin>>range[i];
    }

    state initial = {150, 150, 0, range[0] - 1, 0};
    dfs(initial);

    int sol = 0;
    for (int i = 0; i < MAXN; i++)
    {
        for (int j = 0; j < MAXN; j++)
        {
            sol += marked[i][j];
        }
    }
    cout<<sol<<'\n';
    
    return 0;
}

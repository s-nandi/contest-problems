// BFS (large state), traversing on hexagonal grid
// https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4112
// 2012 Mid-Central Regional

#include <bits/stdc++.h>

using namespace std;

vector <int> dx = {0, -1, -1, 0, 1, 1};
vector <int> odd_dy = {-1, -1, 0, 1, 0, -1};
vector <int> even_dy = {-1, 0, 1, 1, 1, 0};

int r, c, n;
char grid[8][8];

bool inBounds(int i, int j)
{
    if (i < 0 or i >= r) return false;
    if (j < 0) return false;
    if (i & 1 and j >= c + 1) return false;
    if (!(i & 1) and j >= c) return false;
    return true;
}

int getIndex(int i, int j)
{
    int prev = (i / 2) * (2 * c + 1);
    int after = (i & 1) ? c + j : j;
    return prev + after;
}

struct state
{
    int x, y, match;
    bitset <64> visited;
    string pattern = "";
    bool reachedBottom = false;
};

string solve(int sx, int sy)
{
    queue <state> q;

    state start;
    start.x = sx, start.y = sy;
    start.visited[getIndex(sx, sy)] = 1;
    start.pattern += grid[sx][sy];

    q.push(start);
    while (!q.empty())
    {
        state curr = q.front();
        q.pop();

        if (curr.x == r - 1) curr.reachedBottom = true;
        else if(curr.reachedBottom and curr.x == 0 and curr.match == 0)
            return curr.pattern;

        for (int k = 0; k < 6; k++)
        {
            int nx, ny;
            if (curr.x & 1)
                ny = curr.y + odd_dy[k];
            else
                ny = curr.y + even_dy[k];
            nx = curr.x + dx[k];

            if (!inBounds(nx, ny)) continue;
            if (curr.visited[getIndex(nx, ny)] == 1) continue;

            state neighbor = curr;
            neighbor.x = nx, neighbor.y = ny;
            neighbor.visited[getIndex(nx, ny)] = 1;
            neighbor.pattern += grid[nx][ny];

            if (curr.pattern.length() >= n)
            {
                char expected = curr.pattern[curr.match % n];
                if (grid[nx][ny] != expected) continue;
                neighbor.match = (neighbor.match + 1) % n;
            }

            q.push(neighbor);
        }
    }
    return "";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    while (true)
    {
        cin>>r;
        if (r == 0) break;
        cin>>c>>n;

        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c + (i & 1); j++)
            {
                cin>>grid[i][j];
            }
        }

        string best = "";
        for (int j = 0; j < c; j++)
        {
            string possible = solve(0, j);
            if (best == "" or (possible != "" and possible.length() < best.length()))
                best = possible;
        }

        if (best == "")
            cout<<"no solution"<<'\n';
        else
            cout<<best<<'\n';
    }

    return 0;
}

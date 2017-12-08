//edit distance, dijkstra, dynamic programming
//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&category=757&page=show_problem&problem=5715
//2016 Mid-Atlantic Regional

#include <iostream>
#include <queue>
#include <map>
using namespace std;

#define INF 123123123

int H, W;

struct node
{
    int i, j, at, edit;
    bool operator >  (node b) const
    {
        return edit > b.edit;
    }
};

string s;

int dijkstra(vector <vector<char>> &grid, int starti, int startj, int endi, int endj)
{
    priority_queue <node, vector<node>, greater<node>> q;
    int d[H][W][s.length() + 1];

    for (int k = 0; k <= s.length(); k++)
    {
        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[0].size(); j++)
            {
                d[i][j][k] = INF;
            }
        }
    }

    q.push({starti, startj, 0, 0});
    vector <char> dir = {'D', 'U', 'R', 'L'};
    vector <int> dx = {1, -1, 0, 0};
    vector <int> dy = {0, 0, 1, -1};

    while (!q.empty())
    {
        node curr = q.top();
        q.pop();

        if (curr.i == endi and curr.j == endj)
        {
            return curr.edit;
        }


        for (int i = 0; i < 4; i++)
        {
            node newNode;
            int newi, newj, newat, newedit;
            if (curr.i + dx[i] < 0 or curr.i + dx[i] >= H or curr.j + dy[i] < 0 or curr.j + dy[i] >= W or grid[curr.i + dx[i]][curr.j + dy[i]] == '#')
            {
                newi = curr.i;
                newj = curr.j;
            }
            else
            {
                newi = curr.i + dx[i];
                newj = curr.j + dy[i];
            }
            if (curr.at < s.length() and s[curr.at] == dir[i])
            {
                newat = curr.at + 1;
                newedit = curr.edit;
            }
            else
            {
                newat = curr.at;
                newedit = curr.edit + 1;
            }
            newNode = {newi, newj, newat, newedit};
            if (newNode.edit < d[newNode.i][newNode.j][newNode.at])
            {
                q.push(newNode);
                d[newNode.i][newNode.j][newNode.at] = newNode.edit;
            }
        }
    }

    int res = -1;

    for (int k = 0; k < s.length(); k++)
    {
        if (res == -1 or d[endi][endj][k] < res)
        {
            res = d[endi][endj][k];
        }
    }

    return res;

}

int main()
{
    while (cin>>H>>W)
    {
        vector <vector<char>> grid(H, vector<char>(W));

        int starti, startj;
        int endi, endj;
        for (int i = 0; i < H; i++)
        {
            for (int j = 0; j < W; j++)
            {
                cin>>grid[i][j];
                if (grid[i][j] == 'S' or grid[i][j] == 'R')
                {
                    starti = i;
                    startj = j;
                }
                if (grid[i][j] == 'E' or grid[i][j] == 'G')
                {
                    endi = i;
                    endj = j;
                }
            }
        }
        cin>>s;

        int res = dijkstra(grid, starti, startj, endi, endj);
        cout<<res<<endl;

    }

    return 0;
}

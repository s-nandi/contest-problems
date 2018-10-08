// trie (checking if a prefix exists), backtracking (enumerate nCk)
// https://naq18.kattis.com/problems/bingoties
// 2018 North American Qualifier

#include <bits/stdc++.h>

using namespace std;

typedef array<array<int, 5>, 5> card;

const int INF = 1231231234;

const int alpha = 3005;
struct node
{
    array <int, alpha> to;
    bool isEnd = false;

    node(){fill(to.begin(), to.end(), -1);}
};

struct trie
{
    vector <node> elements;
    int sz;

    trie(){elements.resize(1); sz = 1;}

    int next(int i, int t){return elements[i].to[t];}

    void addString(const array <int, 5> &v)
    {
        int curr = 0;
        for (int mc: v)
        {
            if (next(curr, mc) == -1)
            {
                elements.emplace_back();
                elements[curr].to[mc] = sz++;
            }
            curr = next(curr, mc);
        }
        elements[curr].isEnd = true;
    }

    bool contained(const vector <int> &v)
    {
        int curr = 0;
        for (int mc: v)
        {
            if (next(curr, mc) == -1)
                return false;
            curr = next(curr, mc);
        }
        return elements[curr].isEnd;
    }
};

vector <card> cards;
trie tr;

bool backtrack(vector <int> &curr, vector <int> &options, int last)
{
    if (curr.size() == 5)
        return !tr.contained(curr);
    else
    {
        for (int i = last; i < options.size(); i++)
        {
            curr.push_back(options[i]);
            if (!backtrack(curr, options, i + 1))
                return false;
            curr.pop_back();
        }
        return true;
    }
}


bool isBad(int i, int j, int r1, int r2, int c1, int c2)
{
    vector <int> rem;
    for (int it = 0; it < 5; it++)
    {
        if (it != c1)
            rem.push_back(cards[i][r1][it]);
        if (it != c2)
            rem.push_back(cards[j][r2][it]);
    }
    sort(rem.begin(), rem.end());

    vector <int> curr;
    return backtrack(curr, rem, 0);
}

int main()
{
   ios_base::sync_with_stdio(false);
   cin.tie(0);

    int n;
    cin >> n;

    cards.resize(n);
    for (int i = 0; i < n; i++)
    {
       for (int x = 0; x < 5; x++)
       {
           for (int y = 0; y < 5; y++)
               cin >> cards[i][x][y];
           sort(cards[i][x].begin(), cards[i][x].end());
           tr.addString(cards[i][x]);
       }
    }

    pair <int, int> best = {INF, INF};
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            for (int row = 0; row < 5; row++)
            {
                for (int row2 = 0; row2 < 5; row2++)
                {
                    for (int l = 0, r = 0; l < 5 and r < 5;)
                    {
                        if (cards[i][row][l] < cards[j][row2][r])
                            l++;
                        else if(cards[i][row][l] > cards[j][row2][r])
                            r++;
                        else
                        {
                            if (isBad(i, j, row, row2, l, r))
                                best = min(best, {i, j});
                            l++, r++;
                        }
                    }
                }
            }
        }
    }
    if (best.first != INF)
        cout << best.first + 1 << " " << best.second + 1 << '\n';
    else
        cout << "no ties" << '\n';
}

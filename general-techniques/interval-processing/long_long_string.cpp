//interval processing (inefficient rope)
//https://open.kattis.com/problems/longlongstrings (2017 Mid-Atlantic Regional)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define ll long long
#define MAXN 10000000000

struct node
{
    ll left;
    ll right;
    bool operator == (node b) const
    {
        return (left == b.left and right == b.right);
    }
    ll size()
    {
        return right - left + 1;
    }
    bool valid()
    {
        return right >= left;
    }
};

vector <node> p[2];

ll charMap(char c)
{
    ll val = c - 'A';
    return -1LL * (val + 1);
}

void modifyChar(vector <node> &program, ll pos, char newChar)
{
    bool del = newChar == '\0' ? true : false;
    bool modified = false;

    vector <node> newProgram;

    for (int i = 0; i < program.size(); i++)
    {
        if (!modified)
        {
            if (program[i].size() < pos)
            {
                pos -= program[i].size();
                newProgram.push_back(program[i]);
            }
            else
            {
                node leftSegment, newNode, rightSegment;

                if (del)
                {
                    leftSegment = {program[i].left, program[i].left + pos - 2};
                    newNode = {0, -1};
                    rightSegment = {program[i].left + pos, program[i].right};
                }
                else
                {
                    leftSegment = {program[i].left, program[i].left + pos - 2};
                    newNode = {charMap(newChar), charMap(newChar)};
                    rightSegment = {program[i].left + pos - 1, program[i].right};
                }

                if (leftSegment.valid())
                {
                    newProgram.push_back(leftSegment);
                }
                if (newNode.valid())
                {
                    newProgram.push_back(newNode);
                }
                if (rightSegment.valid())
                {
                    newProgram.push_back(rightSegment);
                }

                modified = true;
            }
        }
        else
        {
            newProgram.push_back(program[i]);
        }
    }

    program = newProgram;
}

bool continues(node a, node b)
{
    if (a.right + 1 == b.left and a.right >= 0 and b.right >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void repair(vector <node> &program)
{
    vector <node> newProgram;
    bool started = true;
    node prev;
    for (int i = 0; i < program.size(); i++)
    {
        if (started)
        {
            prev = program[i];
            started = false;
        }
        else
        {
            if (continues(prev, program[i]))
            {
                prev = {prev.left, program[i].right};
            }
            else
            {
                newProgram.push_back(prev);
                prev = program[i];
            }
        }
    }
    newProgram.push_back(prev);

    program = newProgram;
}

int main()
{
    char com;
    int curr = 0;
    p[0] = {{1, MAXN}};
    p[1] = {{1, MAXN}};

    while (cin >> com)
    {
        if (com == 'E')
        {
            if (curr == 0)
            {
                curr = 1;
            }
            else
            {
                break;
            }
        }
        else
        {
            if (com == 'D')
            {
                ll i;
                cin>>i;
                modifyChar(p[curr], i, '\0');
            }
            else if(com == 'I')
            {
                ll i;
                char c;
                cin>>i>>c;
                modifyChar(p[curr], i, c);
            }
        }
    }

    repair(p[0]);
    repair(p[1]);

    if (p[0].size() != p[1].size())
    {
        cout<<1<<'\n';
    }
    else
    {
        bool same = true;
        for (int i = 0; i < p[0].size(); i++)
        {
            if (!(p[0][i] == p[1][i]))
            {
                same = false;
                break;
            }
        }
        if (same)
        {
            cout<<0<<'\n';
        }
        else
        {
            cout<<1<<'\n';
        }
    }

    return 0;
}

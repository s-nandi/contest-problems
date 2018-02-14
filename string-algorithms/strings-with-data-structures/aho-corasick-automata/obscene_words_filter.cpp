//aho corasick (map, pattern partition)
//http://acm.timus.ru/problem.aspx?space=1&num=1269

#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

#define INF 1231231234
#define MAXN 100001
#define alpha 256

int mapping(unsigned char c)
{
    return int(c);
}

struct node
{
    map <int, int> to;
    int prefixLink, matchLink, len;

    node()
    {
        prefixLink = -1, matchLink = -1, len = 0;
    }
};

struct ahoCorasick
{
    vector <node> elements;
    int numNodes;

    ahoCorasick()
    {
        numNodes = 1;
        elements.resize(MAXN);
    }

    void addWord(string &s)
    {
        int curr = 0;
        for (char c: s)
        {
            int mc = mapping(c);
            if (next(curr, mc) == -1)
            {
                elements[curr].to[mc] = numNodes++;
                elements[next(curr, mc)].len = elements[curr].len + 1;
            }
            curr = next(curr, mc);
        }
        elements[curr].matchLink = curr;
    }

    int next(int curr, int transition)
    {
        return elements[curr].to.count(transition) ? elements[curr].to[transition] : -1;
    }

    void build()
    {
        elements[0].prefixLink = 0;
        bfs(0);
    }

    void bfs(int root)
    {
        queue <int> q;
        q.push(root);

        while (!q.empty())
        {
            int curr = q.front();
            q.pop();

            int j = elements[curr].prefixLink;

            if (elements[curr].matchLink == -1) elements[curr].matchLink = elements[j].matchLink;

            for (int c = 0; c < alpha; c++) if (next(curr, c) != -1)
            {
                while (j > 0 and next(j, c) == -1)
                {
                    j = elements[j].prefixLink;
                }
                if (curr != 0 and next(j, c) != -1) elements[next(curr, c)].prefixLink = next(j, c);
                else elements[next(curr, c)].prefixLink = 0;

                q.push(next(curr, c));
            }
        }
    }

    int match(string &s)
    {
        int j = 0, res = INF;
        for (int i = 0; i < s.length(); i++)
        {
            int c = mapping(s[i]);
            while (j > 0 and next(j, c) == -1)
            {
                j = elements[j].prefixLink;
            }

            if (next(j, c) != -1) j = next(j, c);
            else j = 0;

            if (elements[j].matchLink != -1)
            {
                res = min(res, i - elements[elements[j].matchLink].len + 1);
            }

        }
        return res;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;
    cin.ignore();

    vector <string> strings[2];

    for (int i = 0; i < n; i++)
    {
        string s;
        getline(cin, s);
        strings[i % 2].push_back(s);
    }

    int m;
    cin>>m;
    cin.ignore();

    vector <string> lines(m);

    for (int i = 0; i < m; i++)
    {
        getline(cin, lines[i]);
    }

    pair <int, int> sol[2] = {{INF, INF}, {INF, INF}};

    for (int t = 0; t < 2; t++)
    {
        ahoCorasick ac;

        for (int i = 0; i < strings[t].size(); i++)
        {
            ac.addWord(strings[t][i]);
        }
        ac.build();

        for (int i = 0; i < m; i++)
        {
            int res = ac.match(lines[i]);
            if (res != INF)
            {
                sol[t] = {i + 1, res + 1};
                break;
            }
        }
    }

    auto best = min(sol[0], sol[1]);

    if (best.first != INF)
    {
        cout<<best.first<<" "<<best.second<<'\n';
    }
    else
    {
        cout<<"Passed"<<'\n';
    }

    return 0;
}

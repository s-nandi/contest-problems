//aho corasick (map, pattern partition)
//http://acm.timus.ru/problem.aspx?space=1&num=1269

#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

const int INF = 1231231234;
const int MAXN = 100001;

struct node
{
    map <int, int> to;
    int prefixLink = -1, matchLink = -1, len = 0;
    bool isEnd = false;
};

struct ahoCorasick
{
    int numNodes;
    vector <node> elements;

    ahoCorasick()
    {
        numNodes = 1;
        elements.resize(MAXN);
    }

    int mapping(char c){return c + 128;}

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
        elements[curr].isEnd = true;
    }

    int next(int i, int t){return elements[i].to.count(t) ? elements[i].to[t] : -1;}

    void build()
    {
        elements[0].prefixLink = 0;
        buildLinks();
    }

    void buildLinks()
    {
        queue <int> q;
        q.push(0);

        while (!q.empty())
        {
            int curr = q.front();
            q.pop();

            int j = elements[curr].prefixLink;
            elements[curr].matchLink = elements[j].isEnd ? j : elements[j].matchLink;
            for (auto &elem: elements[curr].to)
            {
                int mc = elem.first;

                while (j > 0 and next(j, mc) == -1) j = elements[j].prefixLink;
                if (curr != 0 and next(j, mc) != -1) elements[next(curr, mc)].prefixLink = next(j, mc);
                else elements[next(curr, mc)].prefixLink = 0;

                q.push(next(curr, mc));
            }
        }
    }

    int findFirstMatch(string &s)
    {
        int res = INF;
        for (int i = 0, j = 0; i < s.length(); i++)
        {
            int mc = mapping(s[i]);

            while (j > 0 and next(j, mc) == -1) j = elements[j].prefixLink;
            if (next(j, mc) != -1) j = next(j, mc);
            else j = 0;

            for (int k = j; k != -1; k = elements[k].matchLink) if (elements[k].isEnd)
                res = min(res, i - elements[k].len + 1);
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

    string s[n];
    for (int i = 0; i < n; i++)
    {
        getline(cin, s[i]);
    }

    int m;
    cin>>m;
    cin.ignore();

    vector <string> lines(m);
    for (int i = 0; i < m; i++) getline(cin, lines[i]);

    vector <pair <int, int>> sol(2, {INF, INF});
    for (int t = 0; t < 2; t++)
    {
        ahoCorasick ac;

        if (!t) for (int i = 0; i < n; i += 2) ac.addWord(s[i]);
        else for (int i = 1; i < n; i += 2) ac.addWord(s[i]);

        ac.build();
        for (int i = 0; i < m; i++)
        {
            int res = ac.findFirstMatch(lines[i]);
            if (res != INF)
            {
                sol[t] = {i + 1, res + 1};
                break;
            }
        }
    }
    auto best = min(sol[0], sol[1]);

    if (best.first != INF) cout<<best.first<<" "<<best.second<<'\n';
    else cout<<"Passed"<<'\n';

    return 0;
}

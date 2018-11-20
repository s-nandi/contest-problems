// string parsing (splitting, converting to number), dfs (finding connected components)
// https://open.kattis.com/problems/findpoly
// 2018 Mid-Atlantic Regional

#include <bits/stdc++.h>

using namespace std;

const string DELIMS = " (),;";

struct edge{int to;};
typedef vector<vector<edge>> graph;

vector <string> split(const string &s, const string delims = " ")
{
    bool isNew = true;
    vector <string> res;
    for (int i = 0; i < s.length(); i++)
    {
        bool isDelim = false;
        for (char c: delims)
        {
            if (s[i] == c)
                isDelim = isNew = true;
        }
        if (!isDelim)
        {
            if (isNew)
                res.push_back("");
            res.back() += s[i];
            isNew = false;
        }
    }
    return res;
}

map <pair<int, int>, int> mapping;
int getIndex(const pair <int, int> &p)
{
    if (mapping.count(p))
        return mapping[p];
    else
    {
        int cnt = mapping.size();
        mapping[p] = cnt;
        return cnt;
    }
}

bool dfs(graph &g, int curr, vector <int> &visited)
{
    if (visited[curr])
        return true;
    visited[curr] = true;

    bool isPoly = g[curr].size() == 2;
    for (edge e: g[curr]) if (!visited[e.to])
        isPoly &= dfs(g, e.to, visited);
    return isPoly;
}

template <typename T> T stot(const string &s)
{
    T res;
    istringstream(s) >> res;
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string line;
    vector <pair<int, int>> edge_list;
    while(getline(cin, line))
    {
        vector <int> nums;
        auto parsed = split(line, DELIMS);
        transform(parsed.begin(), parsed.end(), back_inserter(nums), stot<int>);
        for (int i = 0; i < nums.size(); i += 4)
        {
            int a = getIndex({nums[i], nums[i + 1]}), b = getIndex({nums[i + 2], nums[i + 3]});
            edge_list.push_back({a, b}), edge_list.push_back({b, a});
        }
    }

    int n = mapping.size();
    graph g(n);
    for (auto e: edge_list)
        g[e.first].push_back({e.second});

    int numComponents = 0, numPoly = 0;
    vector <int> visited(n);
    for (int i = 0; i < n; i++) if (!visited[i])
        numComponents++, numPoly += dfs(g, i, visited);

    cout << numComponents << " " << numPoly << '\n';
}

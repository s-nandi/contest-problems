//finding number of substrings (heap)
//http://codeforces.com/contest/128/problem/B

#include <iostream>
#include <queue>

using namespace std;

#define ll long long

struct node
{
    string s;
    int index;

    bool operator > (const node &o) const
    {
        int cmp = s.compare(o.s);
        if (cmp != 0) return cmp > 0;
        return index > o.index;
    }
};

string kthSubstring(string &s, int k)
{
    priority_queue <node, vector<node>, greater<node>> pq;
    int len = s.length();

    for (int i = 0; i < len; i++)
    {
        pq.push({string(1, s[i]), i});
    }
    string a; int b;
    while (!pq.empty())
    {
        if (--k == 0) return pq.top().s;

        a = pq.top().s;
        b = pq.top().index;
        pq.pop();

        if (++b < len)
        {
            a += s[b];
            pq.push({a, b});
        }
    }
    return "";
}

int main()
{
    string s;
    int k;
    cin>>s>>k;

    int len = s.length();
    ll possible = ((ll) len * (len + 1)) / 2;

    if (k > possible) cout<<"No such line."<<'\n';
    else cout<<kthSubstring(s, k)<<'\n';

    return 0;
}

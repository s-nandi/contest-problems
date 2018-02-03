//finding number of substrings (heap)
//http://codeforces.com/contest/128/problem/B

#include <iostream>
#include <queue>

using namespace std;

#define ll long long

string s;

struct substring
{
    int f, b;

    bool operator > (const substring &o) const
    {
        int len1 = b - f + 1, len2 = o.b - o.f + 1;
        int len = min(len1, len2);

        for (int i = 0; i < len; i++)
        {
            if (s[f + i] != s[o.f + i])
            {
                return s[f + i] > s[o.f + i];
            }
        }
        return len == len2;
    }
};

string kthSubstring(int k)
{
    priority_queue <substring, vector<substring>, greater<substring>> pq;
    int len = s.length();

    for (int i = 0; i < len; i++)
    {
        pq.push({i, i});
    }

    while (!pq.empty())
    {
        int f = pq.top().f, b = pq.top().b;
        pq.pop();

        if (--k == 0) return s.substr(f, b - f + 1);

        if (++b < len)
        {
            pq.push({f, b});
        }
    }
    return "";
}

int main()
{
    int k;
    cin>>s>>k;

    int len = s.length();
    ll possible = ((ll) len * (len + 1)) / 2;

    if (k > possible) cout<<"No such line."<<'\n';
    else cout<<kthSubstring(k)<<'\n';

    return 0;
}

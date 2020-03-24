// trie, combo (counting a different way)
// https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ffc7/00000000001d3ff3
// 2020 Kickstart A

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)

const int alpha = 26;
const int MAXL = 2000005;

struct node {
    int to[alpha];
    int cnt = 0;
    node(){memset(to, -1, sizeof(to));}
};

struct trie {
    vector<node> elements = vector<node>(1);
    int numNodes{1};
    
    static int mapping(char c){return c - 'A';}
    int& next(int i, int t){return elements[i].to[t];} 
    void add(const string &s)
    {
        int curr = 0;
        trav(c, s) {
            int mc = mapping(c);
            if (next(curr, mc) == -1)
                elements.emplace_back(), next(curr, mc) = numNodes++;
            curr = next(curr, mc);
            elements[curr].cnt++;
        }
    }
    ll dfs(int i, int k) {
        ll res = elements[i].cnt / k;
        rep(mc, 0, alpha)
            if (next(i, mc) != -1) 
                res += dfs(next(i, mc), k);
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int test = 1; test <= T; test++) {
        int n, k;
        cin >> n >> k;
        trie tr;
        rep(i, 0, n) {
            string s;
            cin >> s;
            tr.add(s);
        }
        auto sol = tr.dfs(0, k);
        cout << "Case #" << test << ": " << sol << '\n';
    }
}

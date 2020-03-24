// trie, dfs (upward) on trie, amortized complexity
// https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ffc7/00000000001d3ff3
// 2020 Kickstart A

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
using ld = long double;

#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)a.size()
#define PB push_back

const int alpha = 26;
const int MAXL = 2000005;

struct node
{
    int to[alpha];
    int cnt = 0, len = 0;

    node() //PS: remove constructor if using map
    {
        memset(to, -1, sizeof(to));
    }
};

int mapping(char c){return c - 'A';} /*PS*/
char invmap(int i){return i + 'A';} /*PS*/

struct trie
{
    vector<node> elements;
    vi pars;
    vector<vi> bylen;
    int maxlen = 0;
    int numNodes;

    trie()
    {
        elements.resize(1);
        pars.resize(1, -1);
        bylen.resize(MAXL);
        numNodes = 1;
    }

    int& next(int i, int t){return elements[i].to[t];} 

    void addString(const string &s)
    {
        int curr = 0;
        for (char c: s) {
            int mc = mapping(c);
            if (next(curr, mc) == -1)
                pars.emplace_back(), elements.emplace_back(), next(curr, mc) = numNodes++;
            pars[next(curr, mc)] = curr;
            curr = next(curr, mc);
        }
        elements[curr].cnt++;
        bylen[sz(s)].PB(curr);
        maxlen = max(maxlen, sz(s));
    }

    int get(int k) {
        int res = -1;
        int len = maxlen;
        assert(!bylen[len].empty());
        int curr = bylen[len].back();
        if (elements[curr].cnt >= k) {
            res = len;
            elements[curr].cnt -= k;
        } else {
            int p = pars[curr];
            
            elements[p].cnt += elements[curr].cnt;
            bylen[len - 1].push_back(p);
            
            elements[curr].cnt = 0;
            bylen[len].pop_back();
            
            if (sz(bylen[len]) == 0) {
                maxlen--;
            }
        }
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
            tr.addString(s);
        }

        ll acc = 0;
        int got = 0;
        while (got < n) {
            int res = tr.get(k);
            if (res == -1) continue;
            got += k;
            acc += res;
        }
        
        auto sol = acc;
        cout << "Case #" << test << ": " << sol << '\n';
    }
}

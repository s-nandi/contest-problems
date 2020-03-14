// constructive, label edges s.t. mex(u, v) is minimized, greedy (edges adj to leaves get smallest labels)
// https://codeforces.com/contest/1325/problem/C
// Note: editorial has other solutions

#include <bits/stdc++.h>
using namespace std;
 
using graph = vector<vector<pair<int, int>>>;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n;
    cin >> n;
    graph g(n);
    for(int i = 0; i < n - 1; i++) {
      int a, b;
      cin >> a >> b;
      --a; --b;
      g[a].push_back({b, i});
      g[b].push_back({a, i});
    }
    int pos = 0;
    vector<int> labels(n - 1, -1);
    for (int phase = 1; phase >= 0; phase--) {
        for (int i = 0; i < n; i++) {
            if ((g[i].size() == 1) == phase) {
                for (auto [to, id]: g[i]) {
                    if (labels[id] != -1) continue;
                    labels[id] = pos++;
                }
            }
        }
    }
    for (auto i: labels) {
      cout << i << '\n';
    }
}

// game theory (dfs on game state graph)
// https://toph.co/p/keep-moving

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)a.size()

struct edge{int to;};
using graph = vector<vector<edge>>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    rep(test, 1, T + 1) {
        int n, m, x;
        cin >> n >> m >> x;
        --x;

        graph g(n), t(n);
        rep(i, 0, m) {
            int a, b;
            cin >> a >> b;
            --a; --b;
            g[a].push_back({b});
            t[b].push_back({a});
        }

        using state = tuple<int, int>;
        constexpr int win = 1, lose = -1;        
        auto state_index = [&](int node, int my_turn){return 2 * node + my_turn;};
        auto nn = 2 * n;

        queue<state> q;
        vi status(nn), outdegree(nn);
        rep(i, 0, n) {
            if (g[i].empty()) {
                status[state_index(i, 1)] = lose;
                status[state_index(i, 0)] = lose;
                q.push({i, 1});
                q.push({i, 0});
            }
            outdegree[state_index(i, 0)] = sz(g[i]);
            outdegree[state_index(i, 1)] = sz(g[i]);
        }
        while (!q.empty()) {
            auto [curr, turn] = q.front();
            q.pop();
            auto index = state_index(curr, turn);
            
            for (auto [to]: t[curr]) {
                auto new_state = state{to, 1 - turn};
                auto new_index = state_index(to, 1 - turn);
                if (status[new_index] == win or status[new_index] == lose) continue;
                if (status[index] == lose) {
                    status[new_index] = win;
                    q.push(new_state);
                } else if (status[index] == win){
                    if (--outdegree[new_index] == 0) {
                        status[new_index] = lose;
                        q.push(new_state);
                    }
                }
            }
        }
        auto will_win = status[state_index(x, 1)] == win; 
        cout << "Case " << test << ": " << (will_win ? "Yes" : "No") << '\n';
    }
}

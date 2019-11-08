// exchange argument, finding the max # of schedulible tasks (sort by deadline, remove most time-consuming task till feas.)
// https://open.kattis.com/problems/atlantis
// 2017 North Central NA Regional

#include <bits/stdc++.h>
using namespace std;

struct store {
    int time, height;

    bool operator < (const auto& o) const {
        return tie(time, height) > tie(o.time, o.height);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<store> stores(n);
    for (int i = 0; i < n; i++) {
        cin >> stores[i].time >> stores[i].height;
    }

    sort(begin(stores), end(stores),
         [](const auto& a, const auto& b) {
             return tie(a.height, a.time) < tie(b.height, b.time);
         });

    long long total_time = 0;
    multiset<store> taken;
    for (int i = 0; i < n; i++) {
        taken.insert(stores[i]);
        total_time += stores[i].time;

        while(!taken.empty() and total_time > stores[i].height) {
            auto worst = *taken.begin();
            taken.erase(taken.begin());
            total_time -= worst.time;
        }
    }
    auto sol = taken.size();
    cout << sol << '\n';   
}

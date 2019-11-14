// greedy (only take front end or backend, keep going while beneficial)
// https://open.kattis.com/problems/stopcounting
// 2019 North American Qualifier

#include <bits/stdc++.h>
using namespace std;

auto solve(const auto& elems) {
    vector<double> psums(elems.size() + 1);
    psums[0] = 0.0;
    for (int i = 1; i < psums.size(); i++) {
        psums[i] = psums[i - 1] + elems[i - 1];
    }
    auto averages = psums;
    for (int i = 1; i < psums.size(); i++) {
        averages[i] = psums[i] / i;
    }
    return *max_element(begin(averages), end(averages));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> elems(n);
    for (auto& elem: elems) {
        cin >> elem;
    }
    auto sol1 = solve(elems);
    reverse(begin(elems), end(elems));
    auto sol2 = solve(elems);
    cout << setprecision(11) << fixed << max({0.0, sol1, sol2}) << '\n';
}

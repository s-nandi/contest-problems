// combinatorics (# of distinct permutations with repeated elements), greedy (fixing one position at a time)
// https://open.kattis.com/problems/lexicography
// 2014 Mid-Central USA Regional

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using frequency_table = map<char, int>;

constexpr auto INF = 12312312312312312LL;
constexpr auto MAX_LENGTH = 17;

array<ll, MAX_LENGTH> factorial;
constexpr auto precompute() {
    factorial[0] = 1;
    for (int i = 1; i < factorial.size(); i++) {
        factorial[i] = factorial[i - 1] * i;
    }
}

auto decrement_count(const frequency_table& table, char c) {
    auto result = table;
    if (--result[c] == 0) {
        result.erase(c);
    }
    return result;
}

auto ways_to_fix_char(const frequency_table& table, char fixed_char) {
    auto total_count = 0LL;
    auto denom = 1LL;
    for (auto [element, count] : table) {
        total_count += count;
        denom *= factorial[count];
    }
    ll num = factorial[total_count];
    return num / denom;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    precompute();
    while (true) {
        string s;
        ll n;
        cin >> s >> n;
        if (s == "#" && n == 0) break;

        string sol(s.length(), '\0');
        frequency_table table;
        for (char c : s) {
            table[c]++;
        }

        for (int i = 0; i < s.length(); i++) {
            auto num_anagrams = 0LL;
            for (const auto& [ch, cnt] : table) {
                auto num_smaller_anagrams = num_anagrams;

                auto table_if_placing_ch = decrement_count(table, ch);
                num_anagrams += ways_to_fix_char(table_if_placing_ch, ch);
                if (num_anagrams >= n) {
                    n -= num_smaller_anagrams;
                    sol[i] = ch;
                    table = decrement_count(table, ch);
                    break;
                }
            }
        }
        cout << sol << '\n';
    }
}

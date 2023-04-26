// maintaining non-overlapping intervals, O(log n) per operation (not necessary) by tracking set of holes
// tracking smallest number in an infinite set with popSmallest, addBack operations

#include <bits/stdc++.h>
using namespace std;

bool between(pair<int, int> interval, int num) { return interval.first <= num && num <= interval.second; }

bool invalid(pair<int, int> interval) { return !(interval.first <= interval.second); }

auto split(pair<int, int> interval, int partition) {
    assert(between(interval, partition));
    vector<pair<int, int>> partitions = {
        {interval.first, partition - 1},
        {partition + 1, interval.second},
    };
    partitions.erase(remove_if(begin(partitions), end(partitions), invalid), end(partitions));
    return partitions;
}

class SmallestInfiniteSet {
   public:
    SmallestInfiniteSet() {
        missing.insert({-lim, -lim});
        missing.insert({lim, lim});
    }

    int popSmallest() {
        auto [lo_first, hi_first] = *next(begin(missing));
        int hole = lo_first > 1 ? 1 : (hi_first + 1);

        auto lo_new = hole;
        auto hi_new = hole;

        auto next_it = missing.upper_bound({hole, lim});
        auto prev_it = prev(next_it);

        if (hi_new + 1 == (next_it->first)) {
            hi_new = next_it->second;
            missing.erase(next_it);
        }
        if ((prev_it->second) + 1 == lo_new) {
            lo_new = prev_it->first;
            missing.erase(prev_it);
        }
        missing.insert({lo_new, hi_new});
        return hole;
    }

    void addBack(int num) {
        if (missing.empty()) return;

        auto containing_interval = *prev(missing.upper_bound({num, lim}));
        if (!between(containing_interval, num)) return;

        auto new_intervals = split(containing_interval, num);
        missing.erase(containing_interval);
        for (auto interval : new_intervals) {
            missing.insert(interval);
        }
    }

   private:
    set<pair<int, int>> missing;
    static const int lim;
};

const int SmallestInfiniteSet::lim = 1'000'000'000;

int main() {
    SmallestInfiniteSet s;
    s.addBack(2);
    assert(s.popSmallest() == 1);
    assert(s.popSmallest() == 2);
    assert(s.popSmallest() == 3);
    s.addBack(1);
    assert(s.popSmallest() == 1);
    assert(s.popSmallest() == 4);
    assert(s.popSmallest() == 5);
    cout << "Done" << endl;
}

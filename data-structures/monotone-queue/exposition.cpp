// monotone queue, two pointer, finding longest subarray s.t. max and min in subarray differ by at most k
// https://codeforces.com/contest/6/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;

template <typename T, class Operation>
struct monotoneQueue
{
    int sz = 0;
    deque <T> elements;
    Operation op;

    monotoneQueue(Operation o) : op(o) {}

    void insert(T elem)
    {
        while (!elements.empty() and op(elem, elements.back()))
            elements.pop_back();
        elements.push_back(elem), sz++;
    }

    void erase(T elem)
    {
        if (elements.front() == elem)
            elements.pop_front();
        sz--;
    }

    T query(){return elements.front();}
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin >> n >> k;
    vector <int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    auto cmp_le = [](int a, int b){return a < b;};
    monotoneQueue <int, decltype(cmp_le)> min_queue(cmp_le);
    auto cmp_ge = [](int a, int b){return a > b;};
    monotoneQueue <int, decltype(cmp_ge)> max_queue(cmp_ge);

    vector <ii> valid;
    for (int l = 0, r = 0; r < n; r++)
    {
        min_queue.insert(a[r]), max_queue.insert(a[r]);
        while (max_queue.query() - min_queue.query() > k)
        {
            max_queue.erase(a[l]), min_queue.erase(a[l]);
            l++;
        }
        valid.push_back({l, r});
    }

    int longest = 0, numLongest = 0;
    for (auto segment: valid)
    {
        auto len = segment.second - segment.first + 1;
        if (len > longest)
            longest = len, numLongest = 1;
        else if (len == longest)
            numLongest++;
    }

    cout << longest << " " << numLongest << '\n';
    for (auto segment: valid) if (segment.second - segment.first + 1 == longest)
        cout << segment.first + 1 << " " << segment.second + 1 << '\n';
}

//sqrt decomposition, mo's algorithm
//http://codeforces.com/problemset/problem/86/D

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define ll long long

const int bucket_size = 447;

struct query
{
    int left;
    int right;
    int index;

    bool operator < (query o) const
    {
        if (left / bucket_size != o.left / bucket_size)
        {
            return left < o.left;
        }
        else
        {
            if ((left / bucket_size) % 2 == 0)
            {
                return right < o.right;
            }
            else
            {
                return o.right < right;
            }
        }
    }
};

ll add_element(ll element, vector <int> &counts, ll curr_sum)
{
    int elem_count = counts[element];
    counts[element]++;

    return curr_sum + element * ((elem_count + 1) * (elem_count + 1) - elem_count * elem_count);
}

ll remove_element(ll element, vector <int> &counts, ll curr_sum)
{
    int elem_count = counts[element];
    counts[element]--;

    return curr_sum - element* (elem_count*elem_count - (elem_count - 1) * (elem_count - 1));
}

int main()
{
    int n, q;
    cin>>n>>q;

    ll nums[n];

    ll maxn = -1;
    for (int i = 0; i < n; i++)
    {
        cin>>nums[i];
        maxn = max(maxn, nums[i]);

    }

    int l, r;
    vector <query> queries;
    vector <int> element_counts(maxn + 1, 0);

    for (int i = 0; i < q; i++)
    {
        cin>>l>>r;
        --l;
        --r;
        queries.push_back({l, r, i});
    }

    sort(queries.begin(), queries.end());

    int left_pointer = 0;
    int right_pointer = 0;
    ll curr_val = add_element(nums[0], element_counts, 0);

    ll sols[q];

    for (int i = 0; i < queries.size(); i++)
    {
        while (left_pointer < queries[i].left)
        {
            curr_val = remove_element(nums[left_pointer], element_counts, curr_val);
            left_pointer++;
        }
        while (left_pointer > queries[i].left)
        {
            left_pointer--;
            curr_val = add_element(nums[left_pointer], element_counts, curr_val);
        }
        while (right_pointer < queries[i].right)
        {
            right_pointer++;
            curr_val = add_element(nums[right_pointer], element_counts, curr_val);
        }
        while (right_pointer > queries[i].right)
        {
            curr_val = remove_element(nums[right_pointer], element_counts, curr_val);
            right_pointer--;
        }
        sols[queries[i].index] = curr_val;
    }

    for (int i = 0; i < q; i++)
    {
        cout<<sols[i]<<"\n";
    }

    return 0;
}

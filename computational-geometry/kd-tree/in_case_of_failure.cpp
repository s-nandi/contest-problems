// kd-tree (nearest neighbor excluding 0-distance points -> 2 nearest neighbor queries)
// https://www.spoj.com/problems/FAILURE/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 1LL << 63;

typedef ll ptT;
struct pt
{
	ptT x, y;

    pt operator - (const pt &o) const {return {x - o.x, y - o.y};}
    ptT operator * (const pt &o) const {return x * o.x + y * o.y;}

    ptT norm2() const {return *this * *this;}
    ptT dist2(const pt &o) const {return (*this - o).norm2();}

    ptT get(int dim) const {return dim == 0 ? x : y;}
};

struct cmpByDim
{
    int dim;
    cmpByDim(int d) : dim(d) {}
    bool operator() (const pt &a, const pt &b)
    {
        return a.get(dim) < b.get(dim);
    }
};

struct node
{
    pt p;
    int l = -1, r = -1, axis;
};

struct kdist
{
    ptT dist; pt p;
    bool operator < (const kdist &o) const {return dist < o.dist;}
};

struct kdTree
{
	int sz, dim;
	vector <pt> v;
	vector <node> elements;
	priority_queue <kdist> pq;

	kdTree(){}
	kdTree(const vector <pt> &ve, int d)
	{
	    v = ve, sz = 0, dim = d;
        shuffle(v.begin(), v.end(), mt19937(time(0)));
        build(0, v.size());
	}

	int build(int l, int r, int axis = 0)
	{
	    if (l == r)
            return -1;

		int m = (l + r) / 2;
		nth_element(v.begin() + l, v.begin() + m, v.begin() + r, cmpByDim(axis));

		int ind = sz++;
		elements.push_back({v[m]});
        int t1 = build(l, m, (axis + 1) % dim);
        int t2 = build(m + 1, r, (axis + 1) % dim);
		elements[ind].l = t1;
		elements[ind].r = t2;
        elements[ind].axis = axis;
		return ind;
	}

    vector <kdist> query(const pt &q, int k = 1)
    {
        queryn(q, k, 0);
        vector <kdist> result(k);
        for (int i = k - 1; i >= 0; i--, pq.pop())
            result[i] = pq.top();
        return result;
    }

	void queryn(const pt &q, int k, int ind)
	{
	    if (ind == -1)
            return;

		pt p = elements[ind].p;
        auto possible = q.dist2(p);
        if (pq.size() < k or possible < pq.top().dist)
        {
            pq.push({possible, p});
            if (pq.size() > k)
                pq.pop();
        }

        int axis = elements[ind].axis;
        if(p.get(axis) <= q.get(axis))
		{
            queryn(q, k, elements[ind].r);
			if(pq.size() < k or (elements[ind].l != -1 and q.get(axis) - sqrt(pq.top().dist) <= p.get(axis)))
                queryn(q, k, elements[ind].l);
		}
		else
		{
			queryn(q, k, elements[ind].l);
			if(pq.size() < k or (elements[ind].r != -1 and q.get(axis) + sqrt(pq.top().dist) >= p.get(axis)))
                queryn(q, k, elements[ind].r);
		}
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;

        vector <pt> machines(n);
        for (int i = 0; i < n; i++)
        {
            cin >> machines[i].x >> machines[i].y;
        }
        kdTree kd(machines, 2);
        for (int i = 0; i < n; i++)
            cout << kd.query(machines[i], 2).back().dist << '\n';
    }
}

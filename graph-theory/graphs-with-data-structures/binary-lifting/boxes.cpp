// lowest common ancestor (binary lifting)
// https://open.kattis.com/problems/boxes
// Hong Kong Preliminary 2016

#include <bits/stdc++.h>

using namespace std;

struct edge{int to;};
typedef vector<vector<edge>> graph;

struct binaryLift
{
	int sz, h = 0;
	graph g;
	vector <vector<int>> table;
	vector <int> depths, sizes;
  
	binaryLift(graph &gr) : sz(gr.size()), g(gr), depths(sz), sizes(sz)
	{
		calcHeight(), table.resize(sz, vector<int>(h, -1));
		build(0);
	}

	void calcHeight() {while (1 << h < sz) h++;}

	void build(int curr, int depth = 0)
	{
		depths[curr] = depth;
		sizes[curr] = 1;
		for (int i = 1; i < h; i++)
			if (table[curr][i - 1] != -1)
			{
				table[curr][i] = table[table[curr][i - 1]][i - 1];
			}
		for (edge e: g[curr])
			if (e.to != table[curr][0])
			{
				table[e.to][0] = curr;
				build(e.to, depth + 1);
				sizes[curr] += sizes[e.to];
			}
	}

	int lca(int l, int r)
	{
		if (depths[l] > depths[r]) swap(l, r);
		for (int i = h - 1; i >= 0; i--)
		{
			if ((1 << i) & (depths[r] - depths[l]))
				r = table[r][i];
		}
		if (l == r) return l;
		for (int i = h - 1; i >= 0; i--)
			if (table[l][i] != table[r][i])
			{
				l = table[l][i], r = table[r][i];
			}
		return table[l][0];
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	int n;
	cin >> n;

	graph g(n + 1);
	int root;
	for (int i = 1; i <= n; i++)
	{
		int par;
		cin >> par;
		g[par].push_back({i});
	}
	binaryLift bl(g);
    
	int q;
	cin >> q;
	while(q--)
	{
		int cnt;
		cin >> cnt;
		vector <int> boxes(cnt), useful;
		for (int &box: boxes)
			cin >> box;
		
		long long res = 0;
		
		for (int i: boxes)
		{
			bool isRedundant = false;
			for (int j: boxes)
			{
				if (i != j)
				{
					int anc = bl.lca(i, j);
					if (anc == j)
					{
						isRedundant = true;
						break;
					}
				}
			}
			if (!isRedundant)
				res += bl.sizes[i];
		}
		cout << res << '\n';
	}   
}

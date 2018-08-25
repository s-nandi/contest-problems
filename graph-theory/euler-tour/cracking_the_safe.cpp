// de brujin graph (hamiltonian path on n dimension is same as euler path on (n - 1) dimension, euler path on directed graph
// https://leetcode.com/problems/cracking-the-safe/description/

class Solution {
public:
    vector <string> all;

    struct edge{int to, id;};
    typedef vector<vector<edge>> graph;

    struct eulerTour
    {
        int n, m = 0, root = -1;
        graph g;
        bool isFeasible;
        vector <bool> used;
        deque <int> tour;

        eulerTour(graph &gr)
        {
            g = gr, n = g.size();
            if(isFeasible = feasible())
            {
                getEdge(), used.resize(m);
                dfs(root), isFeasible = tour.size() == m + 1;
            }
        }

        void getEdge()
        {
            for (int i = 0; i < n; i++)
                m += g[i].size();
        }

        bool feasible()
        {
            vector <int> in(n), out(n);
            for (int i = 0; i < n; i++) for (edge e: g[i])
                in[e.to]++, out[i]++;
            int neg = 0, pos = 0;
            for (int i = 0; i < n; i++)
            {
                if (!in[i] and !out[i]) continue;

                int d = in[i] - out[i];
                if (abs(d) > 1) return false;
                if (d < 0)
                {
                    if (++neg > 1)
                        return false;
                    root = i;
                }
                if (d > 0)
                {
                    if (++pos > 1)
                        return false;
                }
                if(root == -1) root = i;
            }
            return neg == pos;
        }

        void dfs(int curr)
        {
            for (edge e: g[curr]) if (!used[e.id])
            {
                used[e.id] = true;
                dfs(e.to);
            }
            tour.push_front(curr);
        }
    };

    void construct(string &s, int n, int k)
    {
        if (s.length() == n)
            all.push_back(s);
        else
        {
            for (int i = 0; i < k; i++)
            {
                s.push_back('0' + i);
                construct(s, n, k);
                s.pop_back();
            }
        }
    }

    int findPos(string &s)
    {
        return lower_bound(all.begin(), all.end(), s) - all.begin();
    }

    string crackSafe(int n, int k) {
        string start = "", sol = "";
        if (n == 1)
        {
            for (int i = 0; i < k; i++)
                sol += char('0' + i);
            return sol;
        }
        else
        {
            construct(start, --n, k); // euler tour of (n - 1) dimension de brujin graph is hamiltonian tour of n dimension de brujin graph

            graph g(all.size());
            int id = 0;
            for (int i = 0; i < all.size(); i++)
            {
                string curr = all[i].substr(1, all[i].length() - 1);
                for (int j = 0; j < k; j++)
                {
                    string nxt = curr + char('0' + j);
                    g[i].push_back({findPos(nxt), id++});
                }
            }
            eulerTour eu(g);
            for (int i = 0; i < eu.tour.size(); i++)
            {
                if (i == 0)
                    sol += all[eu.tour[0]];
                else
                    sol += all[eu.tour[i]][n - 1];
            }
            return sol;
        }
    }
};

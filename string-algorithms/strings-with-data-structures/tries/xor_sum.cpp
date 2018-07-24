//binary trie (finding max matching int), xor prefix sums to find max subarray
//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2683
//2009 Amritapuri Regional

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int INF = 1231231234;

const int alpha = 2;
const int MAXL = 31;
const int MAXN = 100005;

struct node
{
    int to[alpha];

    node()
    {
        memset(to, -1, sizeof(to));
    }
};

struct trie
{
    vector <node> elements;
    int numNodes;

    trie()
    {
        elements.resize(MAXN * MAXL + 5);
        numNodes = 1;
    }

    int& next(int i, int t){return elements[i].to[t];}

    void addInt(int n)
    {
        int curr = 0;
        for (int i = MAXL - 1; i >= 0; i--)
        {
            bool mc = n & (1 << i);
            if (next(curr, mc) == -1) next(curr, mc) = numNodes++;
            curr = next(curr, mc);
        }
    }

    int findMaxXorMatch(int n)
    {
        int sol = 0;
        int curr = 0;
        for (int i = MAXL - 1; i >= 0; i--)
        {
            bool mc = n & (1 << i), branch;
            if (next(curr, 1 - mc) != -1) branch = 1 - mc;
            else branch = mc;
            curr = next(curr, branch);
            sol += branch * (1 << i);
        }
        return sol;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin>>T;
    for (int test = 1; test <= T; test++)
    {
        int n;
        cin>>n;

        vector <int> a(n);
        for (int i = 0; i < n; i++)
        {
            cin>>a[i];
        }
        int acc = 0;
        vector <int> ps(n + 1);
        for (int i = 0; i < n; i++)
        {
            ps[i + 1] = a[i] ^ ps[i];
        }

        trie tr;
        int mx = -INF;
        for (int i = 0; i <= n; i++)
        {
            tr.addInt(ps[i]);
            int mx_ending_here = ps[i] ^ tr.findMaxXorMatch(ps[i]);
            mx = max(mx, mx_ending_here);
        }
        cout<<mx<<'\n';
    }

    return 0;
}

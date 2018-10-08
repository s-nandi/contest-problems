// sieve, finding element relatively prime to all other elements in subarray (store locations of primes), amortized runtime
// https://open.kattis.com/problems/factorfree
// 2017 Northwest European Regional

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10000000;

vector <bool> prm;
vector <int> primes;
void sieve(int n)
{
    int sq = sqrt(n) + 100;
    prm.resize(sq, true);
    for (int i = 2; i < sq; i++)
    {
        if (!prm[i]) continue;
        primes.push_back(i);
        for (int j = i * i; j < sq; j += i)
            prm[j] = false;
    }
}

vector <int> factorize(int n)
{
    vector <int> factors;
    for (int p: primes)
    {
        if (n % p == 0) factors.push_back(p);
        while (n % p == 0)
            n /= p;
    }
    if (n != 1) factors.push_back(n);
    return factors;
}

vector <vector<int>> factored;
map <int, vector<int>> positions;

bool isRelativePrime(int i, int l, int r)
{
    for (auto fac: factored[i])
    {
        auto &pos = positions[fac];
        int closestRight = *upper_bound(pos.begin(), pos.end(), i);
        int closestLeft = *(--lower_bound(pos.begin(), pos.end(), i));
        if (closestLeft >= l or closestRight <= r)
            return false;
    }
    return true;
}

vector <int> sol;
bool solve(int l, int r, int par = -1)
{
    if (l >= r)
    {
        if (l == r)
            sol[l] = par;
        return true;
    }

    int root = -1;
    for (int ll = l, rr = r; ll <= rr; ll++, rr--)
    {
        if (isRelativePrime(ll, l, r))
        {
            root = ll;
            break;
        }
        if (isRelativePrime(rr, l, r))
        {
            root = rr;
            break;
        }
    }
    if (root == -1)
        return false;
    else
    {
        sol[root] = par;
        return solve(l, root - 1, root) and solve(root + 1, r, root);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    sieve(MAXN);

    int n;
    cin >> n;
    vector <int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    factored.resize(n);
    for (int i = 0; i < n; i++)
    {
        factored[i] = factorize(a[i]);
        for (auto fac: factored[i])
            positions[fac].push_back(i);
    }
    for (auto &elem: positions)
    {
        auto &pos = elem.second;
        pos.push_back(-1);
        pos.push_back(n + 1);
        sort(pos.begin(), pos.end());
    }

    sol.resize(n, -1);
    if (solve(0, n - 1))
    {
        for (int i: sol)
            cout << i + 1 << " ";
        cout << '\n';
    }
    else
        cout << "impossible" << '\n';
}

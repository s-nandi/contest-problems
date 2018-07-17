//totient function sieve, gcd, abusing growth of function vs bounds
//http://codeforces.com/contest/1009/problem/D

#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

typedef long long ll;

const int MAXN = 100005;

vector <int> primes;
vector <bool> prm;
vector <int> phi;

void totientSieve()
{
	prm.resize(MAXN + 1, true);
	phi.resize(MAXN + 1);
	for (int i = 2; i <= MAXN; i++)
    {
		if (prm[i])
        {
			primes.push_back(i);
			phi[i] = i - 1;
		}
		for (int prime: primes)
        {
            if ((ll) i * (ll) prime > MAXN) break;

			prm[i * prime] = false;
			if (i % prime == 0) {
				phi[i * prime] = phi[i] * prime;
				break;
			}
			else
            {
				phi[i * prime] = phi[i] * phi[prime];
			}
		}
	}
}

int gcd(int a, int b)
{
    while (b != 0)
    {
        tie(a, b) = make_tuple(b, a % b);
    }
    return a;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    totientSieve();

    int n, m;
    cin>>n>>m;

    int needed = m - (n - 1);
    vector <pair<int, int>> edges;
    bool feasible;

    if (m < n - 1 or (ll) m > (ll) n * (ll) (n - 1) / 2LL)
    {
        feasible = false;
    }
    else
    {
        for (int i = 2; i <= n; i++)
        {
            edges.push_back({1, i});
            m--;
        }
        for (int i = 2; i <= n and m > 0; i++)
        {
            m -= phi[i] - 1;
        }
        feasible = m <= 0;
    }

    if (feasible)
    {
        cout<<"Possible"<<'\n';

        for (int i = 2; i <= n; i++)
        {
            for (int j = 2; j < i; j++)
            {
                if (gcd(i, j) == 1)
                {
                    edges.push_back({i, j});
                    needed--;
                }
                if (needed == 0) break;
            }
            if (needed == 0) break;
        }

        for (pair <int, int> edge: edges)
        {
            cout<<edge.first<<" "<<edge.second<<'\n';
        }
    }
    else
    {
        cout<<"Impossible"<<'\n';
    }

    return 0;
}

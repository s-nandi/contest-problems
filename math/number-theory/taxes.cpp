//goldbach's conjecture, primality check (sieve)
//http://codeforces.com/contest/736/problem/B

#include <iostream>
#include <vector>

using namespace std;

vector <bool> isComposite;
vector <int> primes;

void sieve(int n)
{
    int sqrtn = 0;
    while (sqrtn * sqrtn <= n) sqrtn++;

    isComposite.resize(sqrtn);

    for (int i = 2; i < sqrtn; i++)
    {
        if (isComposite[i]) continue;
        primes.push_back(i);
        for (int j = i; j < sqrtn; j += i)
        {
            isComposite[j] = true;
        }
    }
}

bool prime(int i)
{
    if (i < isComposite.size()) return isComposite[i];
    else
    {
        for (int p: primes)
        {
            if (i % p == 0) return false;
        }
        return true;
    }
}

int splitPrimes(int n)
{
    if (prime(n)) return 1;

    if (!(n & 1)) return 2;

    if (prime(n - 2)) return 2;

    return 3;
}

int main()
{
    int n;
    cin>>n;

    sieve(n);
    cout<<splitPrimes(n)<<'\n';

    return 0;
}

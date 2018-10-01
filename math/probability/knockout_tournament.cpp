// probability, greedy (set up bracket to maximize # of wins)
// http://codeforces.com/gym/101623/attachments (problem K)
// 2017 Northwest European Regional

#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    vector <int> ratings(n);
    for (int i = 0; i < n; i++)
    {
        cin >> ratings[i];
    }
    sort(ratings.begin() + 1, ratings.end());

    int sz = 1, numRounds = 0;
    while (sz < n)
    {
        sz *= 2;
        numRounds++;
    }

    auto it = ratings.begin();
    int numZeros = sz - n;
    while (numZeros--)
        it = next(ratings.insert(it + 1, 0));

    vector <int> roundSize(numRounds + 1);
    roundSize[0] = 1;
    for (int i = 1; i <= numRounds; i++)
        roundSize[i] = 2 * roundSize[i - 1];

    vector <vector<double>> probability(sz, vector <double>(numRounds + 1, 0.0));
    for (int i = 0; i < sz; i++)
        probability[i][0] = 1.0;

    for (int i = 1; i <= numRounds; i++)
    {
        for (int j = 0; j < sz; j++)
        {
            int bucket = j / roundSize[i];
            for (int k = roundSize[i] * bucket; k < roundSize[i] * (bucket + 1); k++)
            {
                bool playedBefore = k / roundSize[i - 1] == j / roundSize[i - 1];
                if (playedBefore)
                    continue;

                double probWin = ratings[j] != 0 or ratings[k] != 0 ? (double) ratings[j] / (ratings[j] + ratings[k]) : 0.0;
                probability[j][i] += probability[k][i - 1] * probWin;
            }
            probability[j][i] *= probability[j][i - 1];
        }
    }

    cout << fixed << setprecision(10) << probability[0][numRounds] << '\n';
}

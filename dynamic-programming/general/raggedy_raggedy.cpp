//dynamic programming, string processing
//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3956
//2011 Mid-Atlantic Regional

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

#define INF 123123123

int main()
{
    int L;
    while (true)
    {
        cin>>L;
        if (L == 0)
        {
            break;
        }

        string s;
        vector <string> strings;
        vector <int> widths;

        cin.ignore();

        while (getline(cin, s))
        {
            if (s == "")
            {
                break;
            }
            istringstream iss(s);
            string str;
            while (iss >> str)
            {
                strings.push_back(str);
                widths.push_back(str.length());
            }
        }

        int sz = strings.size();

        int dp[sz][L + 1];
        int prevRemainder[sz][L + 1];
        bool isNewline[sz][L + 1];

        for (int i = 0; i < sz; i++)
        {
            for (int l = 0; l <= L; l++)
            {
                if (i == 0 and l == L - widths[i])
                {
                    dp[i][l] = l * l;
                    isNewline[i][l] = true;
                }
                else
                {
                    dp[i][l] = INF;
                }
            }
        }

        for (int i = 1; i < sz; i++)
        {
            for (int l = 0; l <= L; l++)
            {
                int neededLength = l + widths[i] + 1;

                if (neededLength <= L)
                {
                    int continueLine = dp[i - 1][neededLength] - neededLength * neededLength;

                    if (i < sz - 1)
                    {
                        continueLine += l * l;
                    }

                    if (continueLine < dp[i][l])
                    {
                        dp[i][l] = continueLine;
                        prevRemainder[i][l] = neededLength;
                        isNewline[i][l] = false;
                    }
                }

                if (l == L - widths[i])
                {
                    int bestPrev = INF;
                    int prevLength = -1;

                    for (int l2 = 0; l2 <= L; l2++)
                    {
                        if (dp[i - 1][l2] < bestPrev)
                        {
                            bestPrev = dp[i - 1][l2];
                            prevLength = l2;
                        }
                    }

                    if (i < strings.size() - 1)
                    {
                        bestPrev += l * l;
                    }

                    if (bestPrev < dp[i][l])
                    {
                        dp[i][l] = bestPrev;
                        prevRemainder[i][l] = prevLength;
                        isNewline[i][l] = true;
                    }
                }
            }
        }

        int currWord = strings.size() - 1;
        int currRem = -1;

        int bestSol = INF;
        for (int l = 0; l <= L; l++)
        {
            if (dp[strings.size() - 1][l] < bestSol)
            {
                bestSol = dp[strings.size() - 1][l];
                currRem = l;
            }
        }

        vector <string> lines;
        while (currWord >= 0)
        {
            string currLine = "";
            bool createLine = false;

            while (!createLine)
            {
                if (currLine != "")
                {
                    currLine = " " + currLine;
                }

                currLine = strings[currWord] + currLine;

                createLine = isNewline[currWord][currRem];
                currRem = prevRemainder[currWord][currRem];
                currWord--;
            }

            lines.push_back(currLine);
        }

        for (int i = lines.size() - 1; i >= 0; i--)
        {
            cout<<lines[i]<<'\n';
        }
        cout<<"==="<<'\n';

    }

}

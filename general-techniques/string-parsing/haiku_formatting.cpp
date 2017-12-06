//string parsing
//https://open.kattis.com/problems/haikuformatting

#include <iostream>
#include <vector>
#include <cctype>
#include <set>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;

struct node
{
    bool isVowel;
    string val;
};

int syllable(string s)
{
    string temp = s;

    set <char> vowels = {'a', 'e', 'i', 'o', 'u', 'y'};

    s = "";
    for (char c: temp)
    {
        s += tolower(c);
    }

    temp = s;
    s = "";
    for (char c: temp)
    {
        if (c >= 'a' and c <= 'z')
        {
            s += c;
        }
    }
    if (s.length() == 0)
    {
        return 1;
    }

    vector <node> type;
    int curr = 0;
    while (curr < s.length())
    {
        if (s[curr] == 'q' and curr + 1 < s.length() and s[curr+1] == 'u')
        {
            type.push_back({false, "qu"});
            curr += 2;
        }
        else if(s[curr] == 'y' and curr + 1 < s.length() and vowels.count(s[curr+1]) == 1 and s[curr + 1] != 'y')
        {
            type.push_back({false, "y"});
            curr++;
        }
        else
        {
            string add; add += s[curr];
            if (vowels.count(s[curr]) == 1)
            {
                type.push_back({true, add});
            }
            else
            {
                type.push_back({false, add});
            }
            curr++;
        }
    }

    int last = type.size() - 1;

    if (type[last].val == "e" and !(last - 1 >= 0 and type[last-1].val == "l" and last - 2 >= 0 and !type[last - 2].isVowel))
    {
        type.pop_back();
    }
    if (type[last].val == "s" and last - 1 >= 0 and type[last-1].val == "e" and !(last - 2 >= 0 and !type[last-2].isVowel and last - 3 >= 0 and !type[last-3].isVowel))
    {
        type.pop_back();
        type.pop_back();
    }

    int acc = 0;
    bool prevVowel = false;
    for (int i = 0; i < type.size(); i++)
    {
        if (type[i].isVowel == 1 and !prevVowel)
        {
            acc++;
            prevVowel = true;
        }
        else if(type[i].isVowel == 0 and prevVowel)
        {
            prevVowel = false;
        }
    }

    return max(1, acc);
}

int main()
{
    string s;
    getline(cin, s);
    istringstream iss(s);

    string w;
    vector <string> words;
    while (iss >> w)
    {
        words.push_back(w);
    }

    vector <int> lineLimit = {5, 7, 5};

    vector <string> lines[3];

    int currWord = 0;
    bool feasible = true;
    for (int i = 0; i < 3; i++)
    {
        int currSyllable = 0;
        while (currSyllable < lineLimit[i] and currWord < words.size())
        {
            lines[i].push_back(words[currWord]);
            currSyllable += syllable(words[currWord]);
            currWord++;
        }
        if (currSyllable != lineLimit[i])
        {
            feasible = false;
            break;
        }
    }

    if (currWord != words.size())
    {
        feasible = false;
    }

    if (feasible)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < lines[i].size(); j++)
            {
                cout<<lines[i][j];
                if (j + 1 < lines[i].size())
                    cout<<" ";
            }
            cout<<'\n';
        }
    }
    else
    {
        cout<<s<<'\n';
    }

    return 0;
}

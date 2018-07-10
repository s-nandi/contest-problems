//bitmask dp (enumerating submasks)
//https://leetcode.com/problems/stickers-to-spell-word/description/

class Solution {
public:    
    vector <int> findMasks(string &sticker, string &target)
    {
        int n = target.length();
        vector <int> masks;
        vector <int> contained(26);
        for (char c: sticker)
        {
            contained[c - 'a']++;
        }
        
        for (int mask = 1; mask < (1 << n); mask++)
        {
            vector <int> used_counts(26);
            bool feasible = true;
            for (int i = 0; i < n; i++) if ((1 << i) & mask)
            {
                char c = target[i];
                used_counts[c - 'a']++;
                if (used_counts[c - 'a'] > contained[c - 'a'])
                {
                    feasible = false;
                    break;
                }
            }
            if (feasible)
            {
                masks.push_back(mask);
            }
        }
        return masks;
    }
    
    int minStickers(vector<string>& stickers, string target) {
        int INF = 1031231234;
        
        int n = target.length();
        vector <int> dp(1 << n, INF);
        dp[0] = 0;
        for (string &sticker: stickers)
        {
            auto possible = findMasks(sticker, target);
            for (int mask: possible)
            {
                dp[mask] = 1;
            }
        }
        
        for (int mask = 1; mask < (1 << n); mask++)
        {
            for (int submask = mask; submask; submask = (submask - 1) & mask)
            {
                dp[mask] = min(dp[mask], dp[submask] + dp[mask - submask]);
            }
        }
        
        return dp[(1 << n) - 1] != INF ? dp[(1 << n) - 1] : -1;
    } 
};

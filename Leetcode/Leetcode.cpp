#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <stack>

class FoodRatings {
public:
    FoodRatings(std::vector<std::string>& foods, std::vector<std::string>& cuisines, std::vector<int>& ratings) {
        for (int i=0;i<foods.size();i++)
        {
            rate[foods[i]] = ratings[i];
            cuisinesType[foods[i]] = cuisines[i];
            if (rate[highestRate[cuisines[i]]] < ratings[i])
            {
                highestRate[cuisines[i]] = foods[i];
            }
            else if (rate[highestRate[cuisines[i]]] == ratings[i]&& highestRate[cuisines[i]]>foods[i])
            {
                highestRate[cuisines[i]] = foods[i];
            }

        }
        rate.erase("");
    }

    void changeRating(std::string food, int newRating) {
        if (highestRate[cuisinesType[food]] != food)
        {
            rate[food] = newRating;
            if (rate[highestRate[cuisinesType[food]]] < newRating)
            {
                highestRate[cuisinesType[food]] = food;
            }
            else if (rate[highestRate[cuisinesType[food]]] == newRating)
            {
                highestRate[cuisinesType[food]] = (food< highestRate[cuisinesType[food]]) ? food : highestRate[cuisinesType[food]];
            }
        }
        else
        {
            if(rate[food] <= newRating)
                rate[food] = newRating;
            else
            {
                rate[food] = newRating;
                for (const auto& name : rate)
                {
                    if (cuisinesType[name.first] == cuisinesType[food] && rate[name.first] > rate[highestRate[cuisinesType[food]]])
                    {
                        highestRate[cuisinesType[food]] = name.first;
                    }
                    else if (cuisinesType[name.first] == cuisinesType[food] && rate[name.first] == rate[highestRate[cuisinesType[food]]]&&name.first< highestRate[cuisinesType[food]])
                    {
                        highestRate[cuisinesType[food]] = name.first;
                    }
                }
            }
        }
    }

    std::string highestRated(std::string cuisine) {
        return highestRate[cuisine];
    }
private:
    std::unordered_map<std::string,int> rate; //food - > rating
    std::unordered_map<std::string, std::string> cuisinesType; //food - > cuisines
    std::unordered_map<std::string, std::string> highestRate; //cuisines - > food
};

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
    
};

class Solution {
public:

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* ans = new ListNode;
        int carry = 0;
        int current;
        while (l1 != nullptr || l2 != nullptr || carry != 0)
        {
            current = 0;
            if (l1 != nullptr)
            {
                current += l1->val;
                if (l1->next != nullptr)
                    l1 = new ListNode(l1->next->val, l1->next->next);
                else
                    l1 = nullptr;
            }
            if (l2 != nullptr)
            {
                current += l2->val;
                if (l2->next != nullptr)
                    l2 = new ListNode(l2->next->val, l2->next->next);
                else
                    l2 = nullptr;
            }
            current += carry;
            carry = current / 10;
            current = current % 10;
            ans = new ListNode(current, ans);
        }
        ListNode* ans2 = nullptr;
        while (ans->next != nullptr)
        {
            ans2 = new ListNode(ans->val,ans2);
            ans = new ListNode(ans->next->val,ans->next->next);
        }
        return ans2;
    }

    int lengthOfLongestSubstring(std::string s) {
        std::unordered_map<char, int> map;
        int len = 0;
        int maxLen = 0;
        for (int i=0;i<s.size();i++)
        {
            if (map.count(s[i]))
            {
                len = (i - map[s[i]]<len+1)? i-map[s[i]]:len+1;
            }
            else
            {
                len++;
            }
            if (len > maxLen)
                maxLen = len;
            
            map[s[i]] = i;
        }
        return maxLen;
    }

    //TODO : fix this shit up
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
        


        std::vector<int> med;
        
        if (nums1.size() % 2 == 0)
        {
            med.push_back(nums1[nums1.size()/2 - 1]);
        }
        med.push_back(nums1[nums1.size()/2]);
        if (nums2.size() % 2 == 0)
        {
            med.push_back(nums2[nums2.size()/2 - 1]);
        }
        med.push_back(nums2[nums2.size()/2]);
        sort(med.begin(), med.end());
        if (med.size() % 2 == 0)
            return ((double)med[med.size()/2 - 1] + (double)med[med.size()/2]) / 2;
        return double(med[med.size()/2]);

    }

    //TODO : fix this shit up
    std::string longestPalindrome(std::string s) {
        std::stack<char> a;
        int index=0;
        int len=0;
        int maxLen = 0;
        a.push(s[0]);
        for(int i=1;i<s.size();i++)
        {
            if (a.top() != s[i])
            {
                a.push(s[i]);
                len++;
            }
            else
            {
                len = 0;
                a.pop();
            }
            if (len > maxLen)
            {
                maxLen = len;
                index = i;
            }
        }
        std::string ans = {};
        for(int i = index-maxLen; i < index-1; i++)
        {
            ans += s[i];
        }
        return ans;

    }

    std::string destCity(std::vector<std::vector<std::string>>& paths) {
        std::unordered_map<std::string, std::string> a;
        for (int i = 0; i < paths.size(); i++)
        {
            a[paths[i][0]] = paths[i][1];
        }
        std::string ans;
        ans = paths[0][0];
        while (a.count(ans))
        {
            ans = a[ans];
        }
        return ans;
    }

    bool isAnagram(std::string s, std::string t) {
        if (s.size() != t.size())
            return false;
        std::unordered_map<char, int> map1;
        std::unordered_map<char, int> map2;
        for (int i = 0; i < s.size(); i++)
        {
            map1[s[i]]++;
            map2[t[i]]++;
        }
        return (map1 == map2);

    }

    int reverse(int x) {
        int ans=0;
        while (x != 0)
        {
            if (ans > 214748364||ans< -214748364)
                return 0;
            ans *= 10;
            ans += x % 10;
            x /= 10;
        }
        return ans;

    }

    int myAtoi(std::string s) {
        double ans = 0;
        int sign = 1;
        int place = 0;
        while (s[place] == ' ')
            place++;
        if (s[place] < 46)
        {
            if (s[place] == '-')
                sign = -1;
            place++;
        }
        while (place < s.size() && (s[place] <= '9'&&s[place]>='0'))
        {
            ans *= 10;
            ans += s[place] - '0';
            place++;
            
        }
        ans *= sign;
        if (ans > INT32_MAX)
            ans = INT32_MAX;
        
        if (ans < INT32_MIN)
            ans = INT32_MIN;
        return ans;
    }

    bool isPalindrome(int x) {
        if (x < 0)
            return false;
        if (x % 10 == 0)
            if (x == 0)
                return true;
            else
                return false;
        int a = 0;
        while (a < x)
        {
            a *= 10;
            a += x % 10;
            x /= 10;
        }
        if (a == x||a/10==x)
            return true;
        return false;
    }
    //UNFINISHED

    bool isMatch(std::string s, std::string p) {
        int i=0, j=0;
        char current = ' ';
        while (j < p.size())
        {
            if (p[j] == 0)
                return true;
        }
        return true;
    }

    int maxArea(std::vector<int>& height) {
        int maxArea=0;
        int i = 0, j = height.size() - 1;
        int area;
        while (i < j)
        {
            
            if (height[i] > height[j])
            {
                area = height[j]*(j-i);
                if (area > maxArea)
                    maxArea = area;
                j--;
            }
            else
            {
                area = height[i] * (j - i);
                if (area > maxArea)
                    maxArea = area;
                i++;
            }
        }
        return maxArea;
    }

    std::string intToRoman(int num) {
        char symbols[] = { 'M','D','C','L','X','V','I'};
        std::string pos[] = { "","0","00","000","01","1","10","100","1000","02"};
        std::string output="";
        int i = 0;
        int val = 1000;
        int cur;
        while (num > 0)
        {
            cur = num / val;
            for (char& a : pos[cur])
                output += symbols[i-(a-'0')];
            num = num % val;
            val /= 10;
            i += 2;
        }
        return output;
    }

    int romanToInt(std::string s) {
        std::unordered_map<char, int> m;

        m['I'] = 1;
        m['V'] = 5;
        m['X'] = 10;
        m['L'] = 50;
        m['C'] = 100;
        m['D'] = 500;
        m['M'] = 1000;

        int ans = 0;

        for (int i = 0; i < s.length(); i++) {
            if (m[s[i]] < m[s[i + 1]]) {
                ans -= m[s[i]];
            }
            else {
                ans += m[s[i]];
            }
        }
        return ans;
    }

    std::string longestCommonPrefix(std::vector<std::string>& strs) {
        std::sort(strs.begin(), strs.end());
        std::string ans = "";
        for (int i = 0; i < strs[0].size(); i++)
        {
            if (strs[0][i] == strs[strs.size() - 1][i])
            {
                ans += strs[0][i];
            }
            else
                break;
        }
        return ans;
    }

    void f(int ind, std::string& digits, std::vector<std::string>& v, std::string& s, std::map<char, std::string>& m) {
        if (ind == digits.size()) {
            v.push_back(s);
            return;
        }
        std::string t = m[digits[ind]];
        for (int i = 0; i < t.size(); i++) {
            s += t[i];
            f(ind + 1, digits, v, s, m);
            s.pop_back();
        }
    }
    std::vector<std::string> letterCombinations(std::string digits) {
        std::vector<std::string> v;
        if (digits.size() == 0) return v;
        std::string s;
        std::map<char, std::string> m;
        m['2'] = "abc";
        m['3'] = "def";
        m['4'] = "ghi";
        m['5'] = "jkl";
        m['6'] = "mno";
        m['7'] = "pqrs";
        m['8'] = "tuv";
        m['9'] = "wxyz";
        f(0, digits, v, s, m);
        return v;
    }

    //TODO fix this one
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode*& ans = head;
        for (int i = 0; i < n; i++)
        {
            ans = ans->next;
        }
        ans = nullptr;
        return head;
    }
};

int main()
{
    std::vector<std::string> foods = { "vhbibydfop","ggtdlawxup","lslcltacc","bqgkfcy","xxowyabq","ezswv","ewgvsuyvpo","zgochpey","epiaxxiv","idpdiqlcp","wqgrbvme","wqxbxeovwe","iduzk","ahemklz","ah","rvuqnlydxu","dldqmpheob","lzeqwfb","ykwjc","dtrgnrcqr","cwcgevzzz","zejbynj","ivhdsnjpho","gsyewq","ekqhtiijrj","cthwbt","gnbhjyhcil","kkthw","ktiqokzl","zzroi","cjwapjnzql","hfum","jrwby","amhfyno","bj","fszije","nbkpptir","dgzmoxhhoe","bnisfskgxi","uepypxnsy","afdz","tdctkeg","lfsohpzmk","ewwqult","iynyddno","yyroyjzdg","mcpea","lzafjh","jdvcxidtm","qvkyqmupz","kjop","girgfkaib","qecvnaxpsm","itx","xhjmq","lwwbdxkz","chthxuhex","tghokrfica","vrmjibxv","oipnttbz","yyfvlwvj","erbtnw","yezfiom","ismarfqbuv","vmfxlqbxwa","pcwparohxf","bpdrndbv","owgjjitjfd","fdwmxhli","kffetdxvfx","ruahmg","aphbsbkimb","nbkdfkgl","rxehcqcrwu","kxwlfxbe","qukxd","tewgnjuxnm","jxfqwqe","mdgwiok","tbkmnx","klzznopcn","vjbcvddw","yzhawtmpwp","fhjichpi","tapig","glfbwolsoa","xklqlzm" };
    std::vector<std::string> cuisines = { "kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh","kggxajkarh" };
    std::vector<int> ratingList = { 146,562,428,619,731,483,598,619,950,446,630,556,894,911,537,359,863,995,417,702,689,667,502,691,896,582,111,319,182,953,131,372,563,963,300,42,829,187,676,509,259,688,897,614,392,170,392,1,134,79,995,371,886,430,72,830,871,758,247,333,128,987,659,933,640,198,638,585,825,904,729,214,974,935,581,985,85,987,51,174,301,635,148,492,200,275,101 };
    FoodRatings ratings(foods,cuisines,ratingList);

    std::cout<<ratings.highestRated("kggxajkarh")<<std::endl;
    return 0;
}


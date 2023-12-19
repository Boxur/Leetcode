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

    bool isValid(std::string s) {
        std::stack<char> stack;

        for (char& a : s)
        {

            switch (a)
            {
            case'[':case'{':case'(':
                stack.push(a);
                break;
            case']':
                if (stack.size() == 0|| stack.top() != '[')
                    return false;
                stack.pop();
                break;
            case'}':
                if (stack.size() == 0|| stack.top() != '{')
                    return false;
                stack.pop();
                break;
            case')':
                if (stack.size() == 0|| stack.top() != '(')
                    return false;
                stack.pop();
                break;

            default:
                break;
            }
        }
        return (stack.size() == 0);
    }

    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
    {

        if (l1 == NULL)
        {
            return l2;
        }

        if (l2 == NULL)
        {
            return l1;
        }

        if (l1->val <= l2->val)
        {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        }

        else
        {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
    }

    int maxProductDifference(std::vector<int>& nums) {
        int max1=0, max2=0;
        int min1=0, min2=0;
        for (int& num : nums)
        {
            if (num > max1)
            {
                max2 = max1;
                max1 = num;
            }
            else if (num > max2)
                max2 = num;
            if (num < min1 || min1 == 0)
            {
                min2 = min1;
                min1 = num;
            }
            else if (num < min2 || min2 == 0)
                min2 = num;
        }
        return max1 * max2 - min1 * min2;
    }

    //TODO fix this shit up
    std::vector<std::string> generateParenthesis(int n) {
        std::vector<std::string> output;
        return output;
    }

    std::vector<std::vector<int>> imageSmoother(std::vector<std::vector<int>>& img) {
        std::vector<std::vector<int>> ans = img;
        for (int y = 1; y < img.size()-1; y++)
        {
            for (int x = 1; x < img[0].size()-1; x++)
            {
                ans[x][y] = (img[x - 1][y - 1] + img[x][y - 1] + img[x + 1][y - 1] + img[x - 1][y] + img[x][y] + img[x + 1][y] + img[x - 1][y + 1] + img[x][y + 1] + img[x + 1][y + 1]) / 9;
            }
        }
        return ans;
    }
};

int main()
{
    std::vector<std::vector<int>> in;

    in.resize(5);
    for (int i = 0; i < 25; i++)
    {
        in[i % 5].resize(5);
        in[i % 5][i / 5] = i*i;
    }
    Solution a;

    in=a.imageSmoother(in);

    for (int j = 0; j < 5; j++)
    {
        for (int i = 0; i < 5; i++)
            std::cout << in[i][j] << " ";
        std::cout << std::endl;
    }

    return 0;
}


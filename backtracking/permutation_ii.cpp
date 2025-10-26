/*
LeetCode 47 — Permutations II

🧩 Problem:
Given a collection of numbers `nums` that might contain duplicates, 
return all possible **unique permutations** in any order.

---------------------------------------------
🔹 Approach — Backtracking with Frequency Map
---------------------------------------------

We must generate **all permutations** without duplicates.  
Normal permutation logic (swapping elements) causes repetition when duplicates exist.  
To avoid duplicates, we use a **frequency map** (like a dictionary) that keeps track 
of how many times each number is still available to use.

---------------------------------------------
🧠 Example:
Input: nums = [1, 1, 2]

We start with:
freq = {1: 2, 2: 1}

Recursion tree:
- Choose 1 → freq {1:1, 2:1}
  - Choose 1 → freq {1:0, 2:1}
    - Choose 2 → [1,1,2] ✅
  - Choose 2 → freq {1:1, 2:0}
    - Choose 1 → [1,2,1] ✅
- Choose 2 → freq {1:2, 2:0}
  - Choose 1 → freq {1:1, 2:0}
    - Choose 1 → [2,1,1] ✅

Result: [[1,1,2], [1,2,1], [2,1,1]]

---------------------------------------------
🧮 Steps:
1️⃣ Count how many times each number appears (use `unordered_map<int, int>`).
2️⃣ Use recursion + backtracking:
    - If the current permutation’s size == nums.size(), store it.
    - Else, for every number that still has count > 0:
        ➤ Choose it (add to temp)
        ➤ Decrease its count
        ➤ Recurse
        ➤ Undo (remove and restore count)
3️⃣ Collect all unique permutations in a result vector.

---------------------------------------------
⏱️ Time Complexity: O(N × N!)  → exploring all unique permutations
📦 Space Complexity: O(N)       → recursion + temporary vectors
---------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> ans;

    // Helper function for backtracking
    void solve(unordered_map<int, int>& freq, vector<int>& nums, vector<int>& temp) {
        // Base Case — if we have used all numbers
        if (temp.size() == nums.size()) {
            ans.push_back(temp);
            return;
        }

        // Try placing each available number
        for (auto &it : freq) {
            int num=it.first;
            int count=it.second;

            if (count > 0) {
                // Choose this number
                temp.push_back(num);
                freq[num]--;

                // Recurse to fill the next position
                solve(freq, nums, temp);

                // Backtrack — undo the choice
                temp.pop_back();
                freq[num]++;
            }
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        unordered_map<int, int> freq;
        for (int num : nums) freq[num]++;  // Count frequency of each number

        vector<int> temp;
        solve(freq, nums, temp);
        return ans;
    }
};

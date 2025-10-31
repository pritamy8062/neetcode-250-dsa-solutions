// 🔹 Problem: 698. Partition to K Equal Sum Subsets
// 🔹 Link: https://leetcode.com/problems/partition-to-k-equal-sum-subsets/

// ✅ Approach:
// This problem is the **generalized form of "Matchsticks to Square"**.
// Instead of dividing sticks into 4 equal sides, we divide numbers into K subsets,
// each having an equal sum.
//
// 1️⃣ Calculate total sum of all elements. If it's not divisible by K → return false.
//
// 2️⃣ Our goal: divide array `nums` into K subsets where each subset sum = total_sum / K.
//
// 3️⃣ Use **backtracking**:
//     - Maintain a vector `subsetSums[k]` to store current sum of each subset.
//     - Try to place each element `nums[idx]` into one of the subsets.
//     - If the subset sum exceeds target, skip it.
//     - If after trying all subsets, no valid placement → backtrack.
//
// 4️⃣ Optimization:
//     - Sort `nums` in descending order → helps prune faster.
//     - If after removing an element, the subset sum becomes 0 → break
//       (no point trying the same number in other empty subsets — avoids TLE).
//
// 🔹 Example:
//     nums = [4, 3, 2, 3, 5, 2, 1], k = 4
//     total_sum = 20 → target = 5
//     Possible subsets: [5], [1,4], [2,3], [2,3] ✅
//
// 🔹 Time Complexity: O(k^N)
//     - Each element can go into any of the K subsets.
//     - Optimizations (sorting + pruning) greatly reduce actual runtime.
//
// 🔹 Space Complexity: O(k + N)
//     - `subsetSums` of size K + recursion stack depth = N.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Recursive helper to try placing nums[idx] into one of K subsets
    bool backtrack(int idx, vector<int>& nums, vector<int>& subsetSums, int target) {
        // ✅ Base case: all numbers placed
        if (idx == nums.size()) {
            // Check all subsets equal to target
            for (int s : subsetSums)
                if (s != target)
                    return false;
            return true;
        }

        // 🔁 Try placing nums[idx] in each subset
        for (int i = 0; i < subsetSums.size(); i++) {
            // ❌ Skip if sum exceeds target
            if (subsetSums[i] + nums[idx] > target)
                continue;

            // Choose: add current number to subset i
            subsetSums[i] += nums[idx];

            // Recurse for next element
            if (backtrack(idx + 1, nums, subsetSums, target))
                return true;

            // Undo choice (backtrack)
            subsetSums[i] -= nums[idx];

            // 🧠 Optimization:
            // If this subset is still 0 after removing → no point trying others
            if (subsetSums[i] == 0)
                break;
        }

        return false;
    }

    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int n = nums.size();

        int sum = accumulate(nums.begin(), nums.end(), 0);

        // ❌ If total sum not divisible by k → not possible
        if (sum % k != 0)
            return false;

        int target = sum / k;

        // 🔹 Sort in descending order for better pruning
        sort(nums.rbegin(), nums.rend());

        vector<int> subsetSums(k, 0);

        // Start recursive assignment
        return backtrack(0, nums, subsetSums, target);
    }
};

// 🧪 Example usage
// int main() {
//     Solution sol;
//     vector<int> nums = {4, 3, 2, 3, 5, 2, 1};
//     int k = 4;
//     cout << sol.canPartitionKSubsets(nums, k); // Output: 1 (true)
// }

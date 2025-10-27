// 🔹 Problem: 473. Matchsticks to Square
// 🔹 Link: https://leetcode.com/problems/matchsticks-to-square/

// ✅ Approach:
// We are given an array of matchsticks, and we need to check if we can form a square using all of them.
// A square has 4 equal sides, so each side must have a sum = total_sum / 4.
//
// 1️⃣ First, check if total sum of all matchsticks is divisible by 4.
//     - If not divisible, we can’t make 4 equal sides → return false.
//
// 2️⃣ Our goal: distribute all matchsticks among 4 sides such that each side’s length = total_sum / 4.
//
// 3️⃣ Use **backtracking**:
//     - Try to assign each matchstick to one of the 4 sides.
//     - If any side exceeds `side_length`, backtrack.
//     - Continue until all sticks are used (idx == n).
//
// 4️⃣ Optimization: sort the matchsticks in descending order.
//     - Placing larger sticks first helps fail faster (reduces recursion depth).
//
// 5️⃣ Base case:
//     - If all matchsticks are placed, check if all sides are equal.
//
// 🔹 Example:
//     matchsticks = [1,1,2,2,2]
//     total_sum = 8 → side_length = 2
//     Possible grouping: [1,1], [2], [2], [2] ✅
//
// 🔹 Time Complexity: O(4^N)
//     - Each matchstick can go to any of 4 sides.
//     - But with pruning (sorting), practical performance is much faster.
//
// 🔹 Space Complexity: O(N)
//     - Due to recursion stack.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int side_length;

    // Recursive helper to assign matchsticks to 4 sides
    bool solve(int idx, int side1, int side2, int side3, int side4, vector<int>& ms) {
        // ✅ Base case: all matchsticks are placed
        if (idx == ms.size()) {
            // If all 4 sides are equal, square formed successfully
            return (side1 == side2 && side2 == side3 && side3 == side4);
        }

        // ❌ Pruning: if any side exceeds required length
        if (side1 > side_length || side2 > side_length || side3 > side_length || side4 > side_length) {
            return false;
        }

        // 🔁 Try assigning current matchstick to each side
        bool path1 = solve(idx + 1, side1 + ms[idx], side2, side3, side4, ms);
        bool path2 = solve(idx + 1, side1, side2 + ms[idx], side3, side4, ms);
        bool path3 = solve(idx + 1, side1, side2, side3 + ms[idx], side4, ms);
        bool path4 = solve(idx + 1, side1, side2, side3, side4 + ms[idx], ms);

        // ✅ If any configuration works, return true
        return (path1 || path2 || path3 || path4);
    }

    bool makesquare(vector<int>& matchsticks) {
        int n = matchsticks.size();
        int sum = accumulate(matchsticks.begin(), matchsticks.end(), 0);

        // ❌ If total sum is not divisible by 4 → can’t form square
        if (sum % 4 != 0) return false;

        side_length = sum / 4;

        // 🔹 Sort in descending order for optimization
        sort(matchsticks.rbegin(), matchsticks.rend());

        // 🔹 Start recursive search
        return solve(0, 0, 0, 0, 0, matchsticks);
    }
};

// 🧪 Example usage
// int main() {
//     Solution sol;
//     vector<int> matchsticks = {1, 1, 2, 2, 2};
//     cout << sol.makesquare(matchsticks); // Output: 1 (true)
// }

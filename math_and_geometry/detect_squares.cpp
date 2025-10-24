// ------------------------------------------------------------
// LeetCode 2013: Detect Squares
// Category: Math and Geometry / Hashing
// Difficulty: Medium
//
// 🧠 Idea:
// We are given a stream of points (x, y). For each query point,
// we need to count how many distinct squares can be formed with
// that query point as one of the vertices.
//
// Approach:
// 1. Use a hashmap `mp[x][y]` to store how many times point (x, y)
//    has appeared.
// 2. Maintain a list `points` to quickly iterate through all
//    previously added points.
// 3. For a query (x, y), check each existing point (x1, y1) —
//    if it can be a diagonal point of a square with (x, y).
//    That happens when |x1 - x| == |y1 - y| and x1 != x, y1 != y.
//
// If they form a diagonal, then the other two corners of the
// square are:
//     (x1, y)  and  (x, y1)
//
// We count how many times each of those two points exists.
// Each combination of those contributes one distinct square.
//
// So total squares = freq[(x1, y)] * freq[(x, y1)]
//
// ⚠️ Why multiply instead of taking min()?
// Because each occurrence of (x1, y) can pair with each
// occurrence of (x, y1) — they form *combinations*.
// Example:
//   (x1, y) appears 2 times, (x, y1) appears 3 times
//   → total 2 × 3 = 6 distinct squares.
//
// ------------------------------------------------------------
// 🧩 Time Complexity:
//   - add() → O(1)
//   - count() → O(N) per query (iterate all points)
//
// 💾 Space Complexity: O(N) for storing all points & frequencies
// ------------------------------------------------------------

#include <bits/stdc++.h>
using namespace std;

class DetectSquares {
public:
    // store all added points
    vector<vector<int>> points;

    // frequency map: mp[x][y] = count of point (x, y)
    unordered_map<int, unordered_map<int, int>> mp;

    DetectSquares() {}

    // Function to add a new point
    void add(vector<int> point) {
        int x = point[0];
        int y = point[1];

        points.push_back(point);
        
        mp[x][y]++; // increment frequency of this point
    }

    // Function to count how many squares can be formed
    int count(vector<int> point) {
        int x = point[0];
        int y = point[1];
        int ans = 0;

        // check all existing points to find potential diagonals
        for (auto& p : points) {
            int x1 = p[0];
            int y1 = p[1];

            // not a diagonal point if x or y are same
            if (x1 == x || y1 == y) continue;

            // must satisfy the property of a square
            if (abs(x1 - x) != abs(y1 - y)) continue;

            // we have found a diagonal point
            int freqA = mp[x1][y]; // frequency of horizontal point
            int freqC = mp[x][y1]; // frequency of vertical point

            ans += freqA * freqC; // combinations of A and C
        }

        return ans;
    }
};

/**
 * Example usage:
 *
 * DetectSquares* obj = new DetectSquares();
 * obj->add({3, 10});
 * obj->add({11, 2});
 * obj->add({3, 2});
 * int result = obj->count({11, 10});
 * cout << result << endl; // Output: 1
 */

/*
LeetCode 43 — Multiply Strings

🧩 Problem:
You are given two non-negative integers `num1` and `num2` represented as strings.
Return their product, also represented as a string.
You must not use any built-in BigInteger library or convert the inputs directly to integers.

---------------------------------------------
🔹 Approach — Simulating Manual Multiplication
---------------------------------------------

Imagine multiplying numbers on paper:

       123
     x  45
    -------
       615   ← (123 × 5)
+    4920   ← (123 × 4), shifted one position to left
    -------
      5535

We do exactly the same in code — multiply digit by digit from the end (like by hand)
and store results in an array of size (n1 + n2).

---------------------------------------------
🧮 Steps:
1️⃣ Initialize a result vector `res` of size n1 + n2 filled with 0.
2️⃣ Traverse both numbers from right to left.
3️⃣ Multiply each digit pair and add to the corresponding index in `res`.
4️⃣ Handle carry-over correctly.
5️⃣ Remove leading zeros and convert to string.

---------------------------------------------
⏱️ Time Complexity: O(n1 * n2)
📦 Space Complexity: O(n1 + n2)
---------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") {
            return "0";
        }

        int n1 = num1.size();
        int n2 = num2.size();
        vector<int> res(n1 + n2, 0);

        // Step 1: Multiply digits from right to left
        for (int i = n1 - 1; i >= 0; i--) {
            for (int j = n2 - 1; j >= 0; j--) {

                // 🔹 Multiply single digits (convert char → int)
                int mul = (num1[i] - '0') * (num2[j] - '0');

                // 🔹 Add product to current position in result
                int sum = mul + res[i + j + 1];

                // 🔹 Store the current digit
                res[i + j + 1] = sum % 10;

                // 🔹 Carry over to the previous index
                res[i + j] += sum / 10;
            }
        }

        // Step 2: Skip any leading zeros
        int start_idx = 0;
        while (start_idx < res.size() && res[start_idx] == 0) {
            start_idx++;
        }

        // Step 3: Convert result array to string
        string ans = "";
        for (int k = start_idx; k < res.size(); k++) {
            ans += (res[k] + '0');
        }

        return ans;
    }
};

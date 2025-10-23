#include <iostream>
using namespace std;

/*
Problem: LeetCode 50 - Pow(x, n)
Implement pow(x, n), which calculates x raised to the power n (x^n).

Approach: Binary Exponentiation (Divide & Conquer)
- Idea: Reduce the number of multiplications by exploiting:
    - If n is even: x^n = (x*x)^(n/2)
    - If n is odd:  x^n = x * (x*x)^((n-1)/2)
- Handles negative powers by converting x^(-n) = (1/x)^n
*/

class Solution {
public:
    // Recursive helper function to compute x^n
    double solve(double x, long n) {
        // Base case: any number raised to 0 is 1
        if (n == 0) return 1;

        // Handle negative powers
        if (n < 0) return solve(1 / x, -n);

        // If n is odd
        if (n & 1) {
            // Example: x^3 = x * (x^2)
            return x * solve(x * x, (n - 1) / 2);
        } else {
            // If n is even: x^10 = (x^2)^5
            return solve(x * x, n / 2);
        }
    }

    double myPow(double x, int n) {
        // Cast n to long to avoid integer overflow for INT_MIN
        return solve(x, (long)n);
    }
};

int main() {
    Solution sol;

    double x = 2.0;
    int n = 10;

    cout << x << "^" << n << " = " << sol.myPow(x, n) << endl;

    x = 2.0;
    n = -2;
    cout << x << "^" << n << " = " << sol.myPow(x, n) << endl;

    return 0;
}

/*
Time Complexity (TC):
- O(log n)
- Reason: At each step, n is divided by 2 (binary exponentiation)

Space Complexity (SC):
- O(log n) due to recursion stack
- Can be reduced to O(1) with iterative approach
*/

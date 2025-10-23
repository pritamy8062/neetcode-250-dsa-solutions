#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // ==============================
    // Brute Force Approach O(n^2)
    // ==============================
    int canCompleteCircuitBF(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();

        // Try starting at each station
        for (int start = 0; start < n; start++) {
            int fuel = 0;
            bool canComplete = true;

            // Simulate the circular route
            for (int i = 0; i < n; i++) {
                int station = (start + i) % n;
                fuel += gas[station] - cost[station];
                if (fuel < 0) {
                    canComplete = false;
                    break;
                }
            }

            if (canComplete) return start; // Found a valid starting station
        }

        return -1; // No valid starting station
    }

    // ==============================
    // Optimal Approach (Greedy) O(n)
    // ==============================
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        int totalGas = 0, totalCost = 0;

        // Step 1: Check if total gas is enough
        for (int i = 0; i < n; i++) {
            totalGas += gas[i];
            totalCost += cost[i];
        }
        if (totalGas < totalCost) return -1;

        // Step 2: Find the starting station
        int start_index = 0, tank = 0;
        for (int i = 0; i < n; i++) {
            tank += gas[i] - cost[i];
            if (tank < 0) {
                start_index = i + 1;
                tank = 0;
            }
        }

        return start_index;
    }
};

int main() {
    vector<int> gas = {1, 2, 3, 4, 5};
    vector<int> cost = {3, 4, 5, 1, 2};

    Solution sol;

    // Test both approaches
    cout << "Brute Force Start Index: " << sol.canCompleteCircuitBF(gas, cost) << "\n";
    cout << "Optimal Start Index: " << sol.canCompleteCircuit(gas, cost) << "\n";

    return 0;
}

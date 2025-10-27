/*
LeetCode 895 — Maximum Frequency Stack (FreqStack)

Problem:
Implement FreqStack, a stack-like data structure that supports:
- push(int val): push an integer onto the stack.
- pop(): remove and return the element with the highest frequency.
  If multiple elements have the same highest frequency, pop and return the one which was pushed most recently.

Approach (Idea):
- Maintain two data structures:
  1) freq_map[val] -> frequency (how many times val has been pushed)
  2) freq_stack[f] -> stack of values that have frequency f (values ordered by push-time;
                      top is the most recently pushed among those with frequency f)
- Track max_freq: the current maximum frequency among all values.
- push(val):
    - increment freq_map[val]
    - push val into freq_stack[freq_map[val]]
    - update max_freq if needed
- pop():
    - look at freq_stack[max_freq], pop the top (most recent with max frequency)
    - decrement freq_map for that value
    - if freq_stack[max_freq] becomes empty, decrement max_freq

Time Complexity:
- push: O(1)
- pop:  O(1)

Space Complexity:
- O(N) where N is the number of pushed elements (stored across stacks and map)

Notes:
- We use stack<int>& reference when accessing freq_stack[max_freq] to modify the stack
  stored inside the map directly (not a copy).
*/

#include <bits/stdc++.h>
using namespace std;

class FreqStack {
public:
    // frequency map: value -> frequency
    unordered_map<int, int> freq_map;

    // map frequency -> stack of values with that frequency
    // each stack keeps values in push order (top = most recent)
    unordered_map<int, stack<int>> freq_stack;

    // current maximum frequency
    int max_freq;

    FreqStack() {
        max_freq = 0;
    }

    // Push value into the FreqStack
    void push(int val) {
        // increase frequency count
        freq_map[val]++;

        int current_element_freq = freq_map[val];

        // update max_freq if this value's freq exceeds it
        if (current_element_freq > max_freq) {
            max_freq = current_element_freq;
        }

        // push the value into the stack corresponding to its frequency
        // freq_stack[current_element_freq] returns the stack for this frequency.
        freq_stack[current_element_freq].push(val);
    }

    // Pop and return the most frequent and most recent element
    int pop() {
        // Access the stack for the current max frequency by reference.
        // IMPORTANT: use a reference (stack<int>&) so we modify the actual stack
        // stored inside freq_stack. If we use a copy, popping would affect only
        // the copy and not the stored data.
        stack<int>& stk = freq_stack[max_freq];

        int answer = stk.top();
        stk.pop();

        // If the stack for this frequency becomes empty, erase it and update max_freq
        if (stk.empty()) {
            // remove the empty stack from the map (optional but keeps map clean)
            freq_stack.erase(max_freq);
            // decrement max_freq
            max_freq = max_freq - 1;
        }

        // reduce frequency of the popped value
        freq_map[answer]--;

        return answer;
    }
};

/**
Example usage:

int main() {
    FreqStack* fs = new FreqStack();
    fs->push(5);
    fs->push(7);
    fs->push(5);
    fs->push(7);
    fs->push(4);
    fs->push(5);
    cout << fs->pop() << endl; // returns 5 (freq 3)
    cout << fs->pop() << endl; // returns 7 (freq 2, but 7 is most recent among freq 2)
    cout << fs->pop() << endl; // returns 5
    cout << fs->pop() << endl; // returns 4 or 7 depending on remaining freqs
    delete fs;
    return 0;
}

Complexity: explained above.
*/

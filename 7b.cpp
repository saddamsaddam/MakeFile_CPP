#include <iostream>
#include <cstring> // For memset

using namespace std;

#define MAX_DIGITS 1000 // Maximum number of digits we support

// Function to copy one number to another (digit-wise)
void copyNumber(int dest[], int src[]) {
    for (int i = 0; i < MAX_DIGITS; i++) {
        dest[i] = src[i];
    }
}

// Function to add two large numbers (stored as arrays)
void addNumbers(int result[], int num1[], int num2[]) {
    int carry = 0;
    for (int i = 0; i < MAX_DIGITS; i++) {
        int sum = num1[i] + num2[i] + carry;
        result[i] = sum % 10;  // Store single digit
        carry = sum / 10;      // Carry for next digit
    }
}

// Memoization table to store results of subproblems
int memo[MAX_DIGITS][MAX_DIGITS];
bool computed[MAX_DIGITS]; // To check if L(n) has been computed

// Recursive function with memoization to compute Fibonacci-like sequence
void fibLikeRecursive(int n, int result[]) {
    if (computed[n]) {
        copyNumber(result, memo[n]); // Return the precomputed result
        return;
    }

    // Base cases
    if (n == 0) {
        result[0] = 3;  // L(0) = 3
    } else if (n == 1) {
        result[0] = 2;  // L(1) = 2
    } else {
        int L_n_minus_1[MAX_DIGITS] = {0};
        int L_n_minus_2[MAX_DIGITS] = {0};

        // Compute L(n-1)
        fibLikeRecursive(n - 1, L_n_minus_1);

        // Compute L(n-2)
        fibLikeRecursive(n - 2, L_n_minus_2);

        // Add L(n-1) and L(n-2) to get L(n)
        addNumbers(result, L_n_minus_1, L_n_minus_2);
    }

    // Store the result in the memoization table
    copyNumber(memo[n], result);
    computed[n] = true;
}

// Function to print a large number
void printNumber(int num[]) {
    bool leadingZero = true;
    for (int i = MAX_DIGITS - 1; i >= 0; i--) {
        if (num[i] != 0) leadingZero = false;
        if (!leadingZero) cout << num[i];
    }
    if (leadingZero) cout << "0";  // Special case: if all digits are 0
}

int main() {
    cout << "Recursive Approach with Memoization (O(n) Time):\n";

    // Initialize memoization table
    memset(computed, false, sizeof(computed));

    for (int i = 0; i <= 50; i++) {
        int result[MAX_DIGITS] = {0};
        int n = i * 10;

        fibLikeRecursive(n, result);

        cout << "L[" << n << "] = ";
        printNumber(result);
        cout << endl;
    }

    return 0;
}
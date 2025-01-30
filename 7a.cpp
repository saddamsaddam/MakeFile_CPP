#include <iostream>
#include <cstring> // For memset

using namespace std;

#define MAX_DIGITS 1000 // Maximum number of digits to store large numbers

// Function to copy one large number (array representation)
void copyNumber(int dest[], int src[]) {
    for (int i = 0; i < MAX_DIGITS; i++) {
        dest[i] = src[i];
    }
}

// Function to add two large numbers (array representation)
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

// Recursive function with memoization to compute Fibonacci-like numbers
void fibLikeRecursive(int n, int result[]) {
    if (computed[n]) {
        copyNumber(result, memo[n]);
        return;
    }

    if (n == 0) {
        result[0] = 3;  // L(0) = 3
    } else if (n == 1) {
        result[0] = 2;  // L(1) = 2
    } else {
        int L0[MAX_DIGITS] = {0}, L1[MAX_DIGITS] = {0};
        fibLikeRecursive(n - 1, L1); // Compute L(n-1)
        fibLikeRecursive(n - 2, L0); // Compute L(n-2)
        addNumbers(result, L0, L1);  // L(n) = L(n-1) + L(n-2)
    }

    // Store the result in the memoization table
    copyNumber(memo[n], result);
    computed[n] = true;
}

// Function to print a large number stored in an array
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

    // Test for different values of n
    for (int i = 0; i <= 10; i++) {
        int result[MAX_DIGITS] = {0};
        int n = i * 5; // Using n as 5, 10, 15, 20, etc.

        fibLikeRecursive(n, result);  // Using recursive approach with memoization

        cout << "L[" << n << "] = ";
        printNumber(result);  // Print the result
        cout << endl;
    }

    return 0;
}
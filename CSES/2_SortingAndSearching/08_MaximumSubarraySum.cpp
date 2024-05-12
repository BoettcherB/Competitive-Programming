/*

You are given an array of n integers x1...xn that can be positive or negative.
Find the subarray with the maximum sum, and print this sum.

Constraints:
    1 <= n <= 200,000
    -1,000,000,000 <= x <= 1,000,000,000

Example Input:
8
-1 3 -2 5 3 -5 2 2

Example Output:
9

Loop through the array while keeping track of the current sum and the maximum
sum found. If the current sum goes below zero, reset it to 0.

*/

#include <iostream>

const int N = 2e5 + 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, arr[N];
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    long long max = -1e18, cur = 0;
    for (int i = 0; i < n; ++i) {
        cur += arr[i];
        max = std::max(max, cur);
        cur = std::max(cur, 0LL);
    }
    std::cout << max << '\n';
}

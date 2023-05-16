/*

You are given an integer n and all numbers 1..n (inclusive) except one.
Determine which number is missing and print it.

Constraints:
 - 2 <= n <= 200,000

Example Input:
5
2 3 1 5

Example Output:
4

Solve this problem by setting up an array where arr[i] = 0 for all 1 <= i <= n.
Then, for every number x we are given, set arr[x] = 1. Finally, loop through
arr and find the index where arr[x] is still 0.

*/

#include <iostream>
#include <algorithm>

const int N = 2e5 + 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, arr[N] = {};
    std::cin >> n;
    for (int i = 1; i < n; ++i) {
        int x;
        std::cin >> x;
        arr[x] = 1;
    }
    std::cout << std::find(arr + 1, arr + n + 1, 0) - arr << '\n';
}

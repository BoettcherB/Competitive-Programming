/*

You have n coins with positive integer values x1...xn. What is the smallest sum
you cannot create using a subset of these coins?

Constraints:
    1 <= n <= 200,000
    1 <= x <= 1,000,000,000

Example Input:
5
2 9 1 2 7

Example Output:
6

First, sort the coins by value. Let S be the sum of all previous coins (if we
are considering coin i then S = c_0 + c_1 + ... + c_i-1). For every index i,
assume that we can create all sums up to S. Therefore, c_i must be <= S + 1. If
c_i > S + 1, then we cannot create the sum S + 1 and that is the answer.

*/

#include <iostream>
#include <algorithm>

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
    std::sort(arr, arr + n);
    long long max = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] > max + 1)
            break;
        max += arr[i];
    }
    std::cout << max + 1 << '\n';
}

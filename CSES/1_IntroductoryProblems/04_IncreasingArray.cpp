/*

You are given an array of n elements. If one operation involves increasing a
single element by 1, determine the minimum number of operations needed to make
the array increasing (a[i-1] <= a[i] for all 1 < i <= n).

Constraints:
    1 <= n <= 200,000
    1 <= a[i] <= 1,000,000,000

Example Input:
5
3 2 5 1 7

Example Output:
5

For every 1 < i <= n, determine whether element a[i] is smaller than the
previous element a[i-1]. If so, we need to perform a[i-1] - a[i] operations to
make the array non-decreasing. Keep a count of the total number of operations
in a 64-bit integer (long long).

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
    long long moves = 0;
    for (int i = 1; i < n; ++i) {
        if (arr[i - 1] > arr[i]) {
            moves += arr[i - 1] - arr[i];
            arr[i] = arr[i - 1];
        }
    }
    std::cout << moves << '\n';
}

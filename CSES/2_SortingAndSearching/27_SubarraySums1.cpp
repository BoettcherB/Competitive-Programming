/*

You are given an array of n positive integers [a0, a1, ..., an]. Your task is
to count the number of subarrays that have the sum x.

Constraints
    1 <= n <= 200,000
    1 <= x, a <= 1,000,000,000

Example Input:
5 7
2 4 1 2 7

Example Output:
3

This can be solved with the 2-pointers method. Keep 2 pointers p1 and p2 and a
sum variable that contains the sum of the subarray from indices p1 to p2. If
the sum of the subarray is less than x, increment p2 and update the sum. If the
sum of the subarray is greater than x, increment p1 and update the sum.

*/

#include <iostream>

const int N = 2e5 + 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, x, arr[N];
    std::cin >> n >> x;
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    int p1 = 0, p2 = 0, sum = arr[0], res = 0;
    while (p2 < n) {
        if (sum == x)
            ++res;
        if (p1 == p2 || sum <= x)
            sum += arr[++p2];
        else if (sum > x)
            sum -= arr[p1++];
    }
    std::cout << res << '\n';
}

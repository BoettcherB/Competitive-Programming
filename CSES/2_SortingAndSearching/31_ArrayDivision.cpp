/*

CSES: Sorting and Searching: Apple Division

You are given an array of n integers [a0, a1, ..., an]. Your task is to divide
the array into k subarrays such that the largest sum of a subarray is as small
as possible.

Constraints:
    1 <= k <= n <= 200,000
    1 <= a <= 1,000,000,000

Example Input:
5 3
2 4 7 3 5

Example Output:
8

A simpler problem is: given an array arr[n] and a sum S, is it possible to
divide arr into k subarrays such that the maximum sum is <= S? This problem is
easily solved in O(n) time. Simply loop through the array keeping track of the
current sum and the number of subarrays needed. If the current sum goes above
S, increment the number of subarrays and reset the current sum for the next
subarray. If we need more than k subarrays, then the answer is false.

Now, we need to find the optimal (smallest) value of S where the simpler
problem above returns true for a[n] and k. We can find this using binary search
from 0 to 1e9 * n (which is the maximum possible total sum of values of a[n]).

*/

#include <iostream>

const int N = 2e5 + 10;
int n, k, arr[N];

bool check(long long sum) {
    int subarrays = 1;
    long long cur = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] > sum)
            return false;
        if (cur + arr[i] > sum) {
            cur = 0;
            if (++subarrays > k)
                return false;
        }
        cur += arr[i];
    }
    return true;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    long long l = 0, r = 1e9 * n;
    while (l + 1 < r) {
        long long mid = (l + r) / 2;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    std::cout << r << '\n';
}

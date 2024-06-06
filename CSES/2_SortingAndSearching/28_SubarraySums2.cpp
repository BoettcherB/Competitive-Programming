/*

You are given an array of n positive integers [a0, a1, ..., an]. Your task is
to count the number of subarrays that have the sum x.

Constraints
    1 <= n <= 200,000
    -1,000,000,000 <= x, a <= 1,000,000,000

Example Input:
5 7
2 -1 3 5 -2

Example Output:
2

This problem is similar to the previous one (Subarray Sums I) except now
integers can be negative so the 2-pointers method does not work. Instead we can
solve this by calculating the prefix sums of the array and adding them to a
map where the key is the prefix sum and the value is the number of times that
sum has occurred (note that since values can be <= 0, prefix sums can occur
multiple times). The main idea is if we start from the beginning of the array
(i = 0) and there is a prefix sum that equals x, then there is a subarray
starting at i = 0 that sums to x. If we move on to the next index (i = 1) and
there is a prefix sum that equals x + a[0], then there is a subarray starting
at i = 1 that sums to x. (if prefix[j] - prefix[0] == x, then prefix[j] = x +
a[0]). For i = 2 we can check if any prefix sum equals x + a[0] + a[1]. The
values in the map tell us how many prefix sums there are at a specific value.
After considering a sum at index i, remember to delete prefix[i] from the map
(decrement the value at that sum).


*/

#include <iostream>
#include <map>

const int N = 2e5 + 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, arr[N];
    long long x, prefix[N];
    std::map<long long, long long> map;
    std::cin >> n >> x;
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
        prefix[i] = arr[i] + (i > 0 ? prefix[i - 1] : 0);
        ++map[prefix[i]];
    }
    long long res = 0;
    for (int i = 0; i < n; ++i) {
        res += map[x];
        x += arr[i];
        --map[prefix[i]];
    }
    std::cout << res << '\n';
}

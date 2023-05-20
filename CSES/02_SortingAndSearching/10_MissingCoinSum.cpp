/*

You have n coins with positive integer values x1...xn. What is the smallest sum
you cannot create using a subset of these coins?

Constraints:
 - 1 <= n <= 200,000
 - 1 <= x <= 1,000,000,000

Example Input:
5
2 9 1 2 7

Example Output:
6

We can see that the smallest value must be 1. The next value must be either 1
or 2. The third value must be in the range 1-4 (1-3 if the previous value was
1). By examining these small inputs, we can see that the value at index i can't
be greater than the sum of all the previous values plus one. Sort the coins by
value, then for every index i check that the value of the coin at index i is
less than the sum of all the previous coins + 1. If not, the answer is that
sum + 1.

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
    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] > sum + 1)
            break;
        sum += arr[i];
    }
    std::cout << sum + 1 << '\n';
}

/*

CSES: Sorting and Searching: Factory Machines

There are n machines in a factory. Each machine has a time k which is the time
in seconds it takes that machine to make 1 product. The goal is to make t
products. What is the shortest amount of time needed to make all t products?

Constraints:
    1 <= n <= 200,000
    1 <= t <= 1,000,000,000
    1 <= k <= 1,000,000,000

Example Input:
3 7
3 2 5

Example Output:
8

We can define a simpler problem P(t, x) which returns true if we can make all t
products in x seconds. This problem runs in O(n) time and is very simple to
solve (for each machine, calculate how many products it can make in x seconds
(x/k), sum the results, and compare to t). To find the smallest x that allows
us to make all t products, use binary search (L = 1, R = 1e18). Calculate the
midpoint M. If we are able to make t products in M seconds, set R = M.
Otherwise, set L = M.

*/

#include <iostream>

const int N = 2e5 + 10;
int n, t, machine[N];

bool canMakeAll(long long time) {
    long long canMake = 0;
    for (int i = 0; i < n; ++i) {
        canMake += time / machine[i];
        if (canMake >= t) break;
    }
    return canMake >= t;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> n >> t;
    for (int i = 0; i < n; ++i) {
        std::cin >> machine[i];
    }
    long long l = 0, r = 1e18 + 1;
    while (l + 1 < r) {
        long long mid = (r - l) / 2 + l;
        if (canMakeAll(mid))
            r = mid;
        else
            l = mid;
    }
    std::cout << r << '\n';
}

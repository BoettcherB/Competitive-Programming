/*

CSES: Sorting and Searching: Ferris Wheel

There are n children who want to ride on a ferris wheel. Each gondola can
either have 1 or 2 children and has a maximum weight capacity of x. You are
given the weight w1...wn of every child. Determine the minimum number of
gondolas needed for every child.

Constraints:
    1 <= n <= 200,000
    1 <= x <= 1,000,000,000
    1 <= w <= x

Example Input:
4 10
7 2 3 9

Example Output:
3

This can be solved with a greedy 2-pointers method. First, sort the list of
weights. Consider the lightest and heaviest weight of the remaining children.
If the combination of these weights are > x, then the heaviest child must ride
alone. If the combination of weights is <= x, then the two children can ride
together.

*/

#include <iostream>
#include <algorithm>

const int N = 2e5 + 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, x, weights[N];
    std::cin >> n >> x;
    for (int i = 0; i < n; ++i) {
        std::cin >> weights[i];
    }
    std::sort(weights, weights + n);
    int p1 = 0, p2 = n - 1, res = 0;
    while (p1 <= p2) {
        if (weights[p1] + weights[p2] <= x) {
            ++p1;
            --p2;
            ++res;
        } else {
            --p2;
            ++res;
        }
    }
    std::cout << res << '\n';
}

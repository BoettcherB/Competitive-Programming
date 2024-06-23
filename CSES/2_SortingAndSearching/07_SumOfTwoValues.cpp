/*

CSES: Sorting and Searching: Sum of Two Values

You are given an array of n integers, and an integer x. You need to find 2
values in the array a_i and a_j where a_i + a_j is equal to x. Print i and j,
the positions of the values. If none exist, print "IMPOSSIBLE".

Constraints:
    1 <= n <= 200,000
    1 <= x, a <= 1,000,000,000

Example Input:
4 8
2 7 5 1

Example Output:
2 4

This can be solved with the greedy 2-pointers method. Sort the array, then
point the first pointer to the first element in the array, and the second
pointer to the last element in the array. If the sum of these 2 elements is
> x, move the second pointer to the left. If the sum is < x, move the first
pointer to the right. If the sum == x, print the indices of the elements.

*/

#include <iostream>
#include <algorithm>

const int N = 2e5 + 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, x;
    std::cin >> n >> x;
    std::pair<int, int> val[N];
    for (int i = 0; i < n; ++i) {
        std::cin >> val[i].first;
        val[i].second = i + 1;
    }
    std::sort(val, val + n);
    int p1 = 0, p2 = n - 1;
    while (p1 < p2) {
        int cur = val[p1].first + val[p2].first;
        if (cur < x)
            ++p1;
        else if (cur > x)
            --p2;
        else {
            std::cout << val[p1].second << ' ' << val[p2].second << '\n';
            return 0;
        }
    }
    std::cout << "IMPOSSIBLE\n";
}

/*

CSES: Sorting and Searching: Sum of Three Values

You are given n integers and you need to find three of them (at distinct
positions) whose sum is x. Print the indexes of the three integers.

Constraints:
    1 <= n <= 5000
    1 <= x, a <= 1,000,000,000

Example Input:
4 8
2 7 5 1

Example Output:
1 3 4

We will keep a map of {value, index} pairs which stores values as keys and
their index as the value. Loop through all pairs of integers in the array. For
a pair of values at indexes i and j we look in the map for x - val[i] - val[j].
If it exists, then we print the indexes of those numbers. It is important to
know when a {value, index} pair can be inserted into the map to avoid using a
number from the same index multiple times. A value can be inserted into the map
once all pairs containing that value have been checked. For example, we loop
through all pairs of integers (0, 1), (0, 2), (0, 3), etc. Once all pairs
containing index 0 have been checked, only then we can insert {val[0], 0} into
the map. At this point, it is not possible to duplicate the value at index 0
since that value will not come up again in another pair.

*/

#include <iostream>
#include <map>

const int N = 5010;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, x, nums[N];
    std::cin >> n >> x;
    for (int i = 1; i <= n; ++i) {
        std::cin >> nums[i];
    }
    std::map<int, int> map;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            auto itr = map.find(x - nums[i] - nums[j]);
            if (itr != map.end()) {
                std::cout << i << ' ' << j << ' ' << itr->second << '\n';
                return 0;
            }
        }
        map[nums[i]] = i;
    }
    std::cout << "IMPOSSIBLE" << '\n';
}

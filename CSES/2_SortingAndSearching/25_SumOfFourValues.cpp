/*

You are given n integers and you need to find four of them (at distinct
positions) whose sum is x. Print the indexes of the four integers.

Constraints
    1 <= n <= 1000
    1 <= x, a <= 1,000,000,000

Example Input:
4 8
2 7 5 1

Example Output:
1 3 4

We will keep a map of {value, {index, index}} pairs where the key is the sum of
two integers from the list and the value is a pair containing their indices.
Loop through all pairs of integers in the array. For a pair of values at
indexes i and j we look in the map for x - val[i] - val[j]. If it exists, then
we print the indexes of those numbers. It is important to know when a {value,
{index, index}} pair can be inserted into the map to avoid using a number from
the same index multiple times. The sum val[i]+val[j] can be inserted into the
map once all pairs containing those values have been checked. For example, we
loop through all pairs of integers (0, 1), (0, 2), (0, 3), etc. Once all pairs
containing the indices 0 and 1 have been checked, only then we can insert
{val[0]+val[1], {0, 1}} into the map. At this point, it is not possible to
duplicate the value at indices 0 or 1 since those values will not come up again
in another pair.

*/

#include <iostream>
#include <map>

const int N = 1010;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, x, nums[N];
    std::cin >> n >> x;
    for (int i = 1; i <= n; ++i) {
        std::cin >> nums[i];
    }
    std::map<int, std::pair<int, int>> map;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            auto itr = map.find(x - nums[i] - nums[j]);
            if (itr != map.end()) {
                std::cout << i << ' ' << j << ' ' << itr->second.first << ' ';
                std::cout << itr->second.second << '\n';
                return 0;
            }
        }
        for (int j = i - 1; j >= 1; --j) {
            map[nums[i] + nums[j]] = { i, j };
        }
    }
    std::cout << "IMPOSSIBLE" << '\n';
}

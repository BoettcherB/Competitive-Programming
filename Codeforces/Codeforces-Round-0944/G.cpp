/*

Problem Statement: https://codeforces.com/contest/1971/problem/G

If we examine numbers and their xors, we will notice that numbers can be put
into groups where every number in the group has XOR < 4 with every other number
in the group. For example { 0, 1, 2, 3 } is a group. So is { 4, 5, 6, 7 } and
{ 8, 9, 10, 11 }. Every 4 numbers is a group. We can solve this problem by
grouping each group together, sorting their values and indexes, and placing the
smaller values at the smaller indexes.

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        int n;
        std::cin >> n;
        std::vector<int> a(n);
        std::map<int, std::vector<int>> map;
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
            map[a[i] >> 2].push_back(i);
        }
        for (const auto& group : map) {
            std::vector<int> nums, indexes;
            for (int i : group.second) {
                nums.push_back(a[i]);
                indexes.push_back(i);
            }
            std::sort(nums.begin(), nums.end());
            std::sort(indexes.begin(), indexes.end());
            for (int i = 0; i < (int) nums.size(); ++i) {
                a[indexes[i]] = nums[i];
            }
        }
        for (int i = 0; i < n; ++i) {
            std::cout << a[i] << " \n"[i == n - 1];
        }
    }
}

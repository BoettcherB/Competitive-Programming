/*
You are given an array of n integers [x0, x1, ..., xn]. Your task is to find,
for each integer, the nearest position to its left containing a smaller value.
If there is no smaller value to the left, print 0 for that integer.

Constraints
    1 <= n <= 200,000
    1 <= x <= 1,000,000,000

Example Input:
8
2 5 1 4 8 3 2 5

Example Output:
0 1 0 3 4 3 3 7

One way to solve this is to sort the values while keeping track of their index
and keep a set of indexes we have encountered. Then loop through each sorted
value. For each value, check the set to find the largest index that is less
than the current index (we can do this using the upper_bound function). Since
the values are sorted, indexes in the set will contain values <= the current
value. If we sort the values in such a way that later indexes are considered
first, this will cause ties to be handled correctly.

*/

#include <iostream>
#include <algorithm>
#include <set>

const int N = 2e5 + 10;

struct Num {
    int val, index;
    bool operator<(const Num& other) const {
        return val == other.val ? index > other.index : val < other.val;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    Num nums[N];
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        nums[i] = { a, i + 1 };
    }
    std::sort(nums, nums + n);
    std::set<int> s;
    s.insert(0);
    int ans[N];
    for (int i = 0; i < n; ++i) {
        ans[nums[i].index] = *(--s.upper_bound(nums[i].index));
        s.insert(nums[i].index);
    }
    for (int i = 1; i <= n; ++i) {
        std::cout << ans[i] << " \n"[i == n];
    }
}

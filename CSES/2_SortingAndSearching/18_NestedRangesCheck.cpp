/*

You are given n ranges [a, b]. Your task is to figure out, for each range,
whether the range fully contains another range, and whether the range is fully
contained by another range. Print a line that describes for each range whether
it contains another range or not (1 or 0). Then print another line that
describes for each range whether it is contained or not (1 or 0).

Constraints:
    1 <= n <= 200,000
    1 <= a, b <= 1,000,000,000
    No range can appear more than once

Example Input:
4
1 6
2 4
4 8
3 6

Example Output:
1 0 0 0
0 1 0 1

Let start[i] = 'a' and end[i] = 'b' for a range i. Solve. by sorting the ranges
by 'a', then by 'b' in reverse (higher 'b' appears first). When sorted like
this, for any range i we know that all previous ranges have an earlier start
(start[prev] <= start[i]). If any previous range (prev) has a later end
(end[prev] >= end[i]), then we know that range i is contained in range prev. As
we loop through the ranges from 0 to n-1, keep track of the largest end seen so
far. If this value is >= end[i], then range i is contained in another range.

We can determine if a range contains another range in a similar way. If we loop
through the ranges in reverse, we know that for any range i, a previously
encountered range (prev) will have a later start (start[i] <= start[prev]). If
prev also has an earlier end (end[i] >= end[prev]), then range i contains range
prev. While looping through the ranges, keep track of the earliest end
encountered so far. If end[i] is >= this value, then range i contains another
range.

*/

#include <iostream>
#include <algorithm>

const int N = 2e5 + 10;

struct Range {
    int l, r, index;
    bool operator<(const Range& other) const {
        return l == other.l ? r > other.r : l < other.l;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    Range ranges[N];
    for (int i = 0; i < n; ++i) {
        std::cin >> ranges[i].l >> ranges[i].r;
        ranges[i].index = i;
    }
    std::sort(ranges, ranges + n);
    bool contains[N] = { false }, is_contained[N] = { false };
    int max_r = 0;
    for (int i = 0; i < n; ++i) {
        if (ranges[i].r <= max_r)
            is_contained[ranges[i].index] = true;
        else
            max_r = ranges[i].r;
    }
    int min_r = 2e9;
    for (int i = n - 1; i >= 0; --i) {
        if (ranges[i].r >= min_r)
            contains[ranges[i].index] = true;
        else
            min_r = ranges[i].r;
    }
    for (int i = 0; i < n; ++i) {
        std::cout << contains[i] << ' ';
    }
    std::cout << '\n';
    for (int i = 0; i < n; ++i) {
        std::cout << is_contained[i] << ' ';
    }
    std::cout << '\n';
}

/*

CSES: Sorting and Searching: Playlist

You are given a list of n integers x1...xn. What is the length of the longest
sequence of succesive integers that are unique?

Constraints:
    1 <= n <= 200,000
    1 <= x <= 1,000,000,000

Example Input:
8
1 2 1 3 2 7 4 2

Example Output:
5

Loop through the list while keeping track of the starting index of the unique
subarray. If we come across a new number, store its index in a map. If we come
across a number we have already seen, update the start of the unique subarray
to be the index where we previously saw that number + 1 (and then update that
number's index in the map to the current index). For every index i, the length
of the unique subarray is i - start + 1.

*/

#include <iostream>
#include <map>

const int N = 2e5 + 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, start = 0, best = 0;
    std::cin >> n;
    std::map<int, int> map;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        if (map.count(x) == 1) {
            start = std::max(start, map[x] + 1);
        }
        map[x] = i;
        best = std::max(best, i - start + 1);
    }
    std::cout << best << '\n';
}

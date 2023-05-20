/*

There n customers in a restaurant. You are given their arrival time and their
leaving time (a and b). Determine the maximum number of people that were in the
restaurant at any one point in time.

Constraints:
 - 1 <= n <= 200,000
 - 1 <= a < b <= 1,000,000,000

Example Input:
3
5 8
2 4
3 9

Example Output:
2

Combine both the arrival times and leaving times in a single array (while also
keeping track of whether a time is an arrival time or a leaving time). Then,
sort the array and iterate through it while keeping a counter for the number of
people currently in the restaurant. If the current time is an arrival time,
increment the counter. If it is a leaving time, decrement the counter.

*/

#include <iostream>
#include <algorithm>

const int N = 2e5 + 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    std::pair<int, int> times[2 * N];
    for (int i = 0; i < n; ++i) {
        std::cin >> times[i].first >> times[i + n].first;
        times[i].second = 1;
        times[i + n].second = 2;
    }
    std::sort(times, times + 2 * n);
    int cur = 0, max = 0;
    for (int i = 0; i < 2 * n; ++i) { 
        cur += times[i].second == 1 ? 1 : -1;
        max = std::max(cur, max);
    }
    std::cout << max << '\n';
}

/*

CSES: Sorting and Searching: Collecting Numbers

You are given an array that contains each number from 1 to n exactly once. Your
task is to collect each number in increasing order. On each round, you go
through the array from left to right and collect as many numbers as possible.
What is the fewest number of rounds needed?

Constraints:
    1 <= n <= 200,000

Example Input:
5
4 2 1 5 3

Example Output:
3

For each number, keep track of its index in the array. Sort the numbers by
value and then loop through them. A new round is needed if the index of the
i'th number is less than the index of the previous (i-1'th) number.

*/

#include <iostream>
#include <algorithm>

const int N = 2e5 + 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::pair<int, int> nums[N];
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> nums[i].first;
        nums[i].second = i;
    }
    std::sort(nums, nums + n);
    int rounds = 1;
    for (int i = 1; i < n; ++i) {
        rounds += nums[i].second < nums[i - 1].second;
    }
    std::cout << rounds << '\n';
}

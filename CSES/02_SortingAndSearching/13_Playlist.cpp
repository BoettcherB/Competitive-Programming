/*

You are given a list of n integers x1...xn. What is the length of the longest
sequence of succesive integers that are unique?

Constraints:
 - 1 <= n <= 200,000
 - 1 <= x <= 1,000,000,000

Example Input:
8
1 2 1 3 2 7 4 2

Example Output:
5

Loop through the list while keeping track of a set of integers that are in the
current sequence of unique integers, as well as where this sequence starts. If
the next integer is not in our set, add it. If the next integer is already in
the set, increment the start of the sequence until we pass the first occurrence
of that integer (while also removing elements from the set as we pass them).
The answer is the size of the set at its largest.

*/

#include <iostream>
#include <set>

const int N = 2e5 + 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, arr[N], res = 0, start = 0;
    std::cin >> n;
    std::set<int> s;
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
        if (s.count(arr[i]) == 0) {
            s.insert(arr[i]);
            res = std::max(res, i - start + 1);
        } else {
            while (arr[start] != arr[i]) {
                s.erase(arr[start]);
                ++start;
            }
            ++start;
        }
    }
    std::cout << res << '\n';
}

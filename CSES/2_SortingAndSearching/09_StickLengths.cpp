/*

There are n sticks, each with length p. Your task is to modify the sticks so
that they are all the same length. Changing a stick from length p1 to length p2
costs |p2 - p1| units. Find the minimum cost required to make all sticks the
same length.

Constraints:
    1 <= n <= 200,000
    1 <= p <= 1,000,000,000

Example Input:
5
2 3 1 5 2

Example Output:
5

Find the median length and change all sticks to have this length. If the length
of the array is even, either of the 'middle' elements will work. Sort the array
of lengths, then loop through them while modifying each length to be equal to
the length of the stick at position n/2.

*/

#include <iostream>
#include <algorithm>

const int N = 2e5 + 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, arr[N];
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    std::sort(arr, arr + n);
    long long cost = 0;
    for (int i = 0; i < n; ++i) {
        cost += std::abs(arr[i] - arr[n / 2]);
    }
    std::cout << cost << '\n';
}

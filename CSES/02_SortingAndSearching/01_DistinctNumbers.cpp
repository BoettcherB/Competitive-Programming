/*

You are given a list of n integers [x1...xn]. Determine the number of distinct
values in the list.

Constraints:
 - 1 <= n <= 200,000
 - 1 <= x <= 1,000,000,000

Example Input:
5
2 3 2 2 3

Example Output:
2

Sort the list, then find the number of positions i where a[i] != a[i-1]. The
answer is one plus this amount.

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
    int res = 1;
    for (int i = 1; i < n; ++i) {
        res += arr[i] != arr[i - 1];
    }
    std::cout << res << '\n';
}

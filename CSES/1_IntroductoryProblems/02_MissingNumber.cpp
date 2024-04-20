/*

You are given an integer n and all numbers 1..n (inclusive) except one.
Determine which number is missing and print it.

Constraints:
 - 2 <= n <= 200,000

Example Input:
5
2 3 1 5

Example Output:
4

Solve this problem by setting up a boolean array where arr[i] = false for all
1 <= i <= n. Then, for every number x we are given, set arr[x] = true. Finally,
loop through arr and find the index where arr[x] is still false.

*/

#include <iostream>

const int N = 2e5 + 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    bool found[N] = { false };
    for (int i = 0; i < n - 1; ++i) {
        int x;
        std::cin >> x;
        found[x] = true;
    }
    for (int i = 1; i <= n; ++i) {
        if (!found[i]) {
            std::cout << i << '\n';
            break;
        }
    }
}

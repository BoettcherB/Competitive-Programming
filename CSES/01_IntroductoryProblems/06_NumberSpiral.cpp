/*

If we arrange the integer numbers starting at 1 in a spiral grid (as shown in
this picture: https://cses.fi/problemset/task/1071/) where cell (1, 1) is at
the top left, find the number in cell (y, x) (row y and column x). Do this for
T test cases. 

Constraints:
 - 1 <= T <= 100,000
 - 1 <= y, x <= 1,000,000,000

Example Input:
3
2 3
1 1
4 2

Example Output:
8
1
15

This problem becomes easy once we notice a certain property of the spiral. For
every cell (y,x) below the diagonal (y > x), we can travel to the right to
reach the diagonal. This distance is y - x and the values along the path are
increasing or decreasing by only 1. Similarly, for every cell above the
diagonal (x > y) we can travel down a distance of x - y and these values are
also increasing or decreasing by only 1. If we can determine the values on the
diagonal (any cell (i,i)), then we can reverse this to find the value of cell
(y,x). We can find the value of cell (i,i) using the formula i * (i - 1) + 1.
i will be either x or y, which ever is greater. Then we can use the parity of i
to determine whether we add or subtract the distance (either x - y or y - x).

*/

#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    long long T;
    std::cin >> T;
    while (T--) {
        long long y, x, max, diag;
        std::cin >> y >> x;
        max = std::max(x, y);
        diag = max * (max - 1) + 1;
        std::cout << (diag + (max % 2 ? x - y : y - x)) << '\n';
    }
}

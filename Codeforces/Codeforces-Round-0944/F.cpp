/*

Problem Statement: https://codeforces.com/contest/1971/problem/F

The number of lattice points in the first quadrant (where x > 0 and y > 0) with
radius r from the origin is equal to the number of lattice points in the other
3 quadrants. Therefore, we only have to worry about the first quadrant and then
mulitply the answer by 4. We can start at the very right hand side of the
circle and work counter-clockwise. The first lattice point is [r, 0]. From any
lattice point [x, y] of radius r, the next lattice point of radius r must be
[x-1, y], [x, y+1], or [x-1, y-1], and only 1 of these can be of radius r. For
every point that we find, we just need to check those three points for the next
lattice point, until x is 0.

*/

#include <iostream>
#include <cmath>

bool good_dist(long long x, long long y, long long r) {
    return (long long) std::sqrt(x * x + y * y) == r;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        long long r;
        std::cin >> r;
        long long x = r, y = 0, res = 0;
        while (x > 0) {
            ++res;
            if (good_dist(x - 1, y, r))
                --x;
            else if (good_dist(x, y + 1, r))
                ++y;
            else {
                --x;
                ++y;
            }
        }
        std::cout << res * 4 << '\n';
    }
}

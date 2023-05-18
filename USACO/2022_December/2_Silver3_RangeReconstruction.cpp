/*

Problem Statement: http://usaco.org/index.php?page=viewproblem2&cpid=1256

If a[i-1] = x and r[i-1][i] = d, it is clear that a[i] must either be x+d or
x-d. We can determine which one of these is correct by looking at the min and
max values on the range j..i and comparing it to r[j][i] for all values 
0 <= j < i. If max - min != r[j][i], then that value cannot be the value of
a[i]. It is guaranteed that at least one of x+d and x-d will work. It is only
possible for both x+d and x-d to work for the second value (when i is 1,
assuming 0-index). Either choice is fine here, as the resulting arrays will
both be correct, though one of them will be flipped. We can start by setting
a[0] = 0, though any value will work here since any translation of the original
array is correct (as long as all the values are still in range).

*/

#include <iostream>

const int N = 310;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, range[N][N];
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            std::cin >> range[i][j];
        }
    }
    int res[N] = {};
    for (int i = 1; i < n; ++i) {
        int p1 = res[i - 1] + range[i - 1][i];
        int p2 = res[i - 1] - range[i - 1][i];
        int min = p1, max = p1;
        bool OK = true;
        for (int j = i - 1; j >= 0; --j) {
            min = std::min(min, res[j]);
            max = std::max(max, res[j]);
            if (max - min != range[j][i]) {
                OK = false;
                break;
            }
        }
        res[i] = OK ? p1 : p2;
    }
    std::cout << res[0];
    for (int i = 1; i < n; ++i) {
        std::cout << ' ' << res[i];
    }
    std::cout << std::endl;
}

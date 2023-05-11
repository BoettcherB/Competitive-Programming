/*

Problem Statement: http://usaco.org/index.php?page=viewproblem2&cpid=1252

The 'trick' to solving this problem is to realize that the optimal placement of
grass patches is as far to the right as possible (if we loop through the cows
starting from the left). Start from the left and loop through each cow. If a
cow at index i is not fed, place a grass patch for that cow at index i + k and
mark all cows in the range [i, i + 2*k] as fed.

*/

#include <iostream>
#include <string>
#include <algorithm>

const int N = 1e5 + 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        int n, k, patches = 0;
        std::string res, str;
        std::cin >> n >> k >> str;
        res = std::string(n, '.');
        bool hfed[N] = {}, gfed[N] = {};
        for (int i = 0; i < n; ++i) {
            bool* arr = str[i] == 'G' ? gfed : hfed;
            if (!arr[i]) {
                int idx = std::min(i + k, n - 1);
                res[res[idx] == '.' ? idx : --idx] = str[i];
                std::fill(arr + i, arr + std::min(i + 2 * k + 1, n), true);
                ++patches;
            }
        }
        std::cout << patches << '\n' << res << '\n';
    }
}

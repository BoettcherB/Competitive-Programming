/*

Problem Statement: https://usaco.org/index.php?page=viewproblem2&cpid=1252

We can use a greedy approach to solve this problem. Start at the leftmost index
and if the cow is not already within range of a patch of preferred grass, then
place a patch of grass as far to the right as possible. If the cow is at index
i then this will be at index i + k. If there is already a patch of grass at
i + k of the other grass type, then place the patch at index i + k - 1. For
example, assume we are trying to place a patch 'G' at index i + k. If there is
already an 'H' there, then place the 'G' at i + k - 1. This index is guaranteed
to be open because we are assuming that no other 'G' is within range of index i
and we would not have placed two 'H' patches right next to each other (unless
k == 0 but then there would not be an 'H' at i + k). If we place a patch 'G' at
i + k, then all Guernsey cows are covered until index i + 2k, so we can skip
all Guernsey cows with an index <= i + 2k.

*/

#include <iostream>
#include <vector>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        int n, k;
        std::string cows;
        std::cin >> n >> k >> cows;
        std::string grass(n, '.');
        int covered_g = -1, covered_h = -1, patches = 0;
        for (int i = 0; i < n; ++i) {
            if (cows[i] == 'G' && covered_g < i) {
                int index = std::min(i + k, n - 1);
                index -= grass[index] == 'H';
                grass[index] = 'G';
                ++patches;
                covered_g = index + k;
            }
            if (cows[i] == 'H' && covered_h < i) {
                int index = std::min(i + k, n - 1);
                index -= grass[index] == 'G';
                grass[index] = 'H';
                ++patches;
                covered_h = index + k;
            }
        }
        std::cout << patches << '\n' << grass << '\n';
    }
}

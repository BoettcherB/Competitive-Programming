/*

CSES: Dynamic Programming: Counting Tilings

Count the number of ways to place 2x1 and 1x2 tiles on an nxm grid.

Constraints:
    1 <= n <= 10
    1 <= m <= 1000

Example Input:
4 7

Example Output:
781

Since n can only be up to 10, it is possible to store the state of the entire
column for all m columns. Let dp[i][j] be the number of possible tilings when
columns [1, i-1] are full and column i has state j. The binary representation
of j determines which rows of column i are full. For example, if j = b1010110,
then rows 2, 3, 5, and 7 of column i contain a block.

Example (n = 3):
dp[2][1] = 1     dp[2][7] = 3    dp[3][3] = 4
|x               --  --  ||      --x   --x   --x   ||x
|x               ||  --  ||      --|   |||   |--   |||
--               ||  --  --      --|   |||   |--   --|

Let perms[i] be the list of ways to place vertical (2x1) blocks into a single
column. For example, if n = 4, there are 5 ways: {b0000, b1100, b0110, b0011,
b1111}. For each permutation, we can add the permutation to a grid with state
j if none of the bits overlap (ie. if perm + j == perm ^ j). For example, if
there is a grid where the final column has state j = b1000, then there are 3
permutations that we can add to the column: {b0000, b0110, b0011}. The other 2
permutations {b1100, b1111} overlap on the 4th bit. If j = b1010, then the only
permutation that fits is the one with 0 vertical blocks: {b0000}.

For a column i, we try placing each permutation in each of the 2^n possible
column states. We are able to place permutation p into column state j if none
of the bits overlap. In order to get column state j in the current column i,
we need to fill in column states from column i-1 with horizontal blocks. For
example, if state j = b10011 for column i-1 and we fill in the holes with
horizontal blocks, we will get state b01100 for column i. Note that this new
state is the previous state with all bits flipped (ie filling in state j for
column i-1 gets us state ~j for column i. Similarly, ~j -> j. Since there is
only 1 way to fill in horizontal blocks, dp[i][~j] equals dp[i-1][j] and
dp[i-1][j] equals dp[i][~j]. Similarly, there is only one way to add a
permutation to a column state. Therefore, the resulting column state, j + p,
receives all the tilings from column state j: dp[i][j + p] += dp[i][j].
However, dp[i][j] will be filled in as we work on column i. Therefore, it is
is better to use dp[i - 1][~j] (remember, these are the same).

Base case: dp[0][2^n - 1] = 1
Recurrence: dp[i][j + p] += dp[i - 1][~j] for all j,p if j + p == j ^ p

*/

#include <iostream>
#include <vector>

const int MOD = 1e9 + 7;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<long long>> dp(m + 1);
    for (int i = 0; i <= m; ++i) {
        dp[i] = std::vector<long long>(1 << n);
    }
    std::vector<std::vector<int>> perms(n + 1);
    perms[0] = perms[1] = { 0 };
    for (int i = 2; i <= n; ++i) {
        for (const auto& perm : perms[i - 1])
            perms[i].push_back(perm);
        for (const auto& perm : perms[i - 2])
            perms[i].push_back((3 << (i - 2)) | perm);
    }
    int all = (1 << n) - 1;
    dp[0][all] = 1;
    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j < (1 << n); ++j) {
            for (const auto& perm : perms[n]) {
                if ((perm + j) == (perm ^ j)) {
                    dp[i][perm + j] += dp[i - 1][~j & all];
                    dp[i][perm + j] %= MOD;
                }
            }
        }
    }
    std::cout << dp[m][all] << '\n';
}

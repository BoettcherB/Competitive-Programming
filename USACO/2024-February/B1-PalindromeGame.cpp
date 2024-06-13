/*

Problem Statement: https://usaco.org/index.php?page=viewproblem2&cpid=1395

The key here is the property that a palindrome can't start or end with 0. There
is no value of S that ends in 0 that allows the current player to immediately
reduce S to 0. If a player starts their turn and S is a multiple of 10, they
must remove some value x that will cause S to not be a multiple of 10. Then,
the other player can remove the one-digit value (S % 10) to turn S back into a
multiple of 10. The player on whose turn S is a multiple of 10 cannot escape,
and will lose the game. Therefore, Elsie wins if S starts as a multiple of 10
(the final digit is 0) and Bessie wins otherwise.

*/

#include <iostream>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        std::string str;
        std::cin >> str;
        std::cout << (str[str.length() - 1] == '0' ? 'E' : 'B') << '\n';
    }
}

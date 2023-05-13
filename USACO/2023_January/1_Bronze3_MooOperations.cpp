/*

Problem Statement: http://usaco.org/index.php?page=viewproblem2&cpid=1277

This problem can be broken down into a series of if/else statements:
1)  If the length of the string is < 3, forming MOO is impossible, so the
    answer is -1
2)  If the string contains the substring "MOO", remove all other characters. If
    the length of the string is L, this will take L-3 operations.
3)  If the string contains the substring "MO" anywhere except the very end of
    the string, we can remove all characters before and after (except for 1
    character after) and then flip that last character to 'O'. This will take
    L-3+1 = L-2 operations.
4)  If the string contains the substring "OO" anywhere except the very
    beginning of the string, we can remove all characters before and after
    (except for 1 character before) and flip that character to 'M'. This
    will also take L-2 operations.
5)  If the string contains the substring "OO" at the very beginning of the
    string, we can remove all but the first 3 characters and then flip the
    first to 'M' and the last to 'O'. This will take L-3+2 = L-1 operations.
6)  If none of the above conditions are met, we cannot form "MOO" so print -1.

Note that these checks should be done in order, and if the condition is
satisfied then that is the answer.

*/

#include <iostream>
#include <string>

const int N = 110;

int solve(const std::string& str) {
    size_t len = str.length();
    if (len < 3)
        return -1;
    if (str.find("MOO") != std::string::npos)
        return len - 3;
    size_t pos = str.find("MO");
    if (pos != std::string::npos && pos < len - 2)
        return len - 2;
    pos = str.rfind("OO");
    if (pos != std::string::npos)
        return (pos == 0 ? len - 1 : len - 2);
    return -1;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

#ifdef DEBUG_LOCAL
    freopen("in.txt", "r", stdin);
#endif

    int q;
    std::cin >> q;
    while (q--) {
        std::string str;
        std::cin >> str;
        std::cout << solve(str) << '\n';
    }
}

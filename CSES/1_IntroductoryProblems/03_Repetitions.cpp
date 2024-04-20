/*

You are given a string of length n containing the characters A, C, G, and T.
Find the length of the longest repetition in this string (a repetition is a
substring where all characters are the same).

Constraints:
    1 <= n <= 1,000,000

Example Input:
ATTCGGGA

Example Output:
3

To solve this problem, loop through the characters of the string while keeping
track of the length of the longest repetition and the position of the last
index where the characters changed.

*/

#include <iostream>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string str;
    std::cin >> str;
    int len = (int) str.length();
    int longest = 0;
    int last_change = 0;
    for (int i = 1; i < len; ++i) {
        if (str[i] != str[i - 1]) {
            longest = std::max(longest, i - last_change);
            last_change = i;
        }
    }
    std::cout << std::max(longest, len - last_change) << '\n';
}

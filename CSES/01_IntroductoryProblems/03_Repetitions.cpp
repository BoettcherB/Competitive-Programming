/*

You are given a string of length n containing the characters A, C, G, and T.
Find the length of the longest repetition in this string (a repetition is a
substring where all characters are equal).

Constraints:
 - 1 <= n <= 1,000,000

Example Input:
ATTCGGGA

Example Output:
3

To solve this problem, loop through the characters of the string while keeping
track of the length of the current repetition and the length of the longest
repetition.

*/

#include <iostream>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string str;
    std::cin >> str;
    int max = 0, cur = 0;
    char prev = 0;
    for (char c : str) {
        cur = (c == prev) ? cur + 1 : 1;
        max = std::max(cur, max);
        prev = c;
    }
    std::cout << max << '\n';
}

/*

You are given a string consisting of n letters A-Z. Rearrange the letters so
that the string is a palindrome. If this is not possible, print "NO SOLUTION".

Constraints:
 - 1 <= n <= 1,000,000

Example Input:
AAAACACBA

Example Output:
AACABACAA

Loop through all the letters of the string and count how many times each letter
appears. It is not possible to form a palindrome if there are multiple letters
that appear an odd number of times, or if there is a letter that appears an odd
number of times and the string has an even number of characters. Place the
first pair of letters that are the same in positions 0 and n-1, then place the
next pair in positions 1 and n-2.... If there is a letter with an odd count,
place the odd number in position n/2.

*/

#include <iostream>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string str;
    std::cin >> str;
    int count[26] = {};
    for (char c : str) {
        ++count[c - 'A'];
    }
    bool odd = false;
    int index = 0;
    for (int i = 0; i < 26; ++i) {
        if (count[i] % 2 == 1) {
            if (odd || str.length() % 2 == 0) {
                std::cout << "NO SOLUTION\n";
                return 0;
            }
            odd = true;
        }
        while (count[i] > 1) {
            str[index] = str[str.length() - 1 - index] = (i + 'A');
            count[i] -= 2;
            ++index;
        }
        if (count[i]) {
            str[str.length() / 2] = (i + 'A');
        }
    }
    std::cout << str << '\n';
}

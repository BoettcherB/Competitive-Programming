/*

CSES: Introductory Problems: Palindrome Reorder

You are given a string consisting of n letters A-Z. Rearrange the letters so
that the string is a palindrome. If this is not possible, print "NO SOLUTION".

Constraints:
    1 <= n <= 1,000,000

Example Input:
AAAACACBA

Example Output:
AACABACAA

Loop through all the letters of the string and count how many times each letter
appears. It is not possible to form a palindrome if there are multiple letters
that appear an odd number of times, or if there is one odd letter and the
string has an even number of characters, or if there are no odd letters and the
string has an odd number of characters. To rebuild the palindrome, place the
first pair of letters that are the same in positions 0 and n-1, then place the
next pair in positions 1 and n-2, and so on. If there is a letter with an odd
count, place it in position n/2.

*/

#include <iostream>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string str;
    std::cin >> str;
    int n = (int) str.length();
    int count[26] = { 0 };
    for (char c : str) {
        ++count[c - 'A'];
    }
    int numOdd = 0;
    for (int i = 0; i < 26; ++i) {
        numOdd += count[i] % 2 == 1;
    }
    if (numOdd > 1 || numOdd != n % 2) {
        std::cout << "NO SOLUTION\n";
        return 0;
    }
    std::string res(n, ' ');
    int pos = 0;
    for (int letter = 0; letter < 26; ++letter) {
        while (count[letter] > 1) {
            res[pos] = res[n - 1 - pos] = 'A' + letter;
            count[letter] -= 2;
            ++pos;
        }
        if (count[letter] == 1) {
            res[n / 2] = 'A' + letter;
        }
    }
    std::cout << res << '\n';
}

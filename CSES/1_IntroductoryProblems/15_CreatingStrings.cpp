/*

CSES: Introductory Problems: Creating Strings

You are given a string s of length n. Find all possible strings that can be
created using the characters of s. Print the number of strings that can be
created, and then the strings themselves in alphabetical order.

Constraints:
    1 <= n <= 8

Example Input:
aabac

Example Output:
20
aaabc
aaacb
aabac
aabca
aacab
aacba
abaac
abaca
abcaa
acaab
acaba
acbaa
baaac
baaca
bacaa
bcaaa
caaab
caaba
cabaa
cbaaa

This problem can easily be solved with the c++ algorithm next_permutation.
Sort the string's characters and then call next_permutation until no more
lexicographically greater permutations exist.

This problem can also be solved with recursive backtracking. We can recursively
generate all n factorial strings from the characters of s (which is possible
since n <= 8) and them add them to a set. Using a set data structure will
remove duplicates and sort the strings in alphabetical order. Then we just
print all the strings in the set.

*/

#include <iostream>
#include <string>
#include <algorithm>
#include <list>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string str;
    std::cin >> str;
    std::sort(str.begin(), str.end());
    std::list<std::string> strs;
    do {
        strs.push_back(str);
    }
    while (std::next_permutation(str.begin(), str.end()));
    std::cout << strs.size() << '\n';
    for (std::string& s : strs) {
        std::cout << s << '\n';
    }
}

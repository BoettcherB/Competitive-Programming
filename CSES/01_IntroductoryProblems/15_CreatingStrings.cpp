/*

You are given a string s of length n. Find all possible strings that can be
created using the characters of s. Print the number of strings that can be
created, and then the strings themselves in alphabetical order.

Constraints:
 - 1 <= n <= 8

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

This problem can be solved using recursive backtracking. We can recursively
generate all n! (n factorial) strings from the characters of s (which is
possible since n <= 8) and them add them to a set. Using a set data structure
will remove duplicates and sort the strings in alphabetical order. Then we just
print all the strings in the set.

*/

#include <iostream>
#include <string>
#include <set>

std::set<std::string> strings;
std::string res_str, chars_str;
int n;

void generate_strs(int index) {
    if (index == n) {
        strings.insert(res_str);
        return;
    }
    for (int i = 0; i < n; ++i) {
        char c = chars_str[i];
        if (c == 0)
            continue;
        res_str[index] = c;
        chars_str[i] = 0;
        generate_strs(index + 1);
        chars_str[i] = c;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> chars_str;
    n = (int) chars_str.length();
    res_str = std::string(n, 0);
    generate_strs(0);
    std::cout << strings.size() << '\n';
    for (const std::string& s : strings) {
        std::cout << s << '\n';
    }
}

/*

Problem Statement: http://usaco.org/index.php?page=viewproblem2&cpid=1253

This problem can be solved with a greedy method. I will call each sequence of n
bits a 'Test'. Once we find a bit b that can be used in an if or if else
statement, we can remove all Tests that are 'solved' by that if statement. A
bit b can be used in an if statement if, for all remaining Tests t with index
i, any of the following are true:
 - if t[b] == 1 then answer[i] == 1
 - if t[b] == 1 then answer[i] == 0
 - if t[b] == 0 then answer[i] == 1
 - if t[b] == 0 then answer[i] == 0
Once we find one, we can remove all the Tests that are satisfied by the if
statement and mark bit b as done. For example, if answer[i] == 1 for all Tests
t where t[b] == 1, then we can remove all Tests where t[b] == 1, and we can
mark bit b as done. This method is greedy because it does not matter in which 
order we remove tests and mark bits as done. As long as the bits satisfy any of
the conditions above, they can be marked done in any order. If all tests are
removed, or if answer[i] is the same for all remaining tests, we are done and
can print "OK". If we cannot find a bit that satisfies any of the conditions
above, we can print "LIE".

*/

#include <iostream>
#include <string>
#include <algorithm>

const int N = 110;
std::string tests[N], ans(N, '\0');
bool bit_done[N];
int n, m, T;

bool check(int bi, char b, char a) {
    bool seen = false;
    for (int ti = 0; ti < m; ++ti) {
        if (!tests[ti].empty() && tests[ti][bi] == b) {
            if (ans[ti] != a)
                return false;
            seen = true;
        }
    }
    if (seen)
        for (int ti = 0; ti < m; ++ti)
            if (!tests[ti].empty() && tests[ti][bi] == b)
                tests[ti] = "";
    return seen;
}

bool all_equal(char c) {
    for (int ti = 0; ti < m; ++ti)
        if (!tests[ti].empty() && ans[ti] != c)
            return false;
    return true;
}

bool solve() {
    while (true) {
        bool good_check = false;
        for (int i = 0; i < n; ++i) {
            if (bit_done[i])
                continue;
            if (check(i, '1', '1') || check(i, '1', '0')
            || check(i, '0', '1') || check(i, '0', '0')) {
                bit_done[i] = good_check = true;
                break;
            }
        }
        if (!good_check)
            return false;
        if (all_equal('0') || all_equal('1'))
            return true;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> T;
    while (T--) {
        std::cin >> n >> m;
        for (int i = 0; i < m; ++i) {
            std::cin >> tests[i] >> ans[i];
        }
        std::fill(bit_done, bit_done + n, false);
        std::cout << (solve() ? "OK" : "LIE") << '\n';
    }
}

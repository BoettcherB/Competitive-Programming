/*

Problem Statement: http://usaco.org/index.php?page=viewproblem2&cpid=1278

We can treat the needed replacements as a directed graph. For example, changing
the string ABC into DCB can be visualized as a graph with edges A->D, B->C, and
C->B.

Every unique character in the first string will require 1 keystroke. Every loop
(ex: A->B->A) will require an extra keystroke to open the loop (ex: A->C, B->A,
C->B). However, if there is a loop with another path coming into it (example:
...e->A->B->A), then this loop does not require an extra keystroke (we can do
B->E, A->B, E->A).

The transformation of the first string to the second string is impossible if
any character in the first string maps to multiple characters in the second
string. It is also impossible if all 52 characters are used in the first string
and the created graph is made up only of loops (without any paths coming into
them). If the entire graph is just loops and all characters are used, there 
won't be any characters to use as a temporary to open the loop.

*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

const int N = 60;
std::string str, goal;

int solve() {
    int to[N] = {}, in[N] = {};
    for (int i = 0; i < (int) str.length(); ++i) {
        int si = 1 + (str[i] >= 'a' ? str[i] - 'a' : str[i] - 'A' + 26);
        int gi = 1 + (goal[i] >= 'a' ? goal[i] - 'a' : goal[i] - 'A' + 26);
        if (to[si] != 0 && to[si] != gi)
            return -1;
        if (to[si] == 0) {
            to[si] = gi;
            ++in[gi];
        }
    }
    int res = 0;
    int status[N] = {}; // 0 = not seen, 1 = seen in current path, 2 = seen
    bool all_used = true;
    for (int i = 1; i <= 52; ++i) {
        if (to[i] == 0) {
            status[i] = 2;
            all_used = false;
        } else if (to[i] == i) {
            status[i] = 2;
        } else {
            ++res;
        }
    }
    if (res == 0)
        return 0;
    for (int i = 1; i <= 52; ++i) {
        if (status[i] == 2)
            continue;
        std::vector<int> path;
        int cur = i;
        while (status[cur] == 0) {
            path.push_back(cur);
            status[cur] = 1;
            cur = to[cur];
        }
        if (status[cur] == 2)
            all_used = false;
        else {
            // there was a loop. check for another path coming into the loop
            bool other_in = false;
            auto start = std::find(path.begin(), path.end(), cur);
            while (start != path.end()) {
                if (in[*start] > 1) {
                    other_in = true;
                    all_used = false;
                    break;
                }
                ++start;
            }
            res += !other_in; // if no other path, add 1 to res
        }
        for (int letter : path) {
            status[letter] = 2;
        }
    }
    return all_used ? -1 : res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int T;
    std::cin >> T;
    while (T--) {
        std::cin >> str >> goal;
        std::cout << solve() << '\n';
    }
}

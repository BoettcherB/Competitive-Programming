/*

Problem Statement: https://usaco.org/index.php?page=viewproblem2&cpid=1399

First of all, compress the strings down into a sequence of single 1's and 2's
so they are easier to work with. For example: f = 111222212221 would become fv
= {1, 2, 1, 2, 1}. (Do the same for s: compress it into sv). Now, the key is to
"assign" a color to a test tube at the start. If the first characters in fv and
sv are different, then that is the assignment. (for example, if fv starts with
1 and sv starts with 2, then the optimal sequence of moves will result in the
first test tube filled with color 1 and the second test tube filled with color
2. Similarly, if fv[0] = 2 and sv[0] = 1, then the optimal sequence of moves
results in test tube 1 filled with color 2 and test tube 2 filled with color 1.
If the first colors are the same, then we can "assign" a color by inserting
the missing color into the start of one of the test tubes. For example, if
fv[0] = sv[0] = 1, then we can insert 2 at the beginning of fv. This will not
affect the final sequence of moves because we would have to fully empty all the
"real" colors in one of the tubes anyway in order to fill it with the other
color.

Now that the test tubes have different starting colors, the algorithm is this:
    1. Choose the test tube with the highest number of different colors (ex:
        {1, 2, 1} has 3 colors while {2, 1, 2, 1, 2} has 5).
    2. Empty the last color c into either the other test tube (if the final color
        of the other test tube is c) or the beaker.
    3. Do this until the chosen test tube has less colors than the other test
        tube (or until it has only 1 color remaining).
    4. Repeat steps 2-3 on the other test tube. Continue switching test tubes
        and applying these steps until both test tubes have 1 color.
    5. Finally, if the beaker isn't empty, empty it into the correct test tube.

*/

#include <iostream>
#include <vector>
#include <string>

std::vector<std::pair<int, int>> solve(int n, std::string s1, std::string s2) {
    std::vector<int> t1 = { s1[0] - '0' }, t2{ s2[0] - '0' };
    for (int i = 1; i < n; ++i) {
        if (s1[i] != s1[i - 1]) t1.push_back(s1[i] - '0');
        if (s2[i] != s2[i - 1]) t2.push_back(s2[i] - '0');
    }
    if (t1[0] == t2[0])
        t1.insert(t1.begin(), { t2[0] ^ 3 });
    std::vector<int> t3; // beaker
    std::vector<std::pair<int, int>> moves;
    bool t1turn = t1.size() > t2.size();
    while (t1.size() > 1 || t2.size() > 1) {
        int e1 = t1[t1.size() - 1];
        int e2 = t2[t2.size() - 1];
        if (t1turn) {
            if (e1 == e2)
                moves.emplace_back(1, 2);
            else {
                moves.emplace_back(1, 3);
                t3.push_back(e1);
            }
            t1.erase(--t1.end());
            if (t1.size() < t2.size())
                t1turn = false;
        }
        else {
            if (e1 == e2)
                moves.emplace_back(2, 1);
            else {
                moves.emplace_back(2, 3);
                t3.push_back(e2);
            }
            t2.erase(--t2.end());
            if (t2.size() < t1.size())
                t1turn = true;
        }
    }
    if (!t3.empty())
        moves.emplace_back(3, t3[0] == t1[0] ? 1 : 2);
    return moves;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        int n, p;
        std::string s1, s2;
        std::cin >> n >> p >> s1 >> s2;
        std::vector<std::pair<int, int>> moves = solve(n, s1, s2);
        std::cout << moves.size() << '\n';
        if (p != 1) {
            for (const auto& move : moves) {
                std::cout << move.first << ' ' << move.second << '\n';
            }
        }
    }
}

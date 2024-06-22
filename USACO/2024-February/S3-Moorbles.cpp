/*

Problem Statement: https://usaco.org/index.php?page=viewproblem2&cpid=1400

We can start by determining if it is possible to survive for m turns. For each
turn, calculate the number of marbles we will gain or lose for each choice
(even or odd) and take the max of these. Let marbles[i] be the number of
marbles Elsie has on turn i. marbles[0] = n. marbles[i] = marbles[i - 1] + the
number of marbles gained/lost on turn i. If marbles[i] is ever <= 0, even when
playing optimally (not worrying about the lexicographically min sequence), then
it is impossible to survive.

If it is possible to survive, then we need to minimize the sequence of moves.
We do this by trying to change some of our choices from 'odd' to 'even'. Since
we want the lexicographically smallest sequence, we should try changing the
earlier choices (when i is smaller) first. Let seq[i] be the choice made on
turn i (0 = even, 1 = odd). If seq[i] == 1, then we need to determine if we can
choose even on this turn and still survive. Let diff[i] be the difference in
coins we would get if we made the other choice on turn i. For example, if the
k values are { 1 3 5 } for turn i, then we would choose odd (seq[i] == 1) and
we would gain 1 marble on this turn (Bessie would choose the smallest loss for
herself). However, if we instead decided to choose even, then Bessie would
choose 5 (the maximum loss for us). Therefore, diff[i] = abs(1 - -5) = 6. Since
we are losing 6 marbles on this turn by choosing even instead of odd, all
values of marbles[j] for j >= i will be decreased by 6. We can change our
choice to even on turn i and still survive if all marbles[j] for j >= i are >
6. We can determine this by keeping an array min[i] which stores the minimum
value of marbles[j] for all j >= i. (Like a reverse prefix sum, but storing
the min value instead of the sum of values). If we can survive with the change,
then make it. Store the change in marbles in a variable 'added' so that for
subsequent turns, compare min[i] to diff[i] + added.

*/

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int tc;
    std::cin >> tc;
    while (tc--) {
        int n, m, k;
        std::cin >> n >> m >> k;
        std::vector<int> marbles(m + 1), seq(m + 1);
        std::vector<std::pair<int, int>> diff(m + 1);
        marbles[0] = n;
        for (int i = 1; i <= m; ++i) {
            std::vector<int> even, odd;
            for (int j = 0; j < k; ++j) {
                int val;
                std::cin >> val;
                (val % 2 == 0 ? even : odd).push_back(val);
            }
            std::sort(even.begin(), even.end());
            std::sort(odd.begin(), odd.end());
            diff[i].first = odd.empty() ? even[0] : -odd[odd.size() - 1];
            diff[i].second = even.empty() ? odd[0] : -even[even.size() - 1];
            if (diff[i].first > diff[i].second) {
                marbles[i] = marbles[i - 1] + diff[i].first;
                seq[i] = 0;
            } else {
                marbles[i] = marbles[i - 1] + diff[i].second;
                seq[i] = 1;
            }
        }
        std::vector<int> min(m + 1);
        min[m] = marbles[m];
        for (int i = m - 1; i > 0; --i) {
            min[i] = std::min(min[i + 1], marbles[i]);
        }
        if (min[1] <= 0) {
            std::cout << -1 << '\n';
            continue;
        }
        int added = 0;
        for (int i = 1; i <= m; ++i) {
            if (seq[i] == 1) {
                int d = std::abs(diff[i].first - diff[i].second);
                if (added + d < min[i]) {
                    seq[i] = 0;
                    added += d;
                }
            }
            std::cout << (seq[i] == 0 ? "Even" : "Odd") << " \n"[i == m];
        }
    }
}

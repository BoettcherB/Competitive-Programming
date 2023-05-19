/*

Problem Statement: http://usaco.org/index.php?page=viewproblem2&cpid=1280

Since the sum of a[i] for all 0 <= i <= n is at most 10^6, we can simulate the
entire path that Bessie takes. We can use a greedy algorithm for this. Bessie
will start off moving right until the very end of the array (position n).
Whenever Bessie reaches position i, subtract 1 from a[i]. Next, she will move
left until either she reaches position 0 or she is about to cross a position
where a[i] is 1. If she crosses this position, she cannot get back, so she
needs to turn around here if there are still positions she needs to visit to
her right. She will continue moving back and forth until she reaches position
0 and no other positions need to be visited.

*/

#include <iostream>
#include <string>

const int N = 1e5 + 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, arr[N];
    std::cin >> n;
    bool have_right[N] = {};
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
        have_right[i] = true;
    }
    std::string moves;
    bool moving_right = true;
    int pos = 0;
    while (have_right[0]) {
        if (moving_right) {
            if (!have_right[pos])
                moving_right = false;
            else {
                moves.push_back('R');
                --arr[pos++];
            }
        }
        else if (pos == 0 || (arr[pos - 1] == 1 && have_right[pos]))
            moving_right = true;
        else {
            moves.push_back('L');
            if (--arr[--pos] == 0)
                have_right[pos] = false;
        }
    }
    std::cout << moves << '\n';
}

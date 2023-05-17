/*

Problem Statement: http://usaco.org/index.php?page=viewproblem2&cpid=1255

After examining small values of a_i, we can see that Farmer John will win if
a_i is not a multiple of 4. If a_i is a multiple of 4, it doesn't matter which
prime number you take away, the other player can always get a_i back to a
multiple of 4 (or 0, in which case they win on the next turn).

One important realization is that the losing player (the one where a_i is a
multiple of 4 on their turn) wants to make the game take as many turns as
possible, while the winning player wants to make the game take as few turns as
possible. The best strategy for the losing player is to take away 2 cows. This
will force the other player to also take away 2 cows (because this is the only
way to get a_i back to a multiple of 4). The best strategy for the winning
player is to take away the highest prime number p such that a_i - p is a
multiple of 4. However, they can really only do this on their first turn, since
on all other turns they will have to take away 2 cows to counteract the losing
player's strategy.

We will define 2 arrays: prime[N] (which we can create with a Sieve of
Eratosthenes) and best_take_away[N]. best_take_away[i] is the most optimal
number of cows that a player can take away if they come to a barn with i cows.
If i is even, best_take_away[i] is 2. Otherwise, best_take_away[i] is the max
prime number p where p % 4 == i % 4. This ensures that p is the max prime
number such that, after taking away p cows, the number of cows in the barn is a
multiple of 4. We use best_take_away to determine how many turns it will take
for the winning player to win the game. The winning player for the barn with
the smallest number of turns will win the game.

*/

#include <iostream>
#include <algorithm>

const long long INF = 1e18;
const int N = 5e6 + 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    bool prime[N];
    std::fill_n(prime, N, true);
    for (long long i = 2; i < N; ++i) {
        if (!prime[i])
            continue;
        for (long long j = i * i; j < N; j += i) {
            prime[j] = false;
        }
    }
    int best_take_away[N];
    int best1 = 1, best3 = 3;
    for (int i = 1; i < N; ++i) {
        if (prime[i]) {
            if (i % 4 == 1) best1 = i;
            if (i % 4 == 3) best3 = i;
        }
        switch (i % 4) {
            case 0:
            case 2: best_take_away[i] = 2; break;
            case 1: best_take_away[i] = best1; break;
            case 3: best_take_away[i] = best3; break;
        }
    }
    long long T;
    std::cin >> T;
    while (T--) {
        long long n, min_turns = INF, winner = -1;
        std::cin >> n;
        for (int i = 0; i < n; ++i) {
            long long a, cur_winner, turns;
            std::cin >> a;
            cur_winner = a % 4 == 0;
            a -= best_take_away[a];
            if (a == 0) {
                turns = 0;
            } else {
                a -= best_take_away[a];
                turns = 1 + a / 4;
            }
            if (turns < min_turns) {
                winner = cur_winner;
                min_turns = turns;
            }
        }
        std::cout << "Farmer ";
        std::cout << (winner ? "Nhoj" : "John") << '\n';
    }
}

/*

You are given an integer n. For all 1 <= k <= n, find the number of possible
ways that 2 knights can be placed on a kxk chessboard so that they cannot
attack each other.

Constraints:
    1 <= n <= 10,000
 
Example Input:
8

Example Output:
0
6
28
96
252
550
1056
1848

When moving from k-1 to k, all we are doing is adding 1 more row and 1 more
column to the board (for a total of 2k-1 added squares). All of the legal moves
from the previous k-1 x k-1 grid are still legal here. Now we just have to
factor in the moves where one or both knights are placed on an added square.

First, lets handle the case where both knights are on new squares. There are
x = 2k-1 new squares. If we place a knight on square 1 there are x-1 spaces for
the second knight. Next, if we place a knight on square 2 there are x-2 spaces
for the second knight... In total, the answer is the sum of the first x-1
integers, which is x*(x-1)/2. However, there are 2 cases near the middle corner
where the knights can attack each other, so the actual result is x*(x-1)/2-2.

Next, let's look at cases where only 1 knight is on a new square. We can find
how many combinations there are for placing a knight on any new square by
looking at how many old squares the knight is attacking. Adding a knight to a
new square will add (num_old_squares - num_old_squares_attacked) combinations.
The number of old squares is constant ((k-1)*(k-1)) so we just have to look at
each new square and determine how many old squares it is attacking.
1)  There are 5 new squares where the knight can only attack 2 old squares: One
    at each of the 3 corners and one at each of the 2 squares adjacent to the
    middle corner. In total this adds 5*(num_old_squares - 2) combinations.
2)  There are 4 new squares where the knight can only attack 3 old squares: the
    second square from the edge on both sides, and the 2 squares adjacent to
    the 2 squares that were adjacent to the middle corner. In total this adds
    4*(num_old_squares - 3) combinations.
3)  Lastly, all remaining new squares can attack 4 old squares. There are
    2(k-5) remaining new squares for a total of 2(k-5)(num_old_squares - 4)
    combinations.

Add up all these results, along with the previous result for the k-1xk-1 grid,
to find the result for the current kxk grid. Even though it is not intuitive,
this still works for the cases where k is small (2 <= k <= 5).

*/

#include <iostream>

const int N = 10010;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    long long res[N] = { 0, 0 };
    for (int k = 2; k < N; ++k) {
        res[k] = res[k - 1];
        long long x = 2 * k - 1;
        res[k] += x * (x - 1) / 2 - 2;
        long long oldSquares = (k - 1) * (k - 1);
        res[k] += (oldSquares - 2) * 5;
        res[k] += (oldSquares - 3) * 4;
        res[k] += (oldSquares - 4) * (k - 5) * 2;
    }
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cout << res[i] << '\n';
    }
}

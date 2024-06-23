/*

There are n people who want to get to the top of a building that only has one
elevator. Each person has a weight w_i, and the maximum weight capacity of the
elevator is x. What is the minimum number of elevator rides needed?

Constraints:
    1 <= n <= 20
    1 <= x <= 1,000,000,000
    1 <= w_i <= x

Example Input:
4 10
4 8 6 1

Example Output:
2

The greedy method (which doesn't work) is to sequentially place people in the
current elevator until the elevator is full (the next person can't fit). Once
the elevator is full, move on the next elevator and continue the process. While
this method doesn't normally work, it will work for an optimal ordering of
weights. For example, if x = 10, the weights {2,5,6,5,8,4} would result in 5
elevators if we use the greedy method: {|2,5|6|5|8|4|}. However, if we change
the order of elements, we can reduce it to 3 elevators: {|2,8|5,5|6,4|}. Trying
all possible orderings is too slow, O(n*n!), so we need a better approach.

Note that there are multiple orderings that are optimal. The order of
elements within an elevator does not matter ({|2,8|5,5|6,4|} is the same as
{|8,2|5,5|4,6|}), and the order of elevators does not matter ({|2,8|5,5|6,4|}
is the same as {|5,5|6,4|2,8|}). Therefore, we can try to fix the placement of
some elements and find the best ordering for the remaining subset of elements.
If we fix the final element, the optimal ordering for the first n - 1 elements
is an ordering the minimizes the number of elevators required while maximizing
the space remaining in the final elevator. For a set of n elements, we will try
fixing the final element and finding the optimal ordering of all subsets with
n - 1 elements. For each set of n-1 elements, we will try fixing the placement
of the final element and finding the optimal ordering of all subsets with n - 2
elements. This approach iterates through all subsets with n elements, O(n*2^n),
which is fast enough for n = 20.

Remember that an optimal order of elements involves both minimizing the number
of elevators and maximizing the remaining space in the final elevator. Let
dp[i] be the minimum number of elevators needed for the set i (if the j'th bit
in i is 1 then the j'th person is included in set i), and let rem[i] be the
space remaining in the final elevator when placing the people in set i. When
finding dp[i], try sequentially fixing the final person in the ordering to one
of the people p in set i. The remaining subset of people (j = i - p) will have
their own optimal ordering, which is defined by dp[j] and rem[j]. When adding
p to j, p will either fit in the final elevator or require a new elevator. If
weight[p] + rem[j] <= x, then dp[i] = dp[j] and rem[i] = rem[j] + weight[p].
However, if weight[p] + rem[j] > x, then p will require a new elevator: dp[i]
= dp[j] + 1 and rem[i] = weight[p]. Do this for all p in i while minimizing
dp[i] and maximizing rem[i].

*/

#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, x;
    std::cin >> n >> x;
    std::vector<int> weights(n);
    std::vector<int> dp(1 << n, 2e9), rem(1 << n, x);
    for (int i = 0; i < n; ++i) {
        std::cin >> weights[i];
    }
    dp[0] = 1;
    for (int i = 1; i < (1 << n); ++i) {
        for (int p = 0; p < n; ++p) {
            if ((i & (1 << p)) == 0)
                continue;
            int subset = i & ~(1 << p);
            int rides = dp[subset];
            int curRem = rem[subset] - weights[p];
            if (curRem < 0) {
                ++rides;
                curRem = x - weights[p];
            }
            if (rides < dp[i] || (rides == dp[i] && curRem > rem[i])) {
                dp[i] = rides;
                rem[i] = curRem;
            }
        }
    }
    std::cout << dp[(1 << n) - 1] << '\n';
}

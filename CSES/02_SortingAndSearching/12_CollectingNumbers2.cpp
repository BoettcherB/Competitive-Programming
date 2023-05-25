/*

You are given an array of n integers that contains each number between 1..n
exactly once. Your task is to collect the numbers from 1 to n in increasing
order. On each round, you go through the array from left to right and collect
as many numbers as possible. Given m operations that swap two numbers in the
array, report the number of rounds after each operation.

Constraints:
 - 1 <= n, m <= 200,000
 - 1 <= a, b <= n

Example Input:
5 3
4 2 1 5 3
2 3
1 5
2 3

Example Output:
2
3
4

Use the same method in the previous problem to find the initial number of
passes needed. Then, each query gives us two indices (i, j) of two numbers
(num[i] and num[j]) to swap. Since we are only swapping 2 numbers, we do not
have to go through the entire array again to determine the new result (number
of passes needed) after the swap. For each query, we only need to check the
numbers around num[i] and num[j]. Count the number of passes needed to collect
the numbers around num[i] and num[j] before the swap, then do the same count
after the swap. The change in this count is the change in the result after the
swap.

*/

#include <iostream>
#include <set>

const int N = 2e5 + 10;
int n, q, num[N], pos[N];
std::set<int> s;

int count() {
    int cnt = 0, prev = 0;
    for (int x : s) {
        if (prev != 0)
            cnt += pos[prev] > pos[x];
        prev = x;
    }
    return cnt;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        std::cin >> num[i];
        pos[num[i]] = i;
    }
    int res = 1;
    for (int i = 1; i < n; ++i) {
        res += pos[i] > pos[i + 1];
    }
    pos[0] = pos[n + 1] = 2e9;
    while (q--) {
        int i, j;
        std::cin >> i >> j;
        s.clear();
        s.insert({num[i] - 1, num[i], num[i] + 1});
        s.insert({num[j] - 1, num[j], num[j] + 1});
        int before = count();
        std::swap(pos[num[i]], pos[num[j]]);
        std::swap(num[i], num[j]);
        res += count() - before;
        std::cout << res << '\n';
    }
}

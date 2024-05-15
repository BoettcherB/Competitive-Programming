/*

You are given an array of n integers that contains each number between 1..n
exactly once. Your task is to collect the numbers from 1 to n in increasing
order. On each round, you go through the array from left to right and collect
as many numbers as possible. Given m operations that swap two numbers in the
array, report the number of rounds after each operation.

Constraints:
    1 <= n, m <= 200,000
    1 <= a, b <= n

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
int arr[N], index[N];
std::set<int> s;

int count() {
    int res = 0, prev = 0;
    for (int x : s) {
        if (prev != 0) {
            res += index[prev] > index[x];
        }
        prev = x;
    }
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        std::cin >> arr[i];
        index[arr[i]] = i;
    }
    int rounds = 1;
    for (int i = 2; i <= n; ++i) {
        rounds += index[i - 1] > index[i];
    }
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        s.clear();
        s.insert({arr[a] - 1, arr[a], arr[a] + 1});
        s.insert({arr[b] - 1, arr[b], arr[b] + 1});
        int before = count();
        std::swap(index[arr[a]], index[arr[b]]);
        std::swap(arr[a], arr[b]);
        rounds += count() - before;
        std::cout << rounds << '\n';
    }
}

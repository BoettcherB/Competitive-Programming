/*

You are given an array that contains each number from 1 to n exactly once. Your
task is to collect each number in increasing order. On each round, you go
through the array from left to right and collect as many numbers as possible.
What is the fewest number of rounds needed?

Constraints:
 - 1 <= n <= 200,000

Example Input:
5
4 2 1 5 3

Example Output:
3

For each number, store the index that it appears in the array. A new round is
needed if the index of i is greater than the index of i+1.

*/

#include <iostream>
 
const int N = 2e5 + 10;
 
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
 
    int n, arr[N];
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        arr[a - 1] = i;
    }
    int res = 1;
    for (int i = 1; i < n; ++i) {
        res += arr[i - 1] > arr[i];
    }
    std::cout << res << '\n';
}
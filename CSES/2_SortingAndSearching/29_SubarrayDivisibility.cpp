/*

You are given an array of n integers [a0, a1, ..., an]. Your task is to count
the number of subarrays where the sum of values is divisible by n.

Constraints
    1 <= n <= 200,000
    -1,000,000,000 <= a <= 1,000,000,000

Example Input:
5
3 1 2 7 4

Example Output:
1

The solution here is similar to the previous problem (Subarray Sums II) but
instead of storing prefix sums in the map we are storing prefix sums mod n. We
start at i = 0 and check the map for any prefix sums where the sum mod n is 0.
Next we move to i = 1 and check the map for any prefix sums where the sum mod n
is equal to prefix[i - 1] % n (if the subarray [1, j] has sum % n = 0, then
((prefix[j] % n) - (prefix[1] % n) = 0). Do this for all i and remember to
remove prefix[i] from the map as you go.

It is important to note that (prefix[i] % n) could be negative if prefix[i] is
negative. Therefore, if prefix[i] is positive we have to check both (prefix[i]
% n) and (prefix[i] % n - n), and if prefix[i] is negative we have to check
(prefix[i] % n) and (prefix[i] % n + n). An easier way to do it (and how it is
done in the solution below) is to convert all negative mod values to positive
so we only have to check positive values.

*/

#include <iostream>
#include <map>
 
const int N = 2e5 + 10;
int n;
 
long long modN(long long x) {
    return (x % n + n) % n;
}
 
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
 
    std::cin >> n;
    long long prefix[N] = { 0 };
    std::map<long long, long long> map;
    for (int i = 1; i <= n; ++i) {
        int a;
        std::cin >> a;
        prefix[i] = prefix[i - 1] + a;
        ++map[modN(prefix[i])];
    }
    long long res = 0, change = 0;
    for (int i = 1; i <= n; ++i) {
        res += map[modN(prefix[i - 1])];
        --map[modN(prefix[i])];
    }
    std::cout << res << '\n';
}

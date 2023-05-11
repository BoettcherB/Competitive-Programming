/*

Problem Statement: http://usaco.org/index.php?page=viewproblem2&cpid=1251

Cow i is willing to pay a tuition of c_i. If we sort the cows in increasing
order (of c), all cows to the right of cow i will also be willing to pay a
tuition of c_i. It is also important to realize that we do not have to check
all values of c. We only have to check the values of c that cows are willing
to pay. In the given example we do not have to check when c = 5, because the
number of cows willing to pay when c = 5 vs when c = 6 is the same, and we make
more money when c = 6. Therefore, we can loop through the sorted list and for
each cow calculate the amount it is willing to pay (c_i) times the number of
cows willing to pay that amount (n - i). Print the max of these values.

Watch out for integer overflow. N * C can be as high as 1e11, which will
overflow a 32-bit integer.

*/

#include <iostream>
#include <algorithm>

const int N = 1e5 + 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    long long arr[N];
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    std::sort(arr, arr + n);
    long long max = 0, price = 0;
    for (int i = 0; i < n; ++i) {
        long long x = arr[i] * (n - i);
        if (x > max) {
            max = x;
            price = arr[i];
        }
    }
    std::cout << max << ' ' << price << '\n';
}

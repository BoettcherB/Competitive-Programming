/*

Problem Statement: https://usaco.org/index.php?page=viewproblem2&cpid=1251

In this problem, it does not make sense to set the tuiton to a value that no
cow is willing to pay (ie. if there are 3 cows willing to pay tuitions of 1, 4,
and 6, we do not need to check any other values besides 1, 4, and 6). If the
tuition is set to a value that no cow is willing to pay, we can raise it to the
next highest value that a cow is willing to pay (thus making more profit) while
still having the same number of cows attend the university.

We can find the number of cows willing to pay a certain tuition by sorting
the values of c_i. For each value of c_i, the number of cows willing to pay
that tuition is n - i, and profit received is (n - i) * c_i.

*/

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<long long> cow(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> cow[i];
    }
    std::sort(cow.begin(), cow.end());
    long long maxProfit = 0, tuition = 0;
    for (int i = 0; i < n; ++i) {
        if (cow[i] * (n - i) > maxProfit) {
            maxProfit = cow[i] * (n - i);
            tuition = cow[i];
        }
    }
    std::cout << maxProfit << ' ' << tuition << '\n';
}

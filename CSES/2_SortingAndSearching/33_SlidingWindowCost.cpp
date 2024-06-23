/*

CSES: Sorting and Searching: Sliding Window Cost

You are given an array of n integers [a0, a1, ..., an] and an integer k. Your
task is to calculate, for each window of k elements, the cost of making all
elements equal. The cost to convert an integer a into an integer b is |a-b|.
Print n-k+1 values: the costs.

Constraints:
    1 <= k <= n <= 200,000
    1 <= a <= 1,000,000,000

Example Input:
8 3
2 4 3 5 8 1 2 1

Example Output:
2 2 5 7 7 1

This problem is very similar to the previous problem (Sliding Window Median).
Just like in that problem we use 2 sets for each window, one for the lower k/2
values and one for the higher k/2 values. However, instead of just printing the
median we need to calculate the cost of converting each number to the median.
To do this, we need to keep track of the sum of values in each set. If the
median is x, then the cost to convert all values in the 'low' set to the median
is (num elements in low set) * x - (sum of low elements). For the 'high' set,
the cost is (sum of high elements) - (num elements in high set) * x. Calculate
this value for each window.

*/

#include <iostream>
#include <set>

const int N = 2e5 + 10;
int n, k, arr[N];
std::multiset<int> low, high;
long long lowSum, highSum;

void insert(int x) {
    high.insert(x);
    highSum += x;
    if ((int) high.size() > k / 2) {
        auto b = high.begin();
        low.insert(*b);
        lowSum += *b;
        highSum -= *b;
        high.erase(b);
    }
}

void remove(int x) {
    if (high.size() > 0 && *high.begin() <= x) {
        highSum -= x;
        high.erase(high.find(x));
        auto e = --low.end();
        highSum += *e;
        high.insert(*e);
        lowSum -= *e;
        low.erase(e);
    } else {
        lowSum -= x;
        low.erase(low.find(x));
    }
}

long long cost() {
    if (k == 1)
        return 0;
    long long med = *(--low.end());
    return low.size() * med - lowSum + highSum - high.size() * med;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
        if (i < k)
            insert(arr[i]);
    }
    std::cout << cost();

    for (int i = 0; i < n - k; ++i) {
        remove(arr[i]);
        insert(arr[i + k]);
        std::cout << ' ' << cost();
    }
    std::cout << '\n';
}

/*

There are n tickets, each with a price p. There are also m customers. Customers
arrive in order and specify the maximum amount h that they are willing to pay
for a ticket. If a ticket exists with price p < h, that customer will purchase
that ticket (if there are multiple tickets with p < h, they will purchase the
one where p is closest to h). Tickets cannot be purchased multiple times. For
each customer, determine the price they will pay for a ticket. If a customer is
not willing to buy a ticket, print -1.

Constraints:
    1 <= n, m <= 200,000
    1 <= p, h <= 1,000,000,000

Example Input:
5 3
5 3 7 8 5
4 8 3

Example Output:
3
8
-1

We can use a multiset to sort the ticket prices, perform binary search to find
the best ticket, and remove tickets from the list in O(logn) time.

*/

#include <iostream>
#include <set>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::multiset<int> s;
    for (int i = 0; i < n; ++i) {
        int t;
        std::cin >> t;
        s.insert(t);
    }
    for (int i = 0; i < m; ++i) {
        int p;
        std::cin >> p;
        auto itr = s.upper_bound(p);
        if (itr == s.begin()) {
            std::cout << -1 << '\n';
        } else {
            std::cout << *(--itr) << '\n';
            s.erase(itr);
        }
    }
}

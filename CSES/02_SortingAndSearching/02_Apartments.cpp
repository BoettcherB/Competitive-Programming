/*

There are n applicants and m free apartments. Each applicant has a desired
apartment size a, and each apartment has a size b. If b is within k units of a,
the applicant will accept the apartment. You need to distribute the apartments
so that as many applicants as possible get an apartment.

Constraints:
 - 1 <= n, m <= 200,000
 - 0 <= k <= 1,000,000,000
 - 1 <= a, b <= 1,000,000,000

Example Input:
4 3 5
60 45 80 60
30 60 75

Example Output:
2

This can be solved with a greedy 2-pointers method. First, sort both the list
of desired apartment sizes and the list of actual apartment sizes. Then
consider the first element in each list. If the actual apartment size is less
than the desired size - k, then this apartment is too small for any applicant
so try the next apartment. If the actual apartment size is greater than the
desired size + k, then there are no apartments for this applicant so move on to
the next applicant. If the desired size and the actual size are within k units,
match them up and then move on to the next apartment and the next applicant.

*/

#include <iostream>
#include <algorithm>

const int N = 2e5 + 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, k, desired[N], actual[N];
    std::cin >> n >> m >> k;
    for (int i = 0; i < n; ++i) {
        std::cin >> desired[i];
    }
    for (int i = 0; i < m; ++i) {
        std::cin >> actual[i];
    }
    std::sort(desired, desired + n);
    std::sort(actual, actual + m);
    int p1 = 0, p2 = 0, res = 0;
    while (p1 < n && p2 < m) {
        if (desired[p1] + k < actual[p2])
            ++p1;
        else if (desired[p1] - k > actual[p2])
            ++p2;
        else {
            ++res;
            ++p1;
            ++p2;
        }
    }
    std::cout << res << '\n';
}

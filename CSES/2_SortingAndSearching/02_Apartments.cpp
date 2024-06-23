/*

CSES: Sorting and Searching: Apartments

There are n applicants and m free apartments. Each applicant has a desired
apartment size a, and each apartment has a size b. If b is within k units of a,
the applicant will accept the apartment. The task is to distribute the
apartments so that as many applicants as possible get an apartment.

Constraints:
    1 <= n, m <= 200,000
    0 <= k <= 1,000,000,000
    1 <= a, b <= 1,000,000,000

Example Input:
4 3 5
60 45 80 60
30 60 75

Example Output:
2

This can be solved with a greedy 2-pointers method. First, sort both the lists
(applicants and aparements). Then consider the first element in each list. If
the smallest applicant's desired apartment size is not within k of the smallest
apartment, then move on the next applicant. If the smallest apartment size is
not within k of the smallest desired size, then move on the next apartment.
If the desired size and the actual size are within k units, match them up and
move on to both the next apartment and the next applicant.

*/

#include <iostream>
#include <algorithm>

const int N = 2e5 + 10;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, k;
    int applicants[N], appartments[N];
    std::cin >> n >> m >> k;
    for (int i = 0; i < n; ++i) {
        std::cin >> applicants[i];
    }
    for (int i = 0; i < m; ++i) {
        std::cin >> appartments[i];
    }
    std::sort(applicants, applicants + n);
    std::sort(appartments, appartments + m);
    int p1 = 0, p2 = 0, res = 0;
    while (p1 < n && p2 < m) {
        if (applicants[p1] + k < appartments[p2])
            ++p1;
        else if (appartments[p2] + k < applicants[p1])
            ++p2;
        else {
            ++p1;
            ++p2;
            ++res;
        }
    }
    std::cout << res << '\n';
}

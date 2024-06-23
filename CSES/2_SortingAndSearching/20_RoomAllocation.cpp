/*

CSES: Sorting and Searching: Room Allocation

There are n customers at a hotel, each who want their own room. You are given
their arrival and departure day (a and b). Your task is to find the minimum
number of rooms required to accommodate every customer, as well as a possible
way to allocate the rooms.

Constraints:
    1 <= n <= 200,000
    1 <= a, b <= 1,000,000,000

Example Input:
3
1 2
2 4
4 4

Example Output:
2
1 2 1

To solve, keep a variable 'R' which stores the minimum number of rooms required
(initially, R = 0), an array 'room' to store which room each customer stays in,
and a set 'free' which contains the rooms that are free (assuming we only have
R rooms). Sort the 2n arrival and departure times, but keep track of whether a
time is an arrival or departure and the index of the customer the time belongs
to. Loop through all the times. If we encounter an arrival time for customer i,
take a free room r from the 'free' set (if there is none, increment R) and set
room[i] = r. If we encounter a departure time for customer i, add room[i] to
the free set.

*/

#include <iostream>
#include <algorithm>
#include <set>

const int N = 2e5 + 10;

struct Time {
    int t, type, index;
    bool operator<(const Time& other) const {
        return t == other.t ? type == 0 : t < other.t;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    Time times[2 * N];
    for (int i = 0; i < n; ++i) {
        int a, b;
        std::cin >> a >> b;
        times[i] = { a, 0, i };
        times[i + n] = { b, 1, i };
    }
    std::sort(times, times + 2 * n);
    int rooms = 0, room[N];
    std::set<int> free;
    for (int i = 0; i < 2 * n; ++i) {
        int ind = times[i].index;
        if (times[i].type == 1)
            free.insert(room[ind]);
        else {
            if (free.empty())
                room[ind] = ++rooms;
            else {
                room[ind] = *free.begin();
                free.erase(free.begin());
            }
        }
    }
    std::cout << rooms << '\n';
    for (int i = 0; i < n; ++i) {
        std::cout << room[i] << ' ';
    } std::cout << '\n';
}

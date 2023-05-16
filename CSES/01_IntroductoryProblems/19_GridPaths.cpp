/*

You have a 7x7 grid. You start at the top left square and want to end at the
bottom left square while visiting all squares only once. A path is described as
a string consisting of 48 moves (represented by L, R, U, and D). You are given
a description of a path but some of the moves are empty (represented by '?').
Determine how many unique paths fit this description.

Example Input:
??????R??????U??????????????????????????LD????D?

Example Output:
201

This problem can be solved with recursive backtracking. If we are on the i'th
move and the i'th character in the path description is filled in, try to make
that move. If the i'th character is not filled in (is '?'), then try to make
all 4 moves. One important optimization is to stop recursion if our path splits
the grid into 2 regions (if this happens, we won't be able to visit all the
squares). We can detect this if the square in front of us has been visited (or
is an edge), but the squares to our left and right have not been visited.
Another optimization is to stop recursion if we reach the end square (7,1)
before all other squares have been visited. We can also create a 9x9 grid
(instead of 7x7) and mark the edges as visited so we don't have to do any
bounds checking.

*/

#include <iostream>
#include <string>

const int N = 9;
bool grid[N][N];
std::string path;

bool valid(int r, int c) {
    if (grid[r][c] == 1)
        return false;
    if (grid[r + 1][c] && grid[r - 1][c] && !grid[r][c + 1] && !grid[r][c - 1])
        return false;
    if (grid[r][c + 1] && grid[r][c - 1] && !grid[r + 1][c] && !grid[r - 1][c])
        return false;
    return true;
}

int rec(int index, int row, int col) {
    if (row == 7 && col == 1)
        return index == 48;
    if (!valid(row, col))
        return 0;
    grid[row][col] = true;
    int res = 0;
    switch (path[index]) {
        case 'L': res = rec(index + 1, row, col - 1); break;
        case 'R': res = rec(index + 1, row, col + 1); break;
        case 'U': res = rec(index + 1, row - 1, col); break;
        case 'D': res = rec(index + 1, row + 1, col); break;
        case '?': 
            res += rec(index + 1, row, col - 1);
            res += rec(index + 1, row, col + 1);
            res += rec(index + 1, row - 1, col);
            res += rec(index + 1, row + 1, col);
    }
    grid[row][col] = false;
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> path;
    for (int i = 0; i <= 8; ++i) {
        grid[0][i] = grid[i][0] = grid[8][i] = grid[i][8] = true;
    }
    std::cout << rec(0, 1, 1) << '\n';
}

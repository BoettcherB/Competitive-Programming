/*

Determine how many ways you can place 8 queens on a chessboard without them
being able to attack each other. Additionally, each square on the board is
either free or blocked. A queen cannot be placed on a blocked square but
they can attack through them.

Example Input:
........
........
..*.....
........
........
.....**.
...*....
........

Example Output:
65

This is a classic recursive backtracking problem. For every row of the board,
try placing a queen in the first square. If that queen is attacked, try the
next square. If the queen is safe, move on to the next row. If we are not able
to place a queen anywhere in a row, move back to a previous row and try a queen
in a different square. The only difference here is that we cannot place a queen
on squares that have an asterisk.

*/

#include <iostream>
#include <string>

int grid[8][8]; // 0 == empty, 1 == *, 2 == queen

bool intersects(int row, int col) {
    for (int i = row - 1; i >= 0; --i) {
        if (grid[i][col] == 2)
            return true;
        int j1 = col - (row - i);
        int j2 = col + (row - i);
        if (j1 >= 0 && grid[i][j1] == 2)
            return true;
        if (j2 < 8 && grid[i][j2] == 2)
            return true;
    }
    return false;
}

int rec(int row) {
    if (row == 8)
        return 1;
    int count = 0;
    for (int col = 0; col < 8; ++col) {
        if (grid[row][col] == 1 || intersects(row, col))
            continue;
        grid[row][col] = 2;
        count += rec(row + 1);
        grid[row][col] = 0;
    }
    return count;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    for (int i = 0; i < 8; ++i) {
        std::string str;
        std::cin >> str;
        for (int j = 0; j < 8; ++j) {
            grid[i][j] = str[j] == '*';
        }
    }
    std::cout << rec(0) << '\n';
}

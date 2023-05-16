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
in a different square.

*/

#include <iostream>

int board[8][8];

bool attacked(int I, int J) {
    for (int i = I - 1; i >= 0; --i) {
        if (board[i][J] == 2) return true;
    }
    for (int i = I - 1; i >= 0; --i) {
        int j = J - (I - i);
        if (j < 0) break;
        if (board[i][j] == 2) return true;
    }
    for (int i = I - 1; i >= 0; --i) {
        int j = J + (I - i);
        if (j >= 8) break;
        if (board[i][j] == 2) return true;
    }
    return false;
}

int rec(int row) {
    if (row == 8)
        return 1;
    int res = 0;
    for (int col = 0; col < 8; ++col) {
        if (board[row][col] == 1)
            continue;
        if (!attacked(row, col)) {
            board[row][col] = 2;
            res += rec(row + 1);
            board[row][col] = 0;
        }
    }
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string row;
    for (int i = 0; i < 8; ++i) {
        std::cin >> row;
        for (int j = 0; j < 8; ++j) {
            board[i][j] = row[j] == '*';
        }
    }
    std::cout << rec(0) << '\n';
}

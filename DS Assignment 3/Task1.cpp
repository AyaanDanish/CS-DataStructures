#include <iostream>
using namespace std;

// Checks if given player has won
bool checkIfWon(int board[3][3], int player) {
    // Checking if we have 3 in a row
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
                if (board[i][0] == player)
                    return true;
        }
    }
    // Checking if we have 3 in a col
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[0][j] == board[1][j] && board[1][j] == board[2][j])
                if (board[0][j] == player)
                    return true;
        }
    }

    // Checking if we have 3 in right diagonal
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        if (board[0][0] == player)
            return true;
    // Checking if we have 3 in left diagonal
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        if (board[0][2] == player)
            return true;

    return false;
}

bool IsWinPossible(int board[3][3], int player) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 0) {
                board[i][j] = player;

                if (checkIfWon(board, player)) {
                    board[i][j] = 0;
                    return true;
                }

                board[i][j] = 0;
            }
        }
    }
    return false;
}

bool checkBoardValid(int board[3][3]) {
    int ones = 0, twos = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 1)
                ones++;
            if (board[i][j] == 2)
                twos++;
        }
    }
    if (ones - twos > 1 || twos - ones > 1)
        return false;
    return true;
}

int main() {
    int board[3][3];
    // Input board
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> board[i][j];
        }
    }

    // Check board validity
    if (checkBoardValid(board) == false) {
        cout << -1;
        return 0;
    }

    // Generate output
    if (IsWinPossible(board, 1) && IsWinPossible(board, 2))
        cout << 2;
    else if (IsWinPossible(board, 1) || IsWinPossible(board, 2))
        cout << 1;
    else
        cout << 0;
}

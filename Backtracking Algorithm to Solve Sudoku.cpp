#include <iostream>
#include <vector>
using namespace std;

// Function to check if placing the number is valid in the given cell
bool isValid(vector<vector<int>>& board, int row, int col, int num) {
    // Check row
    for (int i = 0; i < 9; ++i) {
        if (board[row][i] == num) {
            return false;
        }
    }
    // Check column
    for (int i = 0; i < 9; ++i) {
        if (board[i][col] == num) {
            return false;
        }
    }
    // Check 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }
    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(vector<vector<int>>& board) {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (board[row][col] == 0) {  // Find an empty cell
                for (int num = 1; num <= 9; ++num) {
                    if (isValid(board, row, col, num)) {
                        board[row][col] = num;  // Place the number
                        if (solveSudoku(board)) {
                            return true;  // Continue to solve the rest
                        }
                        board[row][col] = 0;  // Backtrack if no solution found
                    }
                }
                return false;  // No valid number found
            }
        }
    }
    return true;  // Puzzle solved
}

// Function to print the Sudoku board
void printBoard(const vector<vector<int>>& board) {
    for (const auto& row : board) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
}

int main() {
    // Sample Sudoku puzzle (0 represents empty cells)
    vector<vector<int>> board = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    cout << "Original Sudoku puzzle:\n";
    printBoard(board);

    if (solveSudoku(board)) {
        cout << "\nSolved Sudoku puzzle:\n";
        printBoard(board);
    } else {
        cout << "\nNo solution exists.\n";
    }

    return 0;
}


 #include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// Function to display the Sudoku grid
void displayGrid(const vector<vector<int>> &grid) {
    cout << "\n     Sudoku Solver\n";
    cout << "   ---------------------\n";
    for (int i = 0; i < 9; i++) {
        cout << "   | ";
        for (int j = 0; j < 9; j++) {
            if (grid[i][j] == 0)
                cout << ". "; // Empty cell
            else
                cout << grid[i][j] << " ";
            if ((j + 1) % 3 == 0) cout << "| ";
        }
        cout << "\n";
        if ((i + 1) % 3 == 0) cout << "   ---------------------\n";
    }
}

// Function to check if it's safe to place a number in a cell
bool isSafe(vector<vector<int>> &grid, int row, int col, int num) {
    for (int x = 0; x < 9; x++) {
        if (grid[row][x] == num || grid[x][col] == num ||
            grid[3 * (row / 3) + x / 3][3 * (col / 3) + x % 3] == num)
            return false;
    }
    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(vector<vector<int>> &grid) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (grid[row][col] == 0) { // Find an empty cell
                for (int num = 1; num <= 9; num++) {
                    if (isSafe(grid, row, col, num)) {
                        grid[row][col] = num; // Place the number
                        if (solveSudoku(grid)) return true; // Recur
                        grid[row][col] = 0;  // Backtrack
                    }
                }
                return false; // No solution exists
            }
        }
    }
    return true; // Solved
}

int main() {
    vector<vector<int>> sudoku(9, vector<int>(9, 0));

    cout << "Welcome to the Sudoku Solver!\n";
    cout << "Enter your Sudoku puzzle (row by row):\n";
    cout << "Use 0 for empty cells.\n";

    // Input Sudoku puzzle
    for (int i = 0; i < 9; i++) {
        cout << "Enter 9 numbers for row " << i + 1 << " (separated by spaces): ";
        for (int j = 0; j < 9; j++) {
            cin >> sudoku[i][j];
        }
    }

    cout << "\nYour input Sudoku puzzle:\n";
    displayGrid(sudoku);

    // Solve the Sudoku puzzle
    if (solveSudoku(sudoku)) {
        cout << "\nSolved Sudoku puzzle:\n";
        displayGrid(sudoku);
    } else {
        cout << "\nThe Sudoku puzzle cannot be solved.\n";
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Puzzle {
public:
    virtual void display() = 0;
    virtual bool solve() = 0;
    virtual string getDifficulty() = 0;
    virtual ~Puzzle() {}
};


class Sudoku : public Puzzle {
private:
    vector<vector<int>> grid; // 9x9 Sudoku grid
    string difficulty;


    bool isSafe(int row, int col, int num) {
        for (int x = 0; x < 9; x++) {
            if (grid[row][x] == num || grid[x][col] == num ||
                grid[row - row % 3 + x / 3][col - col % 3 + x % 3] == num)
                return false;
        }
        return true;
    }


    bool backtrackSolve() {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                if (grid[row][col] == 0) { /
                    for (int num = 1; num <= 9; num++) {
                        if (isSafe(row, col, num)) {
                            grid[row][col] = num;
                            if (backtrackSolve())
                                return true;
                            grid[row][col] = 0;
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }

public:

    Sudoku(vector<vector<int>> inputGrid, string level) : grid(inputGrid), difficulty(level) {}

    void display() override {
        cout << "Sudoku Puzzle (" << difficulty << "):" << endl;
        for (const auto &row : grid) {
            for (int num : row) {
                cout << (num ? to_string(num) : ".") << " ";
            }
            cout << endl;
        }
    }

    bool solve() override {
        if (backtrackSolve()) {
            cout << "\nSolved Sudoku:" << endl;
            display();
            return true;
        } else {
            cout << "\nNo solution exists for this Sudoku." << endl;
            return false;
        }
    }

    string getDifficulty() override {
        return difficulty;
    }
};


class Maze : public Puzzle {
private:
    vector<vector<char>> maze;
    string difficulty;

public:
    Maze(vector<vector<char>> inputMaze, string level) : maze(inputMaze), difficulty(level) {}

    void display() override {
        cout << "Maze Puzzle (" << difficulty << "):" << endl;
        for (const auto &row : maze) {
            for (char cell : row) {
                cout << cell << " ";
            }
            cout << endl;
        }
    }

    bool solve() override {

        cout << "Solving the maze..." << endl;
        return true;
    }

    string getDifficulty() override {
        return difficulty;
    }
};


class PuzzleManager {
private:
    vector<Puzzle *> puzzles;

public:
    void addPuzzle(Puzzle *puzzle) {
        puzzles.push_back(puzzle);
    }

    void displayPuzzles() {
        cout << "\nAvailable Puzzles:\n";
        for (size_t i = 0; i < puzzles.size(); i++) {
            cout << i + 1 << ". " << typeid(*puzzles[i]).name() << " (" << puzzles[i]->getDifficulty() << ")\n";
        }
    }

    void solvePuzzle(int index) {
        if (index >= 1 && index <= puzzles.size()) {
            puzzles[index - 1]->display();
            puzzles[index - 1]->solve();
        } else {
            cout << "Invalid puzzle selection!" << endl;
        }
    }

    ~PuzzleManager() {
        for (Puzzle *puzzle : puzzles) {
            delete puzzle;
        }
    }
};

int main() {
    PuzzleManager manager;


    vector<vector<int>> sudokuGrid = {
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
    manager.addPuzzle(new Sudoku(sudokuGrid, "Medium"));


    vector<vector<char>> mazeGrid = {
        {'S', '.', '.', '#', '.'},
        {'#', '#', '.', '#', '.'},
        {'.', '.', '.', '#', '.'},
        {'#', '#', '.', '.', '.'},
        {'.', '#', '#', '#', 'E'}
    };
    manager.addPuzzle(new Maze(mazeGrid, "Hard"));


    manager.displayPuzzles();


    int choice;
    cout << "\nEnter the number of the puzzle you want to solve: ";
    cin >> choice;
    manager.solvePuzzle(choice);

    return 0;
}

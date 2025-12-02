#include <stdio.h>

// Global Sudoku grid
int puzzle[9][9] = {
    {3,0,0,0,2,0,0,7,0},
    {9,0,0,5,0,0,0,1,4},
    {0,1,6,3,7,0,0,0,8},
    {2,0,0,8,0,0,0,0,1},
    {5,0,0,0,4,1,8,0,0},
    {0,8,9,0,0,0,0,5,0},
    {0,0,5,0,1,0,2,8,0},
    {0,4,0,0,0,6,0,9,3},
    {7,3,1,0,8,2,0,0,0}
};

// Tracks original cells (1 = original, 0 = user/solution)
int is_original[9][9];

// Function declarations
void print_puzzle(int puzzle[9][9]);
int valid_move(int puzzle[9][9], int row, int col, int value);
int solve_puzzle(int puzzle[9][9], int row, int col);

int main() {
    printf("\n\t   *-* Welcome to the Sudoku Solver! *-*\n");
    printf("\nOriginal Puzzle:\n");
    print_puzzle(puzzle);

    // Mark original values
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            is_original[r][c] = (puzzle[r][c] != 0);
        }
    }

    // User input section
    printf("\nEnter values for empty cells (0 = skip, -1 = auto-solve):\n");

    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {

            if (is_original[r][c]) 
                continue; // skip original numbers

            int temp;
            printf("\nEnter value for cell (%d, %d): ", r + 1, c + 1);
            scanf("%d", &temp);

            // Auto solve trigger
            if (temp == -1) {
                printf("\nSolving puzzle...\n");
                solve_puzzle(puzzle, 0, 0);
                print_puzzle(puzzle);
                return 0;
            }

            // Validate input range
            while (temp < 0 || temp > 9) {
                printf("Invalid! Enter a number between 0–9: ");
                scanf("%d", &temp);
            }

            // Validate Sudoku rules
            if (temp != 0 && !valid_move(puzzle, r, c, temp)) {
                printf("Invalid move! Try again.\n");
                c--; 
                continue;
            }

            puzzle[r][c] = temp;
        }
    }

    // Solve puzzle
    if (solve_puzzle(puzzle, 0, 0)) {
        printf("\nPuzzle Solved:\n");
        print_puzzle(puzzle);
    } else {
        printf("\nThis puzzle is not solvable.\n");
    }

    return 0;
}

// Backtracking solver
int solve_puzzle(int puzzle[9][9], int row, int col) {

    if (col == 9) {
        if (row == 8)
            return 1; 
        row++;
        col = 0;
    }

    if (puzzle[row][col] > 0)
        return solve_puzzle(puzzle, row, col + 1);

    for (int i = 1; i <= 9; i++) {
        if (valid_move(puzzle, row, col, i)) {
            puzzle[row][col] = i;

            if (solve_puzzle(puzzle, row, col + 1))
                return 1;

            puzzle[row][col] = 0; // backtrack
        }
    }

    return 0;
}

// Check if a value is valid in the given row, column, and 3x3 box
int valid_move(int puzzle[9][9], int row, int col, int value) {

    // Row check
    for (int i = 0; i < 9; i++)
        if (puzzle[row][i] == value)
            return 0;

    // Column check
    for (int i = 0; i < 9; i++)
        if (puzzle[i][col] == value)
            return 0;

    // 3x3 box check
    int r = row - row % 3;
    int c = col - col % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (puzzle[r + i][c + j] == value)
                return 0;

    return 1;
}

// Print Sudoku grid with colors
void print_puzzle(int puzzle[9][9]) {

    printf("\n+-------+-------+-------+");

    for (int row = 0; row < 9; row++) {

        if (row % 3 == 0 && row != 0)
            printf("\n|-------|-------|-------|");

        printf("\n");

        for (int col = 0; col < 9; col++) {

            if (col % 3 == 0)
                printf("| ");

            if (puzzle[row][col] != 0) {

                if (is_original[row][col])
                    printf("\033[32m%d \033[0m", puzzle[row][col]); // Green: original
                else
                    printf("\033[33m%d \033[0m", puzzle[row][col]); // Yellow: user/solver
            } else {
                printf("  ");
            }
        }
        printf("|");
    }
    printf("\n+-------+-------+-------+\n");
}

        

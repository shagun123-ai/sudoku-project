#include<stdio.h>

int puzzle[9][9] = {

    {3,0,0,0,2,0,0,7,0},
    {9,0,0,5,0,0,0,1,4},
    {0,1,6,3,7,0,0,0,8},
    {2,0,0,8,0,0,0,0,1},
    {5,0,0,0,4,1,8,0,0},
    {0,8,9,0,0,0,0,5,0},
    {0,0,5,0,1,0,2,8,0},
    {0,4,0,0,0,6,0,9,3},
    {7,3,1,0,8,2,0,0,0},

};

void print_puzzle(int puzzle[9][9]);
int valid_move(int puzzle[9][9] , int row , int col , int value);
int solve_puzzle(int puzzle[9][9] , int row , int col);
int is_original[9][9];

int main() {

printf("\n\t   *-*Welcome to SUDOKU SOLVER!!*-*\n ");
printf("\nOriginal Puzzle : ");
print_puzzle(puzzle);


// Mark original values AFTER user input
for(int r = 0; r < 9; r++){

    for(int c = 0; c < 9; c++){

        is_original[r][c] = (puzzle[r][c] != 0);

    }

}

// Let user enter missing values
printf("\nEnter your values (0 to skip):\n");

for(int r = 0; r < 9; r++){
    for(int c = 0; c < 9; c++){

        if(is_original[r][c] == 1)

            continue; // skip original numbers

int temp;

printf("\nEnter value for cell (%d,%d) (0=skip, -1=get solution): ", r+1, c+1);
scanf("%d", &temp);

// If user enters -1 → stop input & solve puzzle instantly
if(temp == -1) {

    printf("\nSolving puzzle for you...\n");

    solve_puzzle(puzzle, 0, 0);

    print_puzzle(puzzle);

    return 0;  // exit main

}

// validate 0-9 input
while(temp < 0 || temp > 9) {
    printf(" Invalid! Enter number 0-9: ");
    scanf("%d", &temp);
}

        // if user enters number, check Sudoku rules
        if(temp != 0 && !valid_move(puzzle, r, c, temp)) {
            printf(" Invalid Sudoku move! Try again.\n");
            // repeat same cell
            c--; 
            continue;
        }                     
// if valid fill it  
        puzzle[r][c] = temp;

    }

}


//puzzle soluble or not?
if(solve_puzzle(puzzle , 0 , 0)) {
    printf("\n\n puzzle is Solved :\n");
    print_puzzle(puzzle);
}

else {
    printf("\nPuzzle is not soluble.\n\n");
}
       
return 0;

}

int solve_puzzle(int puzzle[9][9] , int row , int col) {

    if(col == 9) {
        if (row == 8) {
            return 1;   //puzzle solved
        }

        row++;
        col = 0; 
    }

    if(puzzle[row][col] > 0) {
        return solve_puzzle(puzzle , row , col + 1);
    }

    for(int i = 1 ; i <= 9 ; i ++) {

        if(valid_move(puzzle , row , col , i)) {
            puzzle[row][col] = i;

            if(solve_puzzle(puzzle , row , col + 1)) {
                    //early move shi h
                return 1;
            }
                //if early move wrong , earse it.
            puzzle[row][col] = 0;
        }

    }
    return 0;
}


// check for valid row or unvalid row
int valid_move(int puzzle[9][9] , int row , int col , int value){

    for(int i = 0 ; i < 9 ; i ++) {
        if(puzzle[row][i] == value) {

            return 0;

        }
    }
    
    //valid col or unvalid col
    for(int i = 0 ; i < 9 ; i++) {
        if(puzzle[i][col] == value) {

            return 0;

        }
    }

    int r = row - row % 3;
    int c = col - col % 3;

    for(int i = 0 ; i < 3 ; i++) {
        for (int j = 0 ; j < 3 ; j++) {

            if(puzzle[r + i][c + j] == value) {
                return 0;
            }
        }
    }

    return 1;
}

void print_puzzle(int puzzle[9][9]) {

printf("\n+-------+-------+-------+");

for(int row = 0 ; row < 9 ; row++) {

    if(row % 3 == 0 && row != 0) {
        printf("\n|-------|-------|-------|");
    }


 {
     printf("\n");
    for (int col = 0 ; col < 9 ; col++) {

        if(col % 3 == 0 ) {
            printf("| ");
        }

if (puzzle[row][col] != 0) {

    if (is_original[row][col])
    
        // Green for original
    printf("\033[32m%d \033[0m", puzzle[row][col]); 

    else
        printf("\033[33m%d \033[0m", puzzle[row][col]); // Yellow for new
} 

else {
    printf("  ");
}

    }
    printf("|");
}
}

printf("\n+-------+-------+-------+");
}
        

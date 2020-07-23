//Freefall is a simple program designed to read and exhibit certain displays
//based on suitable user input.
//Features of freefall include: 
//1. Printing lines of stones on a map.
//2. Moving the player 'P' (situated at the bottom of the map).
//3. Destroying stones on the map.
//4. Shifting contents of the map down by one row. 
//5. A WIN or LOSE game feature.
//6. A vertical flip command.
//7. Create circle on the map (based on the concept of 'TNT blocks')
//8. Marching Blocks.
//9. Blocks above the map.
//10. Gravity storm.

// Author: Alexandria Ji Soo Yoo (z5308575)
// Date: 
// UNSW Freefall assignment.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 15
#define EMPTY 0
#define STONE 1

void printMap(int map[SIZE][SIZE], int playerX);
void tnt_block(int tnt_value, int tnt_row, int tnt_col, int map[SIZE][SIZE]);
int command1(int playerX);
void command2(int map[SIZE][SIZE], int playerX);
void command3(int map[SIZE][SIZE], int playerX, int count_three);
void command4(int map[SIZE][SIZE]);
int game_won(int map[SIZE][SIZE]);
int game_lost(int map[SIZE][SIZE]);

int main (void) {
    int map[SIZE][SIZE] = {EMPTY}, stones;
    int playerX = SIZE / 2;
    
    //Enter the number of lines of stones you wish to see on the map.
    printf("How many lines of stone? ");
    scanf("%d", &stones);
    
    //Enter the particular location of the stones in terms of their respective 
    //row, column,length and value.
    printf("Enter lines of stone:\n");
    int row, column, length, value;
    
    int update = 0;
    //Ensures the number of lines of stones on the map matches user input (from 
    //line 34).
    for(int i = 0;i<stones;i++) {
        scanf("%d%d%d%d", &row, &column, &length, &value);
        //Checks that user input is valid, i.e. does not exceed the dimensions 
        //of the map.
        if ((row >= 0 && row < SIZE) && 
            (column >= 0 && column < SIZE) &&
            (length > 0 && length < SIZE)) {
            for (int j = 0; j < length; j++) {
                //Assigns the value of the stones in a horizontal line to be 
                //placed on the map.
                map[row][column + j] = value;
            }
            
        }
    }
    
    printMap(map, playerX);
    
    int game_on = 1;
    int command;
    int run=0;
    int flips = 0; 
    int count_3 = 0;
    //While loop will continue to run until EOF or until its specified condition
    //does not hold true (game_on != 1).
    while (game_on == 1) {
        //MOVE PLAYER code starts here.
        //Enter '1' as the first integer command to move the player.
        scanf("%d", &command);
        
        if (command == 1) {
            playerX = command1(playerX);
            //Calls the function 'printMap' that will print the map with the 
            //stones.
            printMap(map, playerX);
        }
        if (command == 2) {
        
            command2(map, playerX);
             
            if (game_won(map) == 1) 
            {
                printf("Game Won!\n");
                game_on = 0;
            }
            else {
            printMap(map, playerX);
            }
        }
        if (command == 3) {
            //run = run +1;
            count_3 = count_3 + 1;
            if (game_lost(map) == 1)
            {
                printf("Game Lost!\n");
                game_on=0;
            }
            else
            {
                command3(map, playerX, count_3 );
                printMap(map, playerX);
            }
            
        }     
        
        if (command == 4) {
            int i;
            flips = flips + 1; 
            if (flips == 1) {
                command4(map);
                printMap(map, playerX);
            } 
            else
            {       
                printMap(map, playerX);
            } 
        } 
        
    }
}
void printMap(int map[SIZE][SIZE], int playerX) {
    int i = 0;
    while (i < SIZE) {
        int j = 0;
        while (j < SIZE) {
            printf("%d ", map[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }    
    
    i = 0;
    while (i < playerX) {
        printf("  ");
        i++;
    }
    printf("P\n");
}

int command1(int playerX) {
    //Enter '1' or '-1' as the second integer command to move the player to 
    //the right or to the left respectively.
    int direction;
    
    scanf("%d", &direction);
    if (direction == 1 || direction == -1) {
        //Checks the new position of the player does not exceed the 
        //dimensions of the map.
        if ((playerX + direction) >= 0 && (playerX + direction)
            < SIZE) {
            //Sets the player's new position.
            playerX = playerX + direction;
        }
    }
    return playerX;    
}

void command2(int map[SIZE][SIZE], int playerX) 
{

    int k = 0, one = 0, tnt_value = -1;
    int tnt_col, tnt_row;
    int game_on = 1;
    while (k < SIZE) {
        
        
        if (map[SIZE - 1 - k][playerX] > 0 && one < 3) 
        {
            one = one + 1;
            
            if (map[SIZE - 1 - k][playerX] > 1) 
            {
                    tnt_value = map[SIZE - 1 - k][playerX];
                    tnt_row = SIZE - 1 - k;
                    tnt_col = playerX;
            }
                
            map[SIZE - 1 - k][playerX] = 0;
                   
        }
        k++;
    }
        

    if (tnt_value > 1)
    {
        tnt_block(tnt_value,tnt_row, tnt_col,  map);
    }
    
}
       
    

/*

void command3(int map[SIZE][SIZE], int playerX, int count_three) {
    int new_map[SIZE][SIZE] = {EMPTY};
    int *ptr = &map[0][0];
    int num_shifts = 0;
    //while (num_shifts <= SIZE - row) {
    for (int num1 = 1; num1 < SIZE; num1++) {
        new_map[0][num1] = 0;
        for (int num2 = 0; num2 < SIZE; num2++) {
            if (num1 + 1 <= SIZE) {
                if (map[num1][num2] != 2)
                {
                    new_map[num1][num2] = *(ptr + (num1 - 1) * SIZE + num2);
                }
                else
                {
                    printf("count three value is: %d\n", count_three);
                    if (count_three > 1)
                    {
                        if (count_three % 2 == 0)
                        {
                            new_map[num1][num2] = *(ptr + (num1-1)*SIZE + num2 -1);
                        }
                        else
                        {
                            new_map[num1][num2] = *(ptr + (num1-1)*SIZE + num2 + 1);
                        }
                    }
                    else
                    {
                        new_map[num1][num2] = *(ptr + (num1-1)*SIZE + num2);
                    }
                }
                
            }
        }
    }
        
  
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            map[i][j] = new_map[i][j];
        }
    }

}
*/
int game_lost(int map[SIZE][SIZE])
{
    int s=0;
    while (s < SIZE) {
        if (map[SIZE-1][s] > 0) {
            return 1;
            
        }
        s++;
    }
    return 0; 
} 
    
    
      
void tnt_block(int tnt_value,int tnt_row, int tnt_col,  int map[SIZE][SIZE])
{
    
    
        int i;
        for (i = 0; i < SIZE; i++) {
            int j;
            for (j = 0; j < SIZE; j++) {

                double distance = sqrt((tnt_row - i) * (tnt_row - i) + 
                                          (tnt_col - j) * (tnt_col - j));
                if (distance < tnt_value) {
                    map[i][j] = 0;
                }
            }
        }
    
}


void command4(int map[SIZE][SIZE]) {
    int new_map[SIZE][SIZE] ;
    for (int i = 0; i < SIZE; i++) {
        int j;
        for (j = 0; j < SIZE; j++) {
            new_map[i][j] = map[SIZE - i - 1][j];
        }    
    } 
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            map[i][j] = new_map[i][j];
        }
    }
}   

int game_won (int map[SIZE][SIZE]) {
    int i = 0, count = 0;
    while (i < SIZE) {
        int j = 0;
        while (j < SIZE) 
        {
            if (map[i][j] == 0) 
            {
                count++;
                        }
                        j++;
                    }
                    i++;
                }
                if (count == SIZE * SIZE) {
                    return 1;
                } 
                return 0;
}

void command3(int map[SIZE][SIZE], int playerX, int count_3) 
{
    //Declares a new map that will store the position of stones after a shift
    //down.
    int new_map[SIZE][SIZE] = {EMPTY};
    //Declares a pointer variable that stores the address of the first element
    //in new_map.
    int *ptr = &map[0][0];
    printf("Count three value is %d\n", count_3);
    for (int num1 = 1; num1 < SIZE; num1++) 
    {
        //Integers in the top row of the new map is EMPTY after a shift down.
        new_map[0][num1] = 0;
        for (int num2 = 0; num2 < SIZE; num2++) 
        {
            if (num1 + 1 <= SIZE) 
            {
                //The following if statement determines whether the command for 
                //shifting the map has been typed in more than once in run-time.
                //printf("Value is %d\n", map[num1][num2]);
                if (count_3 > 1 ) 
                {
                    
                    if (count_3 % 4 == 0)
                    { 
                            //When count_3 is divisible by both 2 and 4, the 
                            //following code shifts the map to the left.
                            new_map[num1-1][num2] = *(ptr + (num1-1) * SIZE + 
                                                    num2+1);
                    }
                    if (count_3 % 4 ==2) 
                    {
                            //Following code shifts the map to the right.
                            new_map[num1-1][num2] = *(ptr + (num1-1) * SIZE 
                            + num2-1
                                                );
                        
                    }
                    if (count_3 % 4 == 1 || count_3 % 4 == 3)
                    {
                        new_map[num1][num2] = *(ptr + (num1 - 1) * SIZE + num2);
                    }
                }
                else 
                {
                    new_map[num1][num2] = *(ptr + (num1 - 1) * SIZE + num2);
                }

            } 
                           

                //Following code shifts the map down.
            
        }    
    }
    
    
    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++) 
        {
            //Stores 'new_map' into 'map'.
            map[i][j] = new_map[i][j];
        }
    }
}

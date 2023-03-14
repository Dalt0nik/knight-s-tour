#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int attempts = 0;
int milestones = 0;

bool validMove(int boardSize, int board[][boardSize], int nextX, int nextY);
bool solveTourRec(int x, int y, int boardSize, int board[][boardSize], int moveX[], int moveY[], int step);
void solveTour(int x, int y, int boardSize);
void printBoard(int boardSize, int board[boardSize][boardSize]);
int main()
{
    int boardSize, startX, startY;
    int moveX[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int moveY[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

    printf("Iveskite lentos dydi: ");
    scanf("%d", &boardSize);
    printf("Iveskite per tarpa pradines koordinates: ");
    scanf("%d %d", &startX, &startY);
    printf("\n\nRunning...\n\n");

    int board[boardSize][boardSize];

    // int moveX[8] = { 1, 1, -1, -1, 2, 2, -2, -2 };
    // int moveY[8] = { 2, -2, 2, -2, 1, -1, 1, -1 };

    for(int i = 0; i < boardSize; i++)
    {
        for(int j = 0; j < boardSize; j++)
            board[i][j] = 0;
    }

    
    

    board[startX][startY] = 1;
    if(solveTourRec(startX, startY, boardSize, board, moveX, moveY, 1) == false)
        printf("Impossible to solve\n");
    else
        printf("Attempts: %d * 100 mil + %d\n\n", milestones, attempts);
        for(int i = 0; i < boardSize; i++)
        {
            for (int j = 0; j < boardSize; j++)
            {
                if(board[i][j] / 10 == 0)
                    printf("  %d", board[i][j]);
                else
                    printf(" %d", board[i][j]);
            }
            printf("\n");
            
        }



    return 0;
}


void solveTour(int x, int y, int boardSize)
{

}

bool solveTourRec(int x, int y, int boardSize, int board[][boardSize], int moveX[], int moveY[], int step)
{
    attempts++;
    if(attempts / 100000000)
    {
        printf("100 mil\n");
        attempts = 0;
        milestones++;
    }

    //printBoard(boardSize, board);


    if(step == boardSize*boardSize)
        return true;

    for(int i = 0; i < 8; i++)
    {
        int nextX, nextY;
        nextX = x + moveX[i];
        nextY = y + moveY[i];

        if(validMove(boardSize, board, nextX, nextY))
        {
            board[nextX][nextY] = step + 1;
            if(solveTour(nextX, nextY, boardSize, board, moveX, moveY, step + 1))
                return true;
            else
                board[nextX][nextY] = 0;
        }       
    }
    return false;

}


bool validMove(int boardSize, int board[][boardSize], int nextX, int nextY)
{
    return (nextX >= 0 && nextX < boardSize && nextY >= 0 && nextY < boardSize && board[nextX][nextY] == 0);
}

void printBoard(int boardSize, int board[boardSize][boardSize])
{
    for(int i = 0; i < boardSize; i++)
        {
            for (int j = 0; j < boardSize; j++)
            {
                if(board[i][j] / 10 == 0)
                    printf("  %d", board[i][j]);
                else
                    printf(" %d", board[i][j]);
            }
            printf("\n");
            
        }
        printf("\n\n");
}
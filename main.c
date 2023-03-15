#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


long attempts = 1;
int milestones = 0;

char validMove(int boardSize, int board[][boardSize], int nextX, int nextY);
bool solveTourRec(int x, int y, int boardSize, int board[][boardSize], int moveX[], int moveY[], char moveNames[8][3], int step, FILE *myFile);
void solveTour(int x, int y, int boardSize, FILE *myFile);
void printBoard(int boardSize, int board[boardSize][boardSize], FILE *myFile);
int main()
{
    int boardSize, startX, startY;
    FILE *myFile;
    myFile = fopen("Protokolas.txt", "w");
    
    printf("\nIveskite lentos dydi: ");
    scanf("%d", &boardSize);
    printf("Iveskite per tarpa pradines koordinates: ");
    scanf("%d %d", &startX, &startY);
    printf("\n\nSkaiciuojama...\n\n");

    solveTour(startX-1, startY-1, boardSize, myFile);
   

    return 0;
}


void solveTour(int startX, int startY, int boardSize, FILE *myFile)
{
    int board[boardSize][boardSize];

    int moveX[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int moveY[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
    char moveNames[8][3] = {"R1","R2","R3","R4","R5","R6","R7","R8"};

    // int moveX[8] = { 1, 1, -1, -1, 2, 2, -2, -2 };
    // int moveY[8] = { 2, -2, 2, -2, 1, -1, 1, -1 };

    for(int i = 0; i < boardSize; i++)
    {
        for(int j = 0; j < boardSize; j++)
            board[i][j] = 0;
    }

    board[startX][startY] = 1;

    fprintf(myFile, "PIRMA DALIS. Duomenys\n"
    "1) Lenta %dx%d.\n"
    "2) Pradine zirgo padetis: X=%d, Y=%d, L=1.\n\n"
    "ANTRA DALIS. Vykdymas", boardSize, boardSize, startX+1, startY+1);

    if(solveTourRec(startX, startY, boardSize, board, moveX, moveY, moveNames, 1, myFile) == false)
    {
        fprintf(myFile, "\n\nTRECIA DALYS. Rezultatai\n"
        "1) Apejimo nera. Bandymu %d\n", attempts-1);
    }
    else
    {
        fprintf(myFile, "\n\nTRECIA DALYS. Rezultatai\n"
        "1) Apejimas rastas. Bandymu: %d\n"
        "Apejimas grafiskai:\n\n", attempts-1);
        printBoard(boardSize, board, myFile);
    }
}

bool solveTourRec(int x, int y, int boardSize, int board[][boardSize], int moveX[], int moveY[], char moveNames[8][3], int step, FILE *myFile)
{
    // attempts++;
    // if(attempts / 100000000)
    // {
    //     printf("100 mil\n");
    //     attempts = 0;
    //     milestones++;
    // }

    if(step == boardSize*boardSize)
        return true;

    for(int i = 0; i < 8; i++)
    {
        int nextX, nextY;
        nextX = x + moveX[i];
        nextY = y + moveY[i];

        if(validMove(boardSize, board, nextX, nextY) == 1)
        {
            fprintf(myFile, "\n%d) %s. U=%d, V=%d. L=%d. Laisva. LENTA[%d,%d]:=%d.", attempts, moveNames[i], nextX+1, nextY+1, step+1, nextX+1, nextY+1, step+1);
            attempts++;

            board[nextX][nextY] = step + 1;
            if(solveTourRec(nextX, nextY, boardSize, board, moveX, moveY, moveNames, step + 1, myFile))
                return true;
            else
                board[nextX][nextY] = 0;
        }  
        else if(validMove(boardSize, board, nextX, nextY) == 0)
        {
            fprintf(myFile, "\n%d) %s. U=%d, V=%d. L=%d. Uzimta.", attempts, moveNames[i], nextX+1, nextY+1, step+1);
            attempts++;
        }  
        else
        {
            fprintf(myFile, "\n%d) %s. U=%d, V=%d. L=%d. Uz krasto.", attempts, moveNames[i], nextX+1, nextY+1, step+1);
            attempts++;
        }
    }
    fprintf(myFile, " Backtrack.");
    return false;

}



char validMove(int boardSize, int board[][boardSize], int nextX, int nextY)
{
    if(nextX < 0 || nextX >= boardSize || nextY < 0 || nextY >= boardSize)
        return -1;
    else if(board[nextX][nextY] != 0)
        return 0;
    else
        return 1;
}



void printBoard(int boardSize, int board[boardSize][boardSize], FILE *myFile)
{
    for(int i = 0; i < boardSize; i++)
        {
            for (int j = 0; j < boardSize; j++)
            {
                if(board[i][j] / 10 == 0)
                    fprintf(myFile, "  %d", board[i][j]);
                else
                    fprintf(myFile, " %d", board[i][j]);
            }
            fprintf(myFile, "\n");
            
        }
        fprintf(myFile, "\n\n");
}
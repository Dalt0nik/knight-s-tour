#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


long attempts = 1;

char validMove(int boardSize, int board[][boardSize], int nextX, int nextY);
bool solveTourRec(int x, int y, int boardSize, int board[][boardSize], int moveX[], int moveY[], char moveNames[8][3], int step, FILE *myFileBig);
void solveTour(int x, int y, int boardSize, FILE *myFileBig, FILE *myFileSmall);
void printBoard(int boardSize, int board[boardSize][boardSize], FILE *myFileBig, FILE *myFileSmall);
void printAll(char string[], FILE *myFileBig, FILE *myFileSmall);
int main()
{
    int boardSize, startX, startY;
    FILE *myFileBig, *myFileSmall;
    char fileNameBig[100], fileNameSmall[100];
    
    printf("\nIveskite lentos dydi: ");
    scanf("%d", &boardSize);
    printf("Iveskite per tarpa pradines koordinates: ");
    scanf("%d %d", &startX, &startY);
    printf("Iveskite pilna failo varda trumpam protokolui:\n");
    scanf("%s", &fileNameSmall);
    printf("Iveskite pilna failo varda pilnam protokolui:\n");
    scanf("%s", &fileNameBig);
    printf("\n\nSkaiciuojama...\n\n");

    myFileBig = fopen(fileNameBig, "w");
    myFileSmall = fopen(fileNameSmall, "w");

    solveTour(startX-1, startY-1, boardSize, myFileBig, myFileSmall);
   

    return 0;
}


void solveTour(int startX, int startY, int boardSize, FILE *myFileBig, FILE *myFileSmall)
{
    int board[boardSize][boardSize];



    int moveX[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int moveY[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
    char moveNames[8][3] = {"R1","R2","R3","R4","R5","R6","R7","R8"};


    for(int i = 0; i < boardSize; i++)
    {
        for(int j = 0; j < boardSize; j++)
            board[i][j] = 0;
    }

    board[startX][startY] = 1;

    fprintf(myFileBig, "PIRMA DALIS.\n"
    "2 uzduotis, 4 variantas. Evgenij Shapovalov, 3 grupe, 2 pogrupis.\n\n"
    "1.1 SALYGA: Apeiti kvadrata N*N zirgo ejimais. Vartotojas nurodo kvadrato dydi ir pradine padeti.\n\n"
    "1.2 PRADINE BUSENA:\n"
    "1) Lenta %dx%d.\n"
    "2) Pradine zirgo padetis: X=%d, Y=%d, L=1.\n\n"
    "ANTRA DALIS. Vykdymas", boardSize, boardSize, startX+1, startY+1);

    fprintf(myFileSmall, "PIRMA DALIS.\n"
    "2 uzduotis, 4 variantas. Evgenij Shapovalov, 3 grupe, 2 pogrupis\n\n"
    "1.1 SALYGA: Apeiti kvadrata N*N zirgo ejimais. Vartotojas nurodo kvadrato dydi ir pradine padeti.\n\n"
    "1.2 PRADINE BUSENA:\n"
    "1) Lenta %dx%d.\n"
    "2) Pradine zirgo padetis: X=%d, Y=%d, L=1.\n\n" , boardSize, boardSize, startX+1, startY+1);

    printf("PIRMA DALIS.\n"
    "2 uzduotis, 4 variantas. Evgenij Shapovalov, 3 grupe, 2 pogrupis\n\n"
    "1.1 SALYGA: Apeiti kvadrata N*N zirgo ejimais. Vartotojas nurodo kvadrato dydi ir pradine padeti.\n\n"
    "1.2 PRADINE BUSENA:\n"
    "1) Lenta %dx%d.\n"
    "2) Pradine zirgo padetis: X=%d, Y=%d, L=1.\n\n" , boardSize, boardSize, startX+1, startY+1);

    if(solveTourRec(startX, startY, boardSize, board, moveX, moveY, moveNames, 1, myFileBig) == false)
    {
        fprintf(myFileBig, "\n\nTRECIA DALIS. Rezultatai\n"
        "1) Apejimo nera. Bandymu %d\n", attempts-1);
        fprintf(myFileSmall, "\n\nTRECIA DALIS. Rezultatai\n"
        "1) Apejimo nera. Bandymu %d\n", attempts-1);
        printf("\n\nTRECIA DALIS. Rezultatai\n"
        "1) Apejimo nera. Bandymu %d\n", attempts-1);
    }
    else
    {
        fprintf(myFileBig, "\n\nTRECIA DALIS. Rezultatai\n"
        "1) Apejimas rastas. Bandymu: %d\n"
        "Apejimas grafiskai:\n\n", attempts-1);

        fprintf(myFileSmall, "\n\nTRECIA DALIS. Rezultatai\n"
        "1) Apejimas rastas. Bandymu: %d\n"
        "Apejimas grafiskai:\n\n", attempts-1);

        printf("\n\nTRECIA DALIS. Rezultatai\n"
        "1) Apejimas rastas. Bandymu: %d\n"
        "Apejimas grafiskai:\n\n", attempts-1);

        printBoard(boardSize, board, myFileBig, myFileSmall);
    }
}

bool solveTourRec(int x, int y, int boardSize, int board[][boardSize], int moveX[], int moveY[], char moveNames[8][3], int step, FILE *myFileBig)
{
    if(step == boardSize*boardSize)
        return true;

    for(int i = 0; i < 8; i++)
    {
        int nextX, nextY;
        nextX = x + moveX[i];
        nextY = y + moveY[i];

        
       
        fprintf(myFileBig, "\n% 8d)", attempts);
        
        for(int r = 0; r < step-1; r++)
            fprintf(myFileBig, "-");

        if(validMove(boardSize, board, nextX, nextY) == 1)
        {
            fprintf(myFileBig, "%s. U=%d, V=%d. L=%d. Laisva. LENTA[%d,%d]:=%d.", moveNames[i], nextX+1, nextY+1, step+1, nextX+1, nextY+1, step+1);
            attempts++;

            board[nextY][nextX] = step + 1;
            if(solveTourRec(nextX, nextY, boardSize, board, moveX, moveY, moveNames, step + 1, myFileBig))
                return true;
            else
                board[nextY][nextX] = 0;
        }  
        else if(validMove(boardSize, board, nextX, nextY) == 0)
        {
            fprintf(myFileBig, "%s. U=%d, V=%d. L=%d. Uzimta.", moveNames[i], nextX+1, nextY+1, step+1);
            attempts++;
        }  
        else
        {
            fprintf(myFileBig, "%s. U=%d, V=%d. L=%d. Uz krasto.", moveNames[i], nextX+1, nextY+1, step+1);
            attempts++;
        }
    }
    fprintf(myFileBig, " Backtrack.");
    return false;

}



char validMove(int boardSize, int board[][boardSize], int nextX, int nextY)
{
    if(nextX < 0 || nextX >= boardSize || nextY < 0 || nextY >= boardSize)
        return -1;
    else if(board[nextY][nextX] != 0)
        return 0;
    else
        return 1;
}



void printBoard(int boardSize, int board[boardSize][boardSize], FILE *myFileBig, FILE *myFileSmall)
{


    printAll(" Y,V\n\n", myFileBig, myFileSmall);
    for(int i = boardSize-1; i >= 0; i--)
        {
            printf("%d |",i+1);
            fprintf(myFileBig, "%d |",i+1);
            fprintf(myFileSmall, "%d |",i+1);
            for (int j = 0; j < boardSize; j++)
            {
                if(board[i][j] / 10 == 0)
                {
                    fprintf(myFileBig, "  %d", board[i][j]);
                    fprintf(myFileSmall, "  %d", board[i][j]);
                    printf("  %d", board[i][j]);
                }
                    
                else
                {
                    fprintf(myFileBig, " %d", board[i][j]);
                    fprintf(myFileSmall, " %d", board[i][j]);
                    printf(" %d", board[i][j]);
                }
                    
            }
            printAll("\n", myFileBig, myFileSmall);
            
        }
    printAll("   -", myFileBig, myFileSmall);
    for(int i = 0; i < boardSize; i++)
    {
        printAll("---", myFileBig, myFileSmall);
    }
    
    printAll("  X,U\n", myFileBig, myFileSmall);

    printAll("     ", myFileBig, myFileSmall);
    for(int i = 1; i <= boardSize; i++)
    {
        printf("%d  ",i);
        fprintf(myFileBig,"%d  ",i);
        fprintf(myFileSmall,"%d  ",i);
    }
        
}

void printAll(char string[], FILE *myFileBig, FILE *myFileSmall)
{
    printf(string);
    fprintf(myFileBig, string);
    fprintf(myFileSmall, string);
}
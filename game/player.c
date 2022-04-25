//
// Created by Jorge on 4/22/2022.
//

#include <stdio.h>
#include "player.h"
#include "utils.h"
#include <math.h>

bool VerifyPlayerWinByLine(struct Board *b){
    int i = 0,x = 0;
    bool playerWon = false;
    for(i = 0; i < BOARD_MATRIX_ORDER; i++){
        bool equal = true;
        int firstValue = b->board[i][0];

        if(firstValue == PLAYER_SYMBOL_NULL){
            equal = false;
        }

        for(x = 0; x < BOARD_MATRIX_ORDER; x++){
            if(b->board[i][x] != firstValue)
                equal = false;
        }
        if(equal)
            playerWon = true;
    }
    return playerWon;
}

bool VerifyPlayerWinByColumn(struct Board *b){
    int i = 0,x = 0;
    bool playerWon = false;
    for(i = 0; i < BOARD_MATRIX_ORDER; i++){
        bool equal = true;
        int firstValue = b->board[0][i];

        if(firstValue == PLAYER_SYMBOL_NULL){
            equal = false;
        }

        for(x = 0; x < BOARD_MATRIX_ORDER; x++){
            if(b->board[x][i] != firstValue)
                equal = false;
        }
        if(equal)
            playerWon = true;
    }
    return playerWon;
}

bool VerifyPlayerWinByDiagInverted(struct Board *b){
    int lin,col = BOARD_MATRIX_ORDER-1;
    int defaultValue = b->board[0][BOARD_MATRIX_ORDER-1];
    bool playerWon = true;

    if(defaultValue == PLAYER_SYMBOL_NULL){
        playerWon = false;
    }else{
        if(defaultValue == PLAYER_SYMBOL_NULL){
        playerWon = false;
        }

        //now verify the inverted diagonal
        for(lin = 0; lin < BOARD_MATRIX_ORDER; lin++){
            if(b->board[lin][col] != defaultValue){
                playerWon = false;
            }
            col--; // decrement the col to validate the inverted diagonal
        }
        return playerWon;
    }
}

bool VerifyPlayerWinByDiag(struct Board *b){
    int lin,col = 0;
    int defaultValue = b->board[0][0];
    bool playerWon = true;

    if(defaultValue == PLAYER_SYMBOL_NULL){
        playerWon = false;
    }else{
        for(lin = 0; lin < BOARD_MATRIX_ORDER; lin++){

            if(b->board[lin][col] != defaultValue){
                playerWon = false;
                //printf("the value from row: %d, col: %d, its different from %d \n",lin,col,defaultValue);
            }
            col++; // increment the col to validate the diagonal
        }
        return playerWon;
    }
}

void setPlayerBoardVictory(struct Game *gameBoard,struct Board *b,int *boardIndex ){
    b->finished = true;
    b->winner = gameBoard->currentlyPlaying;
    gameBoard->currentlyPlaying->victories++;
    //todo - change XXX with the player name
    printf("Player ");
    displayString(gameBoard->currentlyPlaying->name);
    printf(" Won the board %d.\n",*boardIndex);
    printf("==================================\n");
}

int playMove(struct Game *gameBoard,struct Board *b,int *boardIndex){

    printf("> Player Playing: ");
    displayString(gameBoard->currentlyPlaying->name);
    printf(" | Playing on board: %d\n",*boardIndex);
    printf("In witch index do you want to play?\n");
    printf("Your board game index: ");
    int playIndex = -1;
    scanf("%d",&playIndex);

    //verify if the play index the user is trying to play really exists;
    int limitIndex = pow(BOARD_MATRIX_ORDER,2) -1;
    if(playIndex > limitIndex || playIndex < 0){
        printf("You provided a invalid index number, please provide a valid index based on the current game. \n");
        printf("The index's must be between 0 and %d \n",limitIndex);
        printf("--------------------------------------------\n");
        playIndex = playMove(gameBoard,b,boardIndex);
    }

    int row = playIndex / BOARD_MATRIX_ORDER;
    int column = playIndex % BOARD_MATRIX_ORDER;

    //check if that board number is already occupied
    if(gameBoard->boards[*boardIndex].board[row][column] == PLAYER_SYMBOL_BALL ||
            gameBoard->boards[*boardIndex].board[row][column] == PLAYER_SYMBOL_X){
        printf("You provided a invalid index that is already occupied :( Please try again \n");
        printf("--------------------------------------------\n");
        playIndex = playMove(gameBoard,b,boardIndex);
    }else{
        //update board position
        printf("-- Updating board %d with index %d, row: %d col: %d\n",*boardIndex,playIndex,row,column);
        b->board[row][column] = gameBoard->currentlyPlaying->symbol;
        displayGameBoard(gameBoard);
    }

    //verify by line
    bool winLine = VerifyPlayerWinByLine(b);

    //verify by column
    bool winColumn = VerifyPlayerWinByColumn(b);

    //verify by diag
    bool winDiag = VerifyPlayerWinByDiag(b);

    //verify by diag inverted
    bool winDiagInverted = VerifyPlayerWinByDiagInverted(b);

    if(winLine || winColumn || winDiag || winDiagInverted){
        setPlayerBoardVictory(gameBoard,b,boardIndex);
    }

    //Verify if on the outside boards game someone won
    verifyBoardVictory(gameBoard);

    //returns the index that the player played in that board to affect the next move
    return playIndex;
}

void playerInitialization(struct Player *player,char *playerName, enum PlayerSymbolCode psc){
    int i = 0;

    while (*playerName != '\0'){
        player->name[i] = *playerName;
        playerName++;
        i++;
    }

    player->defeats = 0;
    player->victories = 0;
    player->symbol = psc;
}

void displayPlayer(struct Player *player){

    printf("=========================================\n");
    printf("Player Name: ");
    int charI = 0;
    while(player->name[charI] != '\0'){
        printf("%c",player->name[charI]);
        charI++;
    }
    printf("\n");
    printf("Player Victories: %d\n",player->victories);
    printf("Player Defeats: %d\n", player->defeats);
    printf("Player Symbol Code Number: %d\n",player->symbol);
    printf("=========================================\n\n");
}
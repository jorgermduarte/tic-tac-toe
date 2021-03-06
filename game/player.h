//
// Created by Jorge Duarte on 4/22/2022.
// a2021110042
//

#ifndef TIC_TAC_TOE_PLAYER_H
#define TIC_TAC_TOE_PLAYER_H

#include <stdbool.h>
#include "gameBoard.h"

#define PLAYER_NAME_SIZE 5

typedef enum PlayerSymbolCode{
    PLAYER_SYMBOL_NULL = 0,
    PLAYER_SYMBOL_BALL = 1,
    PLAYER_SYMBOL_X = 2,
    PLAYER_SYMBOL_DRAW = 3
};

typedef struct Player{
    char name[PLAYER_NAME_SIZE];
    int victories;
    int defeats;
    enum PlayerSymbolCode symbol; // if the player is the O,X ou another symbol
    bool isBot;
};

/*
 * Given a respective play, the user provided the index where he wanted to play his move
 * we receive the pointer to the board from the boards list in the game
 * should verify if the given position is already occupied or played, to verify the authenticity of his move
 * if the play was successful it will return the index played, if not it returns -1
 *
 */
int playMove(struct Game *gameBoard,struct Board *b,int *boardIndex);

void playerInitialization(struct Player *player,char *target, enum PlayerSymbolCode psc,bool isBot);

void displayPlayer(struct Player *player);

bool VerifyPlayerWinByLine(struct Board *b);
bool VerifyPlayerWinByColumn(struct Board *b);
bool VerifyPlayerWinByDiagInverted(struct Board *b);
bool VerifyPlayerWinByDiag(struct Board *b);
bool VerifyPlayerBoardDraw(struct Board *b);


#endif //TIC_TAC_TOE_PLAYER_H

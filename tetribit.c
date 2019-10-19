// Copyright 2018 <Copyright Cristiana Lazar>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint-gcc.h>

void mapDisplay(uint64_t map) {
    int i = 63;
    while (i > 0) {
        for (int j = 0; j < 8; j++) {
            if (((map >> i) & 1u) == 1)
                printf("#"); // bits equal with 1 are displayed
            else
                printf("."); // bits equal with 0 are displayed
            i--;
        }
        printf("\n");
    }
    printf("\n");
}

// place the piece at the start of the map
uint64_t singlePieceOnMap(uint64_t piece) {
    int i;
    for (i = 16; i >= 0; i--) {
        if (((piece >> i) & 1u) == 1) {
            break;
        }
    }
    if (i < 8) {
        return piece << 56u;
    } else {
        return piece << 48u;
    }
}

int pieceStartPos(uint64_t piece) {
    int i;
    for (i = 63; i >= 0; i--) {
        if ((piece >> i) & 1u) {
            break;
        }
    }
    return i;
}

int pieceEndPos(uint64_t piece) {
    int i, endPos = 0;
    for (i = 63; i >= 0; i--) {
        if ((piece >> i) & 1u) {
            endPos = i;
        }
    }
    return endPos;
}

uint64_t transformation(uint64_t map, uint64_t piece, int transf) {
    int i, moves = 0;

    if (transf > 0) {
        int endPos = pieceEndPos(piece);
        for (i = 1; i <= transf; i++) {
            if (!((piece >> (moves + 1)) & map)) {
                if ((piece >> (endPos + 7)) & 1u) {
                    if (((endPos + 7) / 8) == ((endPos + 7 - i) / 8)) {
                        moves++;
                    } else {
                        break;
                    }
                } else if (((endPos / 8) == ((endPos - i) / 8) &&
                            ((endPos - i) > 0))) {
                    moves++;
                } else if (((endPos - i) < 8) && (i < 8)) {
                    moves = endPos;
                } else {
                    break;
                }
            } else {
                break;
            }
        }
        return piece >> moves;
    } else if (transf < 0) {
        int startPos = pieceStartPos(piece);
        transf = abs(transf);
        for (i = 1; i <= transf; i++) {
            if (!((piece << (moves + 1) & map))) {
                if ((piece >> (startPos - 7)) & 1u) {
                    if (((startPos - 7) / 8) == ((startPos - 7 + i) / 8)) {
                        moves++;
                    } else {
                        break;
                    }
                } else if ((piece >> (startPos - 9)) & 1u) {
                    if ((startPos / 8) == ((startPos + i) / 8)) {
                        moves++;
                    } else {
                        break;
                    }
                } else if ((startPos / 8) == ((startPos + i) / 8)) {
                    moves++;
                } else {
                    break;
                }
            }
        }
        return piece << moves;
    } else {
        return piece;
    }
}

uint64_t removeCompletedLines(uint64_t map, int *completedLines) {
    int i;
    uint64_t mapAux1, mapAux2;

    for (i = 0; i < 64; i += 8) {
        if (((map >> i) & 0XFF) == 0XFF) {
            if (i) {
                mapAux1 = map << (64 - i);
                mapAux1 = mapAux1 >> (64 - i);

                mapAux2 = map >> (i + 8);
                mapAux2 = mapAux2 << i;
                map = mapAux1 | mapAux2;
                *completedLines = *completedLines + 1;
                i -= 8;
            } else {
                map = map >> 8;
                *completedLines = *completedLines + 1;
                i -= 8;
            }
        }
    }
    return map;
}

int numOfZeros(uint64_t map) {
    int i, noZeros = 0;
    for (i = 63; i >= 0; i--) {
        if (((map >> i) & 1) == 0)
            noZeros++;
    }
    return noZeros;
}

void printScore(uint64_t map, int completedLines) {
    double score;
    score = sqrt(numOfZeros(map)) + pow(1.25, completedLines);
    printf("Score:%.2f", score);
}

void newGame(int M_moves, uint64_t map) {
    uint64_t mapAux = map;
    uint64_t piece;
    int transf, i, j, collision = 0, gameOver = 0, aux;
    int completedLines = 0;

    mapDisplay(map);

    if (M_moves) {
        for (i = 0; i < M_moves; i++) {
            if (!gameOver) {
                scanf("%lu", &piece);
                piece = singlePieceOnMap(piece);

                for (j = 0; j < 8; j++) {
                    scanf("%d", &transf);
                    if (!gameOver) {
                        if (!collision) {
                            if ((piece << 8u) && !j) {
                                // check for collision
                                if (!((piece << 8u) & map)) {
                                    piece = transformation(map, piece, transf);
                                    mapAux = map | (piece << 8u);
                                    mapDisplay(mapAux);
                                } else {
                                    gameOver = 1;
                                }
                            } else {
                                // check for collision
                                if (!(piece & map)) {
                                    piece = transformation(map, piece, transf);
                                    mapAux = map | piece;
                                    mapDisplay(mapAux);
                                    if ((piece >> 8u) & map) {
                                        collision = 1;
                                    } else {
                                        piece = piece >> 8u; // piece get down
                                    }
                                } else {
                                    gameOver = 1;
                                }
                            }
                        }
                    }
                }
                collision = 0;
                aux = completedLines;
                map = removeCompletedLines(mapAux, &completedLines);
                if (aux < completedLines)
                    mapDisplay(map);
            }
        }
    }
    if (gameOver) {
        mapDisplay(map);
    }
    printf("GAME OVER!\n");
    printScore(map, completedLines);
}

int main() {
    uint64_t map;
    int M_moves;

    scanf("%lu", &map); // the map is read
    scanf("%d", &M_moves);  // read the M moves
    newGame(M_moves, map);
    return 0;
}

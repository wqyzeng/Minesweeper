#include "minesweeper_lib.h"
#include "minesweeper.h"

char * createBoard(std::size_t xdim, std::size_t ydim){
    char *board{new char[xdim*ydim]{}};
    return board;
}
void hideBoard(char * board, std::size_t xdim, std::size_t ydim){
    for (std::size_t i{0}; i<xdim*ydim; ++i){
        board[i] |= hiddenBit();
    }
}
void cleanBoard(char * board){
    delete[] board;
    board = nullptr;
}
void printBoard(char * board, std::size_t xdim, std::size_t ydim){
    for (std::size_t i{0}; i < (xdim * ydim); ++i){
        //check if marked
        if (board[i] & markedBit()){
            std::cout << 'M';
        } 
        //check if hidden
        else if (board[i] & hiddenBit()){
            std::cout << '*';
        } 
        //display field value (0-9)
        else {
            std::cout << int(board[i]);
        }
        //print new line 
        if (((i + 1) % xdim) == 0){
            std::cout << std::endl;
        }
    }
}

int mark(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
    int index = (yloc*xdim)+xloc;

    if ((board[index] & markedBit()) == markedBit()){
        board[index] ^= markedBit();
      return 0;
    }
    else if ((board[index] & hiddenBit()) == hiddenBit()){
        board[index] |= markedBit();
        return 0;
    }
    else {
      return 2;
    }
}

void computeNeighbors(char * board, std::size_t xdim, std::size_t ydim){
    for (std::size_t i{0}; i < xdim*ydim; ++i){
        //check every field until goose is found uwu
        if (board[i] == 9){
            //increment field above
            if (i >= xdim){
                if (board[i - xdim] != 9){
                    board[i - xdim] ++;
                }
            }
            //increment field below
            if (i < xdim*ydim-xdim){
                if (board[i + xdim] != 9){
                    board[i + xdim] ++;
                }
            }
            //increment field to the left
            if ((i % xdim) != 0){
                if (board[i - 1] != 9){
                    board[i - 1] ++;
                }
            }
            //increment field to the right
            if ((i+1)%xdim != 0){
                if (board[i + 1] != 9){
                    board[i + 1] ++;
                }
            }
            //increment field to the left and above 
            if (i >= xdim && (i % xdim) != 0){
                if (board[i - xdim - 1] != 9){
                    board[i - xdim - 1] ++;
                }
            }
            //increment field to the right and above
            if (i >= xdim && (i + 1)%xdim != 0){
                if (board[i - xdim + 1] != 9){
                    board[i - xdim + 1] ++;
                }
            }
            //increment field to the left and down
            if (i < xdim*ydim-xdim && (i % xdim) != 0){
                if (board[i + xdim - 1] != 9){
                    board[i + xdim - 1] ++;
                }
            }
            //increment field to the rght and down
            if (i < xdim*ydim-xdim && (i+1)%xdim != 0){
                if (board[i + xdim + 1] != 9){
                    board[i + xdim + 1] ++;
                }
            }
        }
    }
}
int reveal(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
    int index = (yloc*xdim)+xloc;
    if (board[index] & hiddenBit()){
        //goose :(
        if (int(board[index] & valueMask()) == 9){
            board[index] &= valueMask();
            return 9;
        }
        //no goose
        else if (int(board[index] & valueMask()) == 0){
            board[index] &= valueMask();
            //up
            if (index >= xdim){
                board[index-xdim] &= valueMask();
            }
            //down
            if (index < xdim*ydim-xdim){
                board[index+xdim] &= valueMask();
            }
            //left
            if ((index % xdim) != 0){
                board[index-1] &= valueMask();
            }
            //right
            if ((index+1)%xdim != 0){
                board[index+1] &= valueMask();
            }
            //up and left
            if (index >= xdim && (index % xdim) != 0){
                board[index-xdim-1] &= valueMask();
            }
            //up and right
            if (index >= xdim && (index+1)%xdim != 0){
                board[index-xdim+1] &= valueMask();
            }
            //down and left
            if (index < xdim*ydim-xdim && (index % xdim) != 0){
                board[index+xdim-1] &= valueMask();
            }
            //down and right
            if (index < xdim*ydim-xdim && (index+1)%xdim != 0){    
                    board[index+xdim+1] &= valueMask();  
            }
            return 0;
        }
        else {
            board[index] &= valueMask();
            return 0;
        }     
    }
    else if (board[index] & markedBit()){
        return 1;
    }
    else {
        return 2;
    }
}
bool isGameWon(char * board, std::size_t xdim, std::size_t ydim){
    for (std::size_t i{0}; i<xdim*ydim; ++i){
        if ((board[i] & hiddenBit()) && ((board[i] & valueMask()) != 0x09)) { 
            return false; 
        } 
    }
    return true;
}

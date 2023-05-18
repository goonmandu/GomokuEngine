#pragma once
#include "OmokMove.h"
#include "consts.h"

#include <vector>

/* With no alpha-beta pruning (unmodified minimax):
 * int  representation does 76.7k nodes/sec
 * bool representation does 94.9k nodes/sec (+23.7% improvement)
 **/

class Omok {
    private:
        std::vector<std::vector<int>> board;
        
        // Experimental bitboard
        std::vector<std::vector<bool>> board_black;
        std::vector<std::vector<bool>> board_white;
        int black_stones;
        int white_stones;
    
    public:
        Omok();
        Omok(std::vector<std::vector<int>>);
        void place(int player, int row, int col);
        void place(OmokMove move);
        std::vector<std::vector<int>> get_board();
        void print_board();

        // Bitboard functions and constructors
        Omok(int flag);
        Omok(std::vector<std::vector<bool>> black, std::vector<std::vector<bool>> white);
        void place_bitboard(bool player, int row, int col);  // false = black, true = white
        std::vector<std::vector<bool>> get_bitboard(bool player);
        void print_bitboard(bool player);
        void increment(bool player);
        int stones_of(bool player);
};
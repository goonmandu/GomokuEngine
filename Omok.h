#pragma once

/* Performance Notes:
 *
 * With no alpha-beta pruning (unmodified minimax)
 * Environment: Apple M1, no power saving, 16GB RAM
 * Compiler arguments: -std=c++11 -Ofast
 *
 * int  representation does 124k nodes/sec (602927 nodes / 4.85s)
 * bool representation does 154k nodes/sec (601964 nodes / 3.90s)
 * 
 * Bitboard representation of omok board is 24.1% faster per node than 3-state int board
 * 
 **/

#include "OmokMove.h"
#include "consts.h"

#include <vector>


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
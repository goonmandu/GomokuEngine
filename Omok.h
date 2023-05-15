#pragma once
#include "OmokMove.h"
#include "consts.h"

#include <vector>

class Omok {
    private:
        std::vector<std::vector<int>> board;
    
    public:
        Omok();
        Omok(std::vector<std::vector<int>>);
        void place(int player, int row, int col);
        void place(OmokMove move);
        std::vector<std::vector<int>> get_board();
        void print_board();
};
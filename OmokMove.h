#pragma once
#include <iostream>

class OmokMove {
    public:
        int player;
        int row;
        int col;
        double eval = 0;

    public:
        OmokMove(int player, int row, int col);
        friend std::ostream& operator<<(std::ostream& os, const OmokMove &move);
};
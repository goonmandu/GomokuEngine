#include "consts.h"
#include "OmokMove.h"

OmokMove::OmokMove(int player, int row, int col) {
    this->player = player;
    this->row = row;
    this->col = col;
}

std::ostream& operator<<(std::ostream& os, const OmokMove &move) {
    os << move.player << " at " << "Row " << move.row << ", Col " << move.col \
       << ", eval=" << move.eval;
    return os;
}
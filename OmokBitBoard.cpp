#include <iostream>
#include "OmokBitBoard.h"

OmokBitBoard::OmokBitBoard() {
    for (int i = 0; i < DIM; ++i) {
        board_black.push_back({});
        board_white.push_back({});
        for (int k = 0; k < DIM; ++k) {
            board_black[i].push_back(false);
            board_white[i].push_back(false);
        }
    }
}

OmokBitBoard::OmokBitBoard(std::vector<std::vector<bool>> black, std::vector<std::vector<bool>> white) {
    for (int i = 0; i < DIM; ++i) {
        board_black.push_back({});
        board_white.push_back({});
        for (int k = 0; k < DIM; ++k) {
            board_black[i].push_back(black[i][k]);
            board_white[i].push_back(white[i][k]);
        }
    }
}

void OmokBitBoard::increment(bool player) {
    if (player) {
        ++white_stones;
    } else {
        ++black_stones;
    }
}

int OmokBitBoard::stones_of(bool player) {
    if (player) {
        return white_stones;
    } else {
        return black_stones;
    }
}

void OmokBitBoard::place_bitboard(bool player, int row, int col) {
    if (board_black[row][col] || board_white[row][col]) {
        std::cerr << "There is already a stone at " << row << ", " << col << "!" << std::endl;
        return;
    }
    if (player) {
        board_white[row][col] = true;
    } else {
        board_black[row][col] = true;
    }
}

std::vector<std::vector<bool>> OmokBitBoard::get_bitboard(bool player) {
    if (player) {
        return board_white;
    } else {
        return board_black;
    }
}

void OmokBitBoard::print_bitboard(bool player) {
    for (int i = 0; i < DIM; ++i) {
        for (int k = 0; k < DIM; ++k) {
            if (player) {
                if (board_white[i][k]) {
                    std::cout << "O ";
                } else {
                    std::cout << ". ";
                }
            } else {
                if (board_black[i][k]) {
                    std::cout << "X ";
                } else {
                    std::cout << ". ";
                }
            }
        }
        std::cout << std::endl;
    }
}
#include "Omok.h"
#include "consts.h"
#include <iomanip>

Omok::Omok() {
    for (int i = 0; i < DIM; ++i) {
        this->board.push_back({});
        for (int k = 0; k < DIM; ++k) {
            this->board[i].push_back(UNDEF);
        }
    }
}

Omok::Omok(std::vector<std::vector<int>> existing_board) {
    for (int i = 0; i < DIM; ++i) {
        this->board.push_back({});
        for (int k = 0; k < DIM; ++k) {
            this->board[i].push_back(existing_board[i][k]);
        }
    }
}

void Omok::place(int player, int row, int col) {
    this->board[row][col] = player;
}

void Omok::place(OmokMove move) {
    this->place(move.player, move.row, move.col);
}

void Omok::print_board() {
    for (auto row : this->board) {
        for (auto cell : row) {
            if (cell == UNDEF) {
                std::cout << ". ";
            } else if (cell == MAX) {
                std::cout << "X ";
            } else if (cell == MIN) {
                std::cout << "O ";
            } else {
                std::cout << "# ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

std::vector<std::vector<int>> Omok::get_board() {
    return board;
}
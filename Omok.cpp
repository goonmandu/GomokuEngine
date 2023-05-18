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

Omok::Omok(int flag) {
    for (int i = 0; i < DIM; ++i) {
        board_black.push_back({});
        board_white.push_back({});
        for (int k = 0; k < DIM; ++k) {
            board_black[i].push_back(false);
            board_white[i].push_back(false);
        }
    }
}

Omok::Omok(std::vector<std::vector<bool>> black, std::vector<std::vector<bool>> white) {
    for (int i = 0; i < DIM; ++i) {
        board_black.push_back({});
        board_white.push_back({});
        for (int k = 0; k < DIM; ++k) {
            board_black[i].push_back(black[i][k]);
            board_white[i].push_back(white[i][k]);
        }
    }
}

void Omok::increment(bool player) {
    if (player) {
        ++white_stones;
    } else {
        ++black_stones;
    }
}

int Omok::stones_of(bool player) {
    if (player) {
        return white_stones;
    } else {
        return black_stones;
    }
}

void Omok::place_bitboard(bool player, int row, int col) {
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

std::vector<std::vector<bool>> Omok::get_bitboard(bool player) {
    if (player) {
        return board_white;
    } else {
        return board_black;
    }
}

void Omok::print_bitboard(bool player) {
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
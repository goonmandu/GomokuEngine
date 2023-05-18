#include <iostream>
#include "Omok.h"
#include "OmokMove.h"
#include "consts.h"
#include "utils.h"

static long long moves_generated = 0;

int next_player(Omok omok) {
    int maxcount = 0;
    int mincount = 0;
    for (auto row : omok.get_board()) {
        for (auto cell : row) {
            if (cell == MAX) {
                maxcount++;
            } else if (cell == MIN) {
                mincount++;
            }
        }
    }
    if (maxcount == mincount) {
        return MAX;
    } else if (maxcount == mincount + 1) {
        return MIN;
    } else {  // Holy shit something bad happened
        return UNDEF;
    }
}

bool five_in_a_row(int cells[]) {
    for (int i = 0; i < 4; ++i) {
        if (cells[i] != cells[i+1]) {
            return false;
        }
    }
    return true;
}

int winner_of(Omok omok) {
    // Scan horizontally
    for (auto row : omok.get_board()) {
        for (int i = 0; i < DIM - 4; ++i) {
            if (row[i] == UNDEF) {
                continue;
            }
            if (five_in_a_row((int[]) {row[i], row[i+1], row[i+2], row[i+3], row[i+4]})) {
                return row[i];
            }
        }
    }

    // Scan vertically
    auto board = omok.get_board();
    for (int i = 0; i < DIM; ++i) {
        for (int k = 0; k < DIM - 4; ++k) {
            if (board[k][i] == UNDEF) {
                continue;
            }
            if (five_in_a_row((int[]) {board[k][i], board[k+1][i], board[k+2][i], board[k+3][i], board[k+4][i]})) {
                return board[k][i];
            }
        }
    }

    // Scan topleft-botright diagonals
    for (int i = 0; i < DIM - 4; ++i) {
        for (int k = 0; k < DIM - 4; ++k) {
            if (board[i][k] == UNDEF) {
                continue;
            }
            if (five_in_a_row((int[]) {board[i][k], board[i+1][k+1], board[i+2][k+2], board[i+3][k+3], board[i+4][k+4]})) {
                return board[i][k];
            }
        }
    }

    // Scan topright-botleft diagonals
    for (int i = 4; i < DIM; ++i) {
        for (int k = 0; k < DIM - 4; ++k) {
            if (board[i][k] == UNDEF) {
                continue;
            }
            if (five_in_a_row((int[]) {board[i][k], board[i-1][k+1], board[i-2][k+2], board[i-3][k+3], board[i-4][k+4]})) {
                return board[i][k];
            }
        }
    }

    return 2;  // Incomplete State
}

std::vector<OmokMove> next_moves(Omok omok, int radius) {
    std::vector<OmokMove> ret;

    auto board = omok.get_board();
    int next = next_player(omok);
    
    std::vector<std::vector<int>> occupied_cells;

    for (int i = 0; i < DIM; ++i) {
        for (int k = 0; k < DIM; ++k) {
            if (board[i][k] != UNDEF) {
                occupied_cells.push_back(std::vector<int>({i, k}));
            }
        }
    }

    if (occupied_cells.empty()) {
        ret.push_back(OmokMove(next, 7, 7));
        return ret;
    }

    std::vector<std::vector<int>> candidates;

    for (auto cell : occupied_cells) {
        int rb, re, cb, ce;
        if (cell[0] < radius) {
            rb = 0;
            re = cell[0] + radius + 1;
        } else if (cell[0] > DIM - 1 - radius) {
            rb = cell[0] - radius;
            re = DIM;
        } else {
            rb = cell[0] - radius;
            re = cell[0] + radius + 1;
        }
        if (cell[1] < radius) {
            cb = 0;
            ce = cell[1] + radius + 1;
        } else if (cell[1] > DIM - 1 - radius) {
            cb = cell[1] - radius;
            ce = DIM;
        } else {
            cb = cell[1] - radius;
            ce = cell[1] + radius + 1;
        }
        for (int i = rb; i < re; ++i) {
            for (int k = cb; k < ce; ++k) {
                std::vector<int> candcell = {i, k};
                if (!vector_contains(candidates, candcell) && !vector_contains(occupied_cells, candcell)) {
                    candidates.push_back(candcell);
                }
            }
        }
    }


    for (auto coords : candidates) {
        ret.push_back(OmokMove(next, coords[0], coords[1]));
    }
    
    return ret;
}

Omok result(Omok omok, OmokMove move) {
    Omok ret = Omok(omok.get_board());
    ret.place(move);
    return ret;
}

int evaluate(Omok omok) {
    int evaluation = 0;

    // BLACK MAGIC GOES HERE

    return evaluation;
}

int minimax(Omok omok, int depth) {
    moves_generated++;
    int state = winner_of(omok);
    int next = next_player(omok);

    if (depth == 0) {
        return evaluate(omok);
    }

    if (vector_contains(std::vector<int>{-1, 0, 1}, state)) {
        return state;
    }

    if (next == MAX) {
        int value = INT_MIN;
        for (auto move : next_moves(omok, 1)) {
            // std::cout << depth << ":" << "(" << move.row << "," << move.col << ")\n";
            value = max(value, minimax(result(omok, move), depth - 1));
        }
        return value;
    }

    if (next == MIN) {
        int value = INT_MAX;
        for (auto move : next_moves(omok, 1)) {
            // std::cout << depth << ":" << "(" << move.row << "," << move.col << ")\n";
            value = min(value, minimax(result(omok, move), depth - 1));
        }
        return value;
    }
    return 2;  // Something bad happened
}

std::vector<OmokMove> evaluate_moves(Omok omok, int radius, int depth) {
    std::cout << "Thinking..." << std::endl;
    auto valid_moves = next_moves(omok, radius);
    int next = next_player(omok);
    int best_outcome = (next == MAX) ? INT_MIN : INT_MAX;
    for (int i = 0; i < valid_moves.size(); ++i) {
        valid_moves[i].eval = minimax(result(omok, valid_moves[i]), depth);
        if (next == MAX && valid_moves[i].eval > best_outcome) {
            best_outcome = valid_moves[i].eval;
        } else if (next == MIN && valid_moves[i].eval < best_outcome) {
            best_outcome = valid_moves[i].eval;
        }
    }
    std::vector<OmokMove> ret;
    for (auto move : valid_moves) {
        if (best_outcome == move.eval) {
            ret.push_back(move);
        }
    }
    return ret;
}

bool five_in_a_row_bitboard(bool cells[]) {
    for (int i = 0; i < 4; ++i) {
        if (!cells[i]) {
            return false;
        }
    }
    return true;
}

bool next_player_bitboard(Omok omok) {
    if (omok.stones_of(false) == omok.stones_of(true)) {
        return false;
    } else {
        return true;
    }
}

bool bitboard_state(Omok omok, bool player) {
    // Scan horizontally
    for (auto row : omok.get_bitboard(player)) {
        for (int i = 0; i < DIM - 4; ++i) {
            if (row[i] && row[i+1] && row[i+2] && row[i+3] && row[i+4]) {
                return true;
            }
        }
    }

    // Scan vertically
    auto board = omok.get_bitboard(player);
    for (int i = 0; i < DIM; ++i) {
        for (int k = 0; k < DIM - 4; ++k) {
            if (board[k][i] && board[k+1][i] && board[k+2][i] && board[k+3][i] && board[k+4][i]) {
                return true;
            }
        }
    }

    // Scan topleft-botright diagonals
    for (int i = 0; i < DIM - 4; ++i) {
        for (int k = 0; k < DIM - 4; ++k) {
            if (board[i][k] && board[i+1][k+1] && board[i+2][k+2] && board[i+3][k+3] && board[i+4][k+4]) {
                return true;
            }
        }
    }

    // Scan topright-botleft diagonals
    for (int i = 4; i < DIM; ++i) {
        for (int k = 0; k < DIM - 4; ++k) {
            if (board[i][k] && board[i-1][k+1] && board[i-2][k+2] && board[i-3][k+3] && board[i-4][k+4]) {
                return true;
            }
        }
    }

    return false;
}

std::vector<OmokMove> next_moves_bitboard(Omok omok, int radius) {
    std::vector<OmokMove> ret;

    auto black_board = omok.get_bitboard(false);
    auto white_board = omok.get_bitboard(true);
    auto next = next_player_bitboard(omok);
    
    std::vector<std::vector<int>> occupied_cells;

    for (int i = 0; i < DIM; ++i) {
        for (int k = 0; k < DIM; ++k) {
            if (black_board[i][k] || white_board[i][k]) {
                occupied_cells.push_back(std::vector<int>({i, k}));
            }
        }
    }

    if (occupied_cells.empty()) {
        ret.push_back(OmokMove(next, 7, 7));
        return ret;
    }

    std::vector<std::vector<int>> candidates;

    for (auto cell : occupied_cells) {
        int rb, re, cb, ce;
        if (cell[0] < radius) {
            rb = 0;
            re = cell[0] + radius + 1;
        } else if (cell[0] > DIM - 1 - radius) {
            rb = cell[0] - radius;
            re = DIM;
        } else {
            rb = cell[0] - radius;
            re = cell[0] + radius + 1;
        }
        if (cell[1] < radius) {
            cb = 0;
            ce = cell[1] + radius + 1;
        } else if (cell[1] > DIM - 1 - radius) {
            cb = cell[1] - radius;
            ce = DIM;
        } else {
            cb = cell[1] - radius;
            ce = cell[1] + radius + 1;
        }
        for (int i = rb; i < re; ++i) {
            for (int k = cb; k < ce; ++k) {
                std::vector<int> candcell = {i, k};
                if (!vector_contains(candidates, candcell) && !vector_contains(occupied_cells, candcell)) {
                    candidates.push_back(candcell);
                }
            }
        }
    }


    for (auto coords : candidates) {
        ret.push_back(OmokMove((int) next, coords[0], coords[1]));
    }
    
    return ret;
}

double evaluate_bitboard(Omok omok) {
    double evaluation = 0;

    // Static analysis algorithm goes here.
    // AKA black magic

    return evaluation;
}

Omok result_bitboard(Omok omok, OmokMove move) {
    Omok ret = Omok(omok.get_bitboard(false), omok.get_bitboard(true));
    if (!move.player) {
        ret.place_bitboard(false, move.row, move.col);
    } else {
        ret.place_bitboard(true, move.row, move.col);
    }
    return ret;
}

int minimax_bitboard(Omok omok, int depth) {
    auto black_board = omok.get_bitboard(false);
    auto white_board = omok.get_bitboard(true);

    moves_generated++;
    bool next = next_player_bitboard(omok);

    if (depth == 0) {
        return evaluate_bitboard(omok);
    }

    if (bitboard_state(omok, false)) {
        return -1;
    } else if (bitboard_state(omok, true)) {
        return 1;
    }

    if (!next) {
        int value = INT_MAX;
        for (auto move : next_moves_bitboard(omok, 1)) {
            value = min(value, minimax_bitboard(result_bitboard(omok, move), depth - 1));
        }
        return value;
    } else {
        int value = INT_MIN;
        for (auto move : next_moves_bitboard(omok, 1)) {
            value = max(value, minimax_bitboard(result_bitboard(omok, move), depth - 1));
        }
        return value;
    }
}

std::vector<OmokMove> evaluate_moves_bitboard(Omok omok, int radius, int depth) {
    std::cout << "Thinking..." << std::endl;
    auto valid_moves = next_moves_bitboard(omok, radius);
    auto next = next_player_bitboard(omok);
    int best_outcome = (!next) ? INT_MAX : INT_MIN;
    for (int i = 0; i < valid_moves.size(); ++i) {
        valid_moves[i].eval = minimax_bitboard(result_bitboard(omok, valid_moves[i]), depth);
        if (!next && valid_moves[i].eval < best_outcome) {
            best_outcome = valid_moves[i].eval;
        } else if (next && valid_moves[i].eval > best_outcome) {
            best_outcome = valid_moves[i].eval;
        }
    }
    std::vector<OmokMove> ret;
    for (auto move : valid_moves) {
        if (best_outcome == move.eval) {
            ret.push_back(move);
        }
    }
    return ret;
}
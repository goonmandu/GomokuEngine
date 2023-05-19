#include <iostream>
#include "Omok.h"
#include "OmokMove.h"
#include "consts.h"
#include "utils.h"

static long long moves_generated = 0;

// 3-state board functions
int next_player(Omok omok);
bool five_in_a_row(int cells[]);
int winner_of(Omok omok);
std::vector<OmokMove> next_moves(Omok omok, int radius);
Omok result(Omok omok, OmokMove move);
int evaluate(Omok omok);
int minimax(Omok omok, int depth);
std::vector<OmokMove> evaluate_moves(Omok omok, int radius, int depth);

// Bitboard functions
bool five_in_a_row_bitboard(bool cells[]);
bool next_player_bitboard(Omok omok);
bool bitboard_state(Omok omok, bool player);
std::vector<OmokMove> next_moves_bitboard(Omok omok, int radius);
double evaluate_bitboard(Omok omok);
Omok result_bitboard(Omok omok, OmokMove move);
int minimax_bitboard(Omok omok, int depth);
std::vector<OmokMove> evaluate_moves_bitboard(Omok omok, int radius, int depth);
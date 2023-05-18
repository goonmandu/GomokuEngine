#pragma once

constexpr int DIM = 15;

// Ordinary omok board representation (std::vector<std::vector<int>>)
constexpr int MAX = 1;
constexpr int MIN = -1;
constexpr int UNDEF = 0;

// Bitboard omok board representation (std::vector<std::vector<bool>>)
constexpr bool BLACK = false;
constexpr bool WHITE = true;
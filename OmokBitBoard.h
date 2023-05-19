#include <vector>
#include "consts.h"

class OmokBitBoard {
    private:
        std::vector<std::vector<bool>> board_black;
        std::vector<std::vector<bool>> board_white;
        int black_stones;
        int white_stones;

    public:
        OmokBitBoard();
        OmokBitBoard(std::vector<std::vector<bool>> black, std::vector<std::vector<bool>> white);
        void place_bitboard(bool player, int row, int col);  // false = black, true = white
        std::vector<std::vector<bool>> get_bitboard(bool player);
        void print_bitboard(bool player);
        void increment(bool player);
        int stones_of(bool player);
};
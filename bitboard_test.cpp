#include <iostream>
#include "Engine.h"

int main() {
    Omok bitb = Omok(1);
    bitb.place_bitboard(false, 7, 7);
    bitb.place_bitboard(true, 6, 7);
    bitb.place_bitboard(false, 7, 6);
    bitb.place_bitboard(true, 7, 8);
    bitb.place_bitboard(false, 7, 5);
    bitb.place_bitboard(true, 7, 4);
    bitb.place_bitboard(false, 5, 6);
    bitb.place_bitboard(true, 8, 9);

    /*
    bitb.print_bitboard(false);
    std::cout << std::endl;
    bitb.print_bitboard(true);
    **/

    int radius = 1, depth = 3;
    /*
    std::cout << "Enter the search radius: ";
    std::cin >> radius;

    std::cout << "Enter the recursion depth: ";
    std::cin >> depth;
    **/
    auto evals = evaluate_moves_bitboard(bitb, radius, depth);
    // println_vector(evals, "\n");
    std::cout << moves_generated << std::endl;
}
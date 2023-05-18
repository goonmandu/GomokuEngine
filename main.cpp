#include <iostream>
#include "Engine.h"

int main(int argc, char **argv) {

    auto omok = Omok();
    omok.place(MAX, 7, 7);
    omok.place(MIN, 6, 7);
    omok.place(MAX, 7, 6);
    omok.place(MIN, 7, 8);
    omok.place(MAX, 7, 5);
    omok.place(MIN, 7, 4);
    omok.place(MAX, 5, 6);
    omok.place(MIN, 8, 9);

    // omok.print_board();

    int radius = 1, depth = 3;
    /*
    std::cout << "Enter the search radius: ";
    std::cin >> radius;

    std::cout << "Enter the recursion depth: ";
    std::cin >> depth;
    **/

    std::vector<OmokMove> evals = evaluate_moves(omok, radius, depth);
    //println_vector(evals, "\n");
    extern long long moves_generated;
    std::cout << moves_generated << std::endl;
}
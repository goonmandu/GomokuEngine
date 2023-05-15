#include "Engine.h"

int main() {
    auto omok = Omok();
    omok.place(MAX, 7, 7);
    omok.place(MIN, 6, 7);
    omok.place(MAX, 7, 6);
    omok.place(MIN, 7, 8);
    omok.place(MAX, 7, 5);
    omok.place(MIN, 7, 4);
    omok.place(MAX, 5, 6);
    omok.place(MIN, 8, 9);
    omok.place(MAX, 6, 6);
    omok.place(MIN, 9, 10);
    omok.place(MAX, 8, 6);

    omok.print_board();

    std::vector<OmokMove> evals = evaluate_moves(omok);
    println_vector(evals, "\n");

}
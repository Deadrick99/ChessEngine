#ifndef BOARD_H
#define BOARD_H

#include <string>

/**
 * Board Class, represented using 64 bit longs for each piece type + color
 */
namespace chess {
class board {
public:
    /**
     * Constructs board object using a FEN string.
     * @param fen FEN string representation of the board.
     * Requires: fen string must be in valid format
     */
    explicit board(const std::string& fen);

    /**
     * Updates board to the next turn based on inputted move.
     * @param move Integer representing a move.
     */
    void make_move(int move);

    /**
     * Updates board to the previous turn based on the inputted move.
     * @param move Integer representing a move.
     */
    void unmake_move(int move);

    /**
     * Returns the bit form of the rank and file.
     * @param rank Rank of the chess position.
     * @param file File of the chess position.
     * @return Bit based on the inputted rank and file.
     * Requires: rank and file must be between 0 and 7. Will throw exception otherwise.
     */
    inline static long long toBit(int rank, int file);

    /**
     * Turns a bit into a index from 0 to 64 based on the Little Edian Square-File mapping.
     * @param bit Bit representation of the piece posistion.
     * @return Index of the bit.
     * Requires: bit must contain only a singular bit. Will throw exception otherwise.
     */
    inline static long long toIndex(long long bit);

    /**
     * Returns current turn of the board. 0 for white and 1 for black.
     */
    [[nodiscard]] int get_turn() const { return turn; }

    const long long& operator[](const int i) const { return boardRep[i]; }
    using const_iterator = const long long*;
    [[nodiscard]] const_iterator begin() const { return boardRep; }
    [[nodiscard]] const_iterator end()   const { return boardRep + 12; }
private:
    long long boardRep[12] = {};
    int turn = 0;
    int castlingRights = 0;
    long long enPassant = 0;
};
}

#endif

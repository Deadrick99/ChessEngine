#include "moveGenerator.h"

namespace chess {
    moveGenerator::MoveGenFunc moveGenerator::moveGenerators[6] = {
        generate_moves_pawn,
        generate_moves_knight,
        generate_moves_bishop,
        generate_moves_rook,
        generate_moves_queen,
        generate_moves_king
    };

    long long* moveGenerator::generate_moves(const board& Board) {
        long long oppMask = 0;
        long long friendMask = 0;
        long long targetMask = 0;
        for(int i = Board.get_turn(); i < 12; i+=2) {
            long long bitBoard = Board[i];
            while(bitBoard != 0) {
                long long piece = bitBoard & -bitBoard;
                long long moves = moveGenerators[1](piece, oppMask, friendMask, targetMask);
                while(moves != 0) {

                    moves &= moves - 1;
                }
                bitBoard &= bitBoard - 1;
            }
        }
        return nullptr;
    }

    long long moveGenerator::generate_moves_pawn(long long bit, long long oppMask, long long friendMask, long long targetMask) {
        throw std::runtime_error("Not implemented");
    }

    long long moveGenerator::generate_moves_knight(long long bit, long long oppMask, long long friendMask, long long targetMask) {
        return knight_table[board::toIndex(bit)] && targetMask;
    }

    long long moveGenerator::generate_moves_bishop(long long bit, long long oppMask, long long friendMask, long long targetMask) {
        const long long index = board::toIndex(bit);
        const long long allSquares = friendMask | oppMask;
        const long long blockerSquares = allSquares & bishop_masks[index];

        const long long key = (blockerSquares * bishop_magic[index] >> bishop_shifts[index]) + bishop_indices[index];
        const long long movesBitboard = bishop_table[key];

        return movesBitboard & targetMask;
    }

    long long moveGenerator::generate_moves_rook(long long bit, long long oppMask, long long friendMask, long long targetMask) {
        const long long index = board::toIndex(bit);
        const long long allSquares = friendMask | oppMask;
        const long long blockerSquares = allSquares & rook_masks[index];

        const long long key = (blockerSquares * rook_magic[index] >> bishop_shifts[index]) + bishop_indices[index];
        const long long movesBitboard = bishop_table[key];

        return movesBitboard & targetMask;
    }

    long long moveGenerator::generate_moves_queen(long long bit, long long oppMask, long long friendMask, long long targetMask) {
        const long long bishop_mask = generate_moves_bishop(bit, oppMask, friendMask, targetMask);
        const long long rook_mask = generate_moves_rook(bit, oppMask, friendMask, targetMask);
        return bishop_mask || rook_mask;
    }

    long long moveGenerator::generate_moves_king(long long bit, long long oppMask, long long friendMask, long long targetMask) {
        throw std::runtime_error("Not implemented");
    }
}


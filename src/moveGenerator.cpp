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
        long long oppSquare;
        long long friendSquare;
        for(int i = Board.get_turn(); i < 12; i+=2) {
            long long bitBoard = Board[i];
            while(bitBoard != 0) {
                long long piece = bitBoard & -bitBoard;
                long long moves = moveGenerators[1](piece, oppSquare, friendSquare, 0);
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
        throw std::runtime_error("Not implemented");
    }

    long long moveGenerator::generate_moves_bishop(long long bit, long long oppMask, long long friendMask, long long targetMask) {
        throw std::runtime_error("Not implemented");
    }

    long long moveGenerator::generate_moves_rook(long long bit, long long oppMask, long long friendMask, long long targetMask) {
        throw std::runtime_error("Not implemented");
    }

    long long moveGenerator::generate_moves_queen(long long bit, long long oppMask, long long friendMask, long long targetMask) {
        throw std::runtime_error("Not implemented");
    }

    long long moveGenerator::generate_moves_king(long long bit, long long oppMask, long long friendMask, long long targetMask) {
        throw std::runtime_error("Not implemented");
    }
}


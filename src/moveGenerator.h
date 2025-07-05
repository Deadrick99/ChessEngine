#ifndef MOVEGENERATOR_H
#define MOVEGENERATOR_H

#include "board.h"

namespace chess {
    class moveGenerator {
    public:
        inline static long long* generate_moves(const board& Board);

        using MoveGenFunc = long long(*)(long long, long long, long long, long long);
        static MoveGenFunc moveGenerators[6];
    private:
        inline static long long generate_moves_pawn(long long bit, long long oppMask, long long friendMask, long long targetMask);
        inline static long long generate_moves_knight(long long bit, long long oppMask, long long friendMask, long long targetMask);
        inline static long long generate_moves_bishop(long long bit, long long oppMask, long long friendMask, long long targetMask);
        inline static long long generate_moves_rook(long long bit, long long oppMask, long long friendMask, long long targetMask);
        inline static long long generate_moves_queen(long long bit, long long oppMask, long long friendMask, long long targetMask);
        inline static long long generate_moves_king(long long bit, long long oppMask, long long friendMask, long long targetMask);
    };
}

#endif

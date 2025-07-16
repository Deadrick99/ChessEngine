#include "moveGenerator.h"
#include <fstream>
#include <iostream>
#include <sstream>

namespace chess {
    moveGenerator::MoveGenFunc moveGenerator::moveGenerators[6] = {
        generate_moves_pawn,
        generate_moves_knight,
        generate_moves_bishop,
        generate_moves_rook,
        generate_moves_queen,
        generate_moves_king
    };

    void moveGenerator::load_bishop_magic_table(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Could not open bishop magic table: " << path << std::endl;
            return;
        }

        std::string line;
        int i = 0;
        while (std::getline(file, line) && i < 5248) {
            std::istringstream iss(line);
            if (!(iss >> bishop_table[i])) {
                std::cerr << "Invalid value at line " << i << ": " << line << std::endl;
                break;
            }
            ++i;
        }

        if (i != 5248) {
            std::cerr << "Warning: Expected 5248 entries but got " << i << std::endl;
        } else {
            std::cout << "Bishop magic table loaded successfully." << std::endl;
        }
    }

    void chess::moveGenerator::load_rook_magic_table(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Could not open rook magic table: " << path << std::endl;
            return;
        }

        std::string line;
        int i = 0;
        while (std::getline(file, line) && i < 102400) {
            std::istringstream iss(line);
            if (!(iss >> rook_table[i])) {
                std::cerr << "Invalid value at line " << i << ": " << line << std::endl;
                break;
            }
            ++i;
        }

        if (i != 102400) {
            std::cerr << "Warning: Expected 102400 entries but got " << i << std::endl;
        } else {
            std::cout << "Rook magic table loaded successfully." << std::endl;
        }
    }

    void moveGenerator::generate_moves(const board& Board, bool captures, long long* output) {
        const int turn = Board.get_turn();
        const int opp_turn = turn ^ 0b1;
        const long long oppMask = Board[opp_turn] ^ Board[opp_turn + 2] ^  Board[opp_turn + 4] ^ Board[opp_turn + 6] ^ Board[opp_turn + 8] ^  Board[opp_turn + 10];;
        const long long friendMask = Board[turn] ^ Board[turn + 2] ^  Board[turn + 4] ^ Board[turn + 6] ^ Board[turn + 8] ^  Board[turn + 10];
        const long long targetMask = captures ? oppMask : -1;
        const int castlingRights = Board.get_castle();
        int index = 0;
        for(int i = Board.get_turn(); i < 12; i+=2) {
            long long bitBoard = Board[i];
            while(bitBoard != 0) {
                long long piece = bitBoard & -bitBoard;
                long long moves = moveGenerators[(i - Board.get_turn())/2](piece, oppMask, friendMask, targetMask, castlingRights);
                while(moves != 0) {
                    const long long pos = moves & - moves;
                    output[index] = make_move(piece, pos);
                    index++;
                    moves &= moves - 1;
                }
                bitBoard &= bitBoard - 1;
            }
        }
    }

    static int make_move(long long pos1, long long pos2) {
        return 0;
    }

    long long moveGenerator::generate_moves_pawn(long long bit, long long oppMask, long long friendMask, long long targetMask, int castlingRights) {
        throw std::runtime_error("Not implemented");
    }

    long long moveGenerator::generate_moves_knight(long long bit, long long oppMask, long long friendMask, long long targetMask, int castlingRights) {
        return knight_table[board::toIndex(bit)] && targetMask;
    }

    long long moveGenerator::generate_moves_bishop(long long bit, long long oppMask, long long friendMask, long long targetMask, int castlingRights) {
        const long long index = board::toIndex(bit);
        const long long allSquares = friendMask | oppMask;
        const long long blockerSquares = allSquares & bishop_masks[index];

        const long long key = (blockerSquares * bishop_magic[index] >> bishop_shifts[index]) + bishop_indices[index];
        const long long movesBitboard = bishop_table[key];

        return movesBitboard & targetMask;
    }

    long long moveGenerator::generate_moves_rook(long long bit, long long oppMask, long long friendMask, long long targetMask, int castlingRights) {
        const long long index = board::toIndex(bit);
        const long long allSquares = friendMask | oppMask;
        const long long blockerSquares = allSquares & rook_masks[index];

        const long long key = (blockerSquares * rook_magic[index] >> bishop_shifts[index]) + bishop_indices[index];
        const long long movesBitboard = bishop_table[key];

        return movesBitboard & targetMask;
    }

    long long moveGenerator::generate_moves_queen(long long bit, long long oppMask, long long friendMask, long long targetMask, int castlingRights) {
        const long long bishop_mask = generate_moves_bishop(bit, oppMask, friendMask, targetMask, castlingRights);
        const long long rook_mask = generate_moves_rook(bit, oppMask, friendMask, targetMask, castlingRights);
        return bishop_mask || rook_mask;
    }

    long long moveGenerator::generate_moves_king(long long bit, long long oppMask, long long friendMask, long long targetMask, int castlingRights) {
        const long long index = board::toIndex(bit);
        long long king_mask = king_table[index];

        long long allSquares = friendMask | oppMask;

        int turn = castlingRights >= 3 ? 0 : 1;
        if(turn == 0) castlingRights >>= 2;
        if ((allSquares & castle_free[turn][0]) == 0 && castlingRights >= 1) king_mask |= castle_free[turn][0];
        if ((allSquares & castle_free[turn][1]) == 0 && castlingRights >= 2) king_mask |= castle_free[turn][1];

        return king_mask;
    }
}


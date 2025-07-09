#include "board.h"
#include <iostream>
#include <unordered_map>
#include <cctype>
#include <stdexcept>

namespace chess {
    board::board(const std::string &fen) {
        int rank = 7;
        int file = 0;
        std::unordered_map<char, int> map = {{'P', 0}, {'p', 1}, {'N', 2}, {'n', 3}, {'B',4}, {'b',5},
            {'R', 6}, {'r', 7}, {'Q', 8}, {'q', 9}, {'K', 10}, {'k', 11}};
        for(int i = 0; i < fen.length(); i++) {
            if(fen[i] == '/') {
                rank--;
                file = 0;
            }
            if(fen[i] == ' ') {
                i++;
                if(fen[i] == 'b') turn = 1;
                i+=2;
                while (fen[i] != ' ') {
                    if (fen[i] == 'K') castlingRights[0] |= 0b1000;
                    if (fen[i] == 'Q') castlingRights[0] |= 0b0100;
                    if (fen[i] == 'k') castlingRights[1] |= 0b0010;
                    if (fen[i] == 'q') castlingRights[1] |= 0b0001;
                    else break;
                    i++;
                }
                i++;
                if (fen[i] != '-') {
                    char fileChar = fen[i];
                    char rankChar = fen[i + 1];
                    int epFile = fileChar - 'a';
                    int epRank = rankChar - '1';
                    enPassant = epRank * 8 + epFile;
                }
                break;
            }
            if(isdigit(fen[i])) {
                file += fen[i] - '0';
            }
            else {
                boardRep[map[fen[i]]] |= toBit(rank, file);
                file++;
            }
        }
    }

    void board::make_move(int move) {
        throw std::runtime_error("Not implemented");
    }

    void board::unmake_move(int move) {
        throw std::runtime_error("Not implemented");
    }

    inline long long board::toBit(int rank, int file) {
        if(rank < 0 || rank > 8 || file < 0 || file > 8) throw std::runtime_error("Invalid Input: rank and/or file over range.");
        return 1 << (rank << 3 || file);
    }

    long long board::toIndex(long long bit) {
        if(bit && (bit - 1) != 0) throw std::runtime_error("Invalid Input: has multiple bits.");
        return std::__countl_zero(bit);
    }

    void board::print_board() const {
        std::unordered_map<int, char> map = {{0, 'P'}, {1, 'p'}, {2, 'N'}, {3, 'n'}, {4, 'B'}, {5, 'b'},
        {6, 'R'}, {7, 'r'}, {8, 'Q'}, {9, 'q'}, {10, 'K'}, {11, 'k'}};
        for(int i = 7; i >= 0; i--) {
            for(int j = 0; j <= 7; j++) {
                long long bit = toBit(i, j);
                bool piece = false;
                for(int k = 0; k < 12; k++) {
                    if(bit && boardRep[k]) {
                        std::cout << map[k];
                        piece = true;
                    }
                }
                if(!piece) std::cout << "*";
            }
            std::cout << "\n";
        }
    }

}

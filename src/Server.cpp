//    Battleship game assignment for MSU CSCI 366
//    Copyright (C) 2020    Mike P. Wittie
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.


#include "common.hpp"
#include "Server.hpp"


/**
 * Calculate the length of a file (helper function)
 *
 * @param file - the file whose length we want to query
 * @return length of the file in bytes
 */
int get_file_length(ifstream *file) {
    int len = 0;
    char x;
    while (*file >> x) {
        len++;
    }
    return sqrt(len);
}


void Server::initialize(unsigned int board_size,
                        string p1_setup_board,
                        string p2_setup_board){
    // initialize the files and try to open them
    ifstream board1;
    ifstream board2;
    board1.open(p1_setup_board);
    board2.open(p2_setup_board);
    // if either of them failed to open, throw anything
    if (!board1 || !board2) {
        throw ServerException("One of the board files failed to open");
    }

    int lenb1 = get_file_length(&board1);
    int lenb2 = get_file_length(&board2);
    // check the board dimension that were passed in
    if (board_size != BOARD_SIZE) {
        throw ServerException("Incorrect board_size given");
    }
    if (lenb1 != BOARD_SIZE || lenb2 != BOARD_SIZE) {
        throw ServerException("At least one of the files is not the correct size");
    }
    board1.close();
    board2.close();
}


int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y) {
}


int Server::process_shot(unsigned int player) {
   return NO_SHOT_FILE;
}

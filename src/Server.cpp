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
int get_file_length(ifstream *file){
}


void Server::initialize(unsigned int board_size,
                        string p1_setup_board,
                        string p2_setup_board){
    // ensure the provided board size is correct
    if(board_size != BOARD_SIZE) {
        throw ServerException("The provided board size does not match the global constant 'board size'");
    } else {
        this->board_size = board_size;
    }
    // ensure the provided board names are not null
    if(p1_setup_board.size() < 1 || p2_setup_board.size() < 1) {
        throw ServerException("At least on of the file names provided is too short");
    }

    // instantiate the boards
    this->p1_setup_board = scan_setup_board(p1_setup_board);
    this->p2_setup_board = new BitArray2D(board_size, board_size);
}


Server::~Server() {
    delete this->p1_setup_board;
    delete this->p2_setup_board;
}


BitArray2D *Server::scan_setup_board(string setup_board_name){
    BitArray2D* board = new BitArray2D(board_size, board_size); // TODO more dynamic by reading in sizes from file, but should throw and error if they don't match
    ifstream setup_board;
    setup_board.open(setup_board_name); // open the setup board file to process the information
    // TODO check that the board opened
    // TODO get the length of the board and compare it to the board size
    char c;
    int count = 0;
    int row = 0;
    int col = 0;
    while(setup_board>>c) {
        for(char d : SHIPS) {
            if (c == d) {
                row = count / 10;
                col = count % 10;
                board->set(row,col);
                //cout << c << " at " << row << "," << col << "\n";
            }
        }
        count++;
    }
    return board;

}

int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y) {
}


int Server::process_shot(unsigned int player) {
   return NO_SHOT_FILE;
}
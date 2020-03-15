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


void Server::initialize(unsigned int in_board_size,
                        string in_p1_setup_board,
                        string in_p2_setup_board){
    board_size = in_board_size;
    // initialize the files and try to open them
    p1_setup_board.open(in_p1_setup_board);
    p2_setup_board.open(in_p2_setup_board);
    // need to replace boards with the servers vars when time allows
    // if either of them failed to open, throw anything
    if (!p1_setup_board || !p2_setup_board) {
        throw ServerException("One of the board files failed to open");
    }

    int lenb1 = get_file_length(&p1_setup_board);
    int lenb2 = get_file_length(&p2_setup_board);
    // check the board dimension that were passed in
    if (board_size != BOARD_SIZE) {
        throw ServerException("Incorrect board_size given");
    }
    if (lenb1 != BOARD_SIZE || lenb2 != BOARD_SIZE) {
        throw ServerException("At least one of the files is not the correct size");
    }
    p1_setup_board.close();
    p2_setup_board.close();
}


int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y) {

    // check that the player number is within bounds
    if(player > MAX_PLAYERS || player <= 0) {
        throw ServerException("the player number for process_shot was not appropriate");
    }
    // check that the shot coordinate is within bounds (if not return OUT_OF_BOUNDS)v
    if(x < 0 || x >= board_size || y < 0 || y >= board_size) {
        return OUT_OF_BOUNDS;
    }
    // determine which setup board to read from
    ifstream board_ifs;
    if(player == 1) {
        board_ifs.open("player_2.setup_board.txt");
    } else {
        board_ifs.open("player_1.setup_board.txt");
    }
    // determines if the shot is a hit or a miss

    // read characters up until where it should be?
    unsigned int offset = (y * (board_size+1)) + x;
    board_ifs.seekg(offset, ios::beg);
    char target[1];
    board_ifs.read(target, 1);
    // compare it to the characters in SHIPS
    for ( char const &c: SHIPS) {
        if(c == target[0])  {
            //board_ifs.close();
            return HIT;
        }
    }
    // if it matches a character then it is a hit, if it doesn't match one then it is a miss
    //board_ifs.close();
    return MISS;
}


int Server::process_shot(unsigned int player) {

    if(player > MAX_PLAYERS || player <= 0) {
        throw ServerException("the player number for process_shot was not appropriate");
    }
    unsigned int x;
    unsigned int y;
    // check if there is a file to read in
    string fname_in = ("player_"+to_string(player)+".shot.json");
    ifstream in_shot_file(fname_in);
    if(in_shot_file) {
        // extract coordinates
        stringstream in_stream;
        in_stream << in_shot_file.rdbuf();
        {
            cereal::JSONInputArchive shot_in(in_stream);
            shot_in(CEREAL_NVP(x), CEREAL_NVP(y));
        }
        // call evaluate_shot
        int eval;
        eval = evaluate_shot(player, x, y);
        // output and serialize to player_#.result.json;
        string result = to_string(eval);
        string fname = "player_" + to_string(player) + ".result.json";
        ofstream writeFile(fname);
        cereal::JSONOutputArchive out_arch(writeFile);
        out_arch(cereal::make_nvp("result",eval));

        writeFile.flush();

        in_shot_file.close();
        // delete the shot file HERE
        remove((fname_in).c_str());
        return SHOT_FILE_PROCESSED;
    }

    return NO_SHOT_FILE;
}

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
#include "Client.hpp"

Client::~Client() {
}


void Client::initialize(unsigned int player, unsigned int board_size){
    // save the player and board size
    this->player = player;
    this->board_size = board_size;

    // create and initialize the action board
    ofstream writeFile("player_"+ to_string(player)+".action_board.json"); // start write file
    cereal::JSONOutputArchive archive(writeFile); // create output archive to write file
    vector<vector<int>> board(board_size); // make a 2D vector for the board
    for(int i = 0;  i < board_size; i++) { // initialize all positions in the board to 0
        board[i] = vector<int>(board_size);
        for(int j = 0; j<board_size; j++) {
            board[i][j] = 0;
        }
    }
    archive(CEREAL_NVP(board)); // write from the archive to the file

    //writeFile.close();
    initialized = true;
}


void Client::fire(unsigned int x, unsigned int y) {
    ofstream writeFile("player_"+ to_string(this->player)+".shot.json"); // setup the output file
    cereal::JSONOutputArchive archive(writeFile); // create an output archive that writes to the file

    archive(CEREAL_NVP(x), CEREAL_NVP(y)); // write the shot coordinates to the output file
}


bool Client::result_available() {
    // check if the result file is available
    string fileName = "player_" + to_string(this->player) + ".result.json";
    ifstream inf(fileName);
    return inf.good();
}


int Client::get_result() {
    // if the result exists, parse it and return the information
    if(result_available()) {
        int res;
        // setup the input file and an archive to read it
        string fname = "player_" + to_string(this->player) + ".result.json";
        ifstream in_result_ifs(fname);
        cereal::JSONInputArchive result_in(in_result_ifs);
        result_in(res);

        remove((fname).c_str());

        if( res >= -1 && res <= 1) {
            return res;
        } else {
            throw ClientException("Unable to get the result");
        }
    }
    else {
        throw ClientException("No results to get");
    }
}



void Client::update_action_board(int result, unsigned int x, unsigned int y) {
    //cout << "Updating the action board" << endl;
    string fname = "player_" + to_string(this->player) + ".action_board.json";
    ifstream in_action_board(fname); // init and open
    vector<vector<int>> board(board_size);
    {
        cereal::JSONInputArchive action_in(in_action_board); // setup archive to read in the file
        action_in(CEREAL_NVP(board)); // read in from the archive
    }
    //cout << "Read in the action board" << endl;
    board[x][y] = result; // update value
    in_action_board.close(); // close input stream
    ofstream out_action_board(fname); // open output stream
    {
        cereal::JSONOutputArchive action_out(out_action_board); // setup archive to write out
        action_out(CEREAL_NVP(board)); // use archive to write out updated board
    }
    out_action_board.close();

}


string Client::render_action_board(){
    string res = "\n"; // start string to return
    string fname = "player_" + to_string(this->player) + ".action_board.json";
    ifstream in_action_board(fname);
    vector<vector<int>> board(board_size);
    { // read in file through the JSON archive
        cereal::JSONInputArchive action_in(in_action_board);
        action_in(CEREAL_NVP(board));
    }
    // iterate through the board and add it to the string that will be returned
    for(int i=0; i < board_size; i++) {
        for(int j=0; j < board_size; j++) {
            res += to_string(board[i][j]);
        }
        res += "\n";
    }

    return res;
}
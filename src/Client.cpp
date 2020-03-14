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
    stored_player = player;

    ofstream writeFile("player_"+ to_string(player)+".action_board.json");
    cereal::JSONOutputArchive archive(writeFile);
    vector<vector<int>> board(board_size);
    for(int i = 0;  i < board_size; i++) {
        board[i] = vector<int>(board_size);
        for(int j = 0; j<board_size; j++) {
            board[i][j] = 0;
        }
    }
    archive(CEREAL_NVP(board));

    //writeFile.close();
    initialized = true;
}


void Client::fire(unsigned int x, unsigned int y) {
    //string temp =("player_"+ to_string(stored_player)+".shot.json");
    //cout << temp << endl;
    ofstream writeFile("player_"+ to_string(stored_player)+".shot.json");
    cereal::JSONOutputArchive archive(writeFile);

    archive(CEREAL_NVP(x), CEREAL_NVP(y));

}


bool Client::result_available() {
    string fileName = "player_" + to_string(stored_player) + ".result.json";
    ifstream inf(fileName);
    return inf.good();
}


int Client::get_result() {

}



void Client::update_action_board(int result, unsigned int x, unsigned int y) {
}


string Client::render_action_board(){
}
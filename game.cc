#include "game.h"
#include <player.h>
#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <fstream>
#include <block.h>
using namespace std;


Game::Game(std::vector<Player>& players, CommandLineInterpreter& CI):
    players{players}, turn{0}, CI{CI}, numTotalMoves{0} {}


void Game::switchPlayer(){
    turn = 
    // handles turn switching logic
    ++numTotalMoves; //?
}
pair<int, string> Game::getUserCmd(){

}
void Game::executeCmd(string cmd){
    if (cmd == "left") {
        players[turn].moveLeft();
    } else if (cmd == "right") {
        players[turn].moveRight();
    } else if (cmd == "down") {
        players[turn].moveDown();
    } else if (cmd == "clockwise") {
        players[turn].rotateCW();
    } else if (cmd == "counterclockwise") {
        players[turn].rotateCCW();
    } else if (cmd == "drop") {
        players[turn].drop();
    } else if (cmd == "levelup") {
        players[turn].levelUp();
    } else if (cmd == "leveldown") {
        players[turn].levelDown();
    } else if (cmd == "norandom") {
        players[turn].noRandom();
    } else if (cmd == "random") {
        players[turn].makeLevelRandom();
    } else if (cmd.substr(0, 8) == "sequence") {
        string s;
        ifstream f{cmd.substr(9)};
        while(f >> s){
            executeCmd(s);
        }
    } else if (cmd == "restart") {
    } else if (cmd == "I" || cmd == "J" || cmd == "L" || 
               cmd == "O" || cmd == "S" || cmd == "T" || cmd == "Z") {
        players[turn].setCurrentBlock(cmd);
    } else if(cmd ==""){
        //EOF
    } else {
        std::cout << "Invalid command" << "\n";
    }
}

void Game::updateDisplay(){

}

GameState Game::getGameState() {
    return {
        .players = players,
        .turn = turn,
        .numTotalMoves = numTotalMoves
    };
}

//start game   //note: prefix for non prefix commands need to be filtered out in CI
void Game::startGame(){
    while(1){
        pair<int, string> cmdPair = getUserCmd();
        for(int i = 0; i < cmdPair.first; ++i){
            executeCmd(cmdPair.second);
        }
    }
}

int main(){
    //initialize everything and put it to game
    Game g {};
    g.startGame();
    // maybe play again feature here?
}
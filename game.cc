#include "game.h"
#include "command_interpreter.h"
#include <player.h>
#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <fstream>
#include <block.h>
using namespace std;


Game::Game(std::vector<std::unique_ptr<Player>>& players, CommandInterpreter& CI):
    players{players}, highScores{{0, 0}}, turn{0}, isGameOver{false}, CI{CI}, numTotalMoves{0} {}

void Game::switchPlayer(){
    //after turn ends, generate new current turn player's block and switch turn
    turn = !turn;
    ++numTotalMoves;
}
pair<int, string> Game::getUserCmd(){
    return CI.getUserCmd(cin);
}
void Game::executeCmd(string cmd){
    if (cmd == "left") {
        players[turn]->moveLeft();
    } else if (cmd == "right") {
        players[turn]->moveRight();
    } else if (cmd == "down") {
        players[turn]->moveDown();
    } else if (cmd == "clockwise") {
        players[turn]->rotateCW();
    } else if (cmd == "counterclockwise") {
        players[turn]->rotateCCW();
    } else if (cmd == "drop") {
        bool canDrop = players[turn]->drop();
        if(!canDrop){
            endGame();
        }
    } else if (cmd == "levelup") {
        players[turn]->levelUp();
    } else if (cmd == "leveldown") {
        players[turn]->levelDown();
    } else if (cmd == "norandom") {
        players[turn]->noRandom();
    } else if (cmd == "random") {
        players[turn]->makeLevelRandom();
    } else if (cmd.substr(0, 8) == "sequence") {
        string s;
        ifstream f{cmd.substr(9)};
        while(f >> s){
            executeCmd(s);
        }
    } else if (cmd == "restart") {
        restartGame();
    } else if (cmd == "I" || cmd == "J" || cmd == "L" || 
               cmd == "O" || cmd == "S" || cmd == "T" || cmd == "Z") {
        players[turn]->setCurrentBlock(cmd[0]);
    } else if(cmd ==""){
        isGameOver = true;
    } else {
        std::cout << "Invalid command" << "\n";
    }
}

void Game::updateDisplay(){
    notifyObservers();
}

//start game   //note: prefix for non prefix commands need to be filtered out in CI
void Game::startGame(){
    while(!isGameOver){ //while game continues
        bool endTurn = false;
        while(!endTurn){ //next player's turn if drop
            pair<int, string> cmdPair = getUserCmd();
            for(int i = 0; i < cmdPair.first; ++i){
                executeCmd(cmdPair.second);
            }
            endTurn = "drop" == cmdPair.second || "" == cmdPair.second;
        }
    } 
    endProgram();
}

void Game::restartGame() {
    players.clear(); //hope this frees the previous pts...
    players.push_back(std::make_unique<Player>());
    players.push_back(std::make_unique<Player>());
    turn = 0;
    isGameOver = false;
    numTotalMoves = 0;
}

void Game::endGame(){
    cout << "run it back?" << endl;
    while(1){
        pair<int, string> cmdPair = getUserCmd();
        string cmd = cmdPair.second;
        if(cmd == "restart") restartGame();
        else if(cmd == "") endProgram();
    }
}

void Game::endProgram(){
    // anything that needs to be run when game is over
    exit(0);
}

int main(){
    //initialize everything and put it to game
    
    CommandInterpreter CI;
    // Create the list of players
    std::vector<std::unique_ptr<Player>> players;
    players.push_back(std::make_unique<Player>());
    players.push_back(std::make_unique<Player>());

    // Initialize the game
    Game g {players, CI};

    g.startGame();
    // maybe play again feature here?
}


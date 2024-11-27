#include "game.h"
#include "command_interpreter.h"
#include "player.h"
#include <cstdlib>
#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <fstream>
#include "block.h"
#include "text_display.h"
#include <fstream>

using namespace std;

int main(int argc, char* argv[]){
    //initialize everything and put it to game
    // Default values for options
    bool textOnly = false;
    int seed = 0;               // Default seed
    std::string scriptFile1 = "sequence1.txt";
    std::string scriptFile2 = "sequence2.txt";
    int startLevel = 0;

  for (int i = 1; i < argc; ++i) { // Start from 1 to skip the program name
        std::string arg = argv[i];

        if (arg == "-text") {
            textOnly = true;
        } else if (arg == "-seed") {
            if (i + 1 < argc) { // Check if a value follows
                try {
                    seed = std::stoi(argv[++i]);
                } catch (const std::invalid_argument&) {
                    std::cerr << "Error: Invalid value for --seed, must be an integer. Using Default" << std::endl;
                    seed = 0;
                }
            } else {
                std::cerr << "Warning: No value provided for -seed. Using default." << std::endl;
                seed = 0;
            }
        } else if (arg == "-scriptfile1") {
            if (i + 1 < argc) {
                scriptFile1 = argv[++i];
                std::ifstream file(scriptFile1);
                if(!file.good()) {
                    std::cerr << "Warning: File " << scriptFile1 << " does not exist. Using default." << std::endl;
                    scriptFile1 = "sequence1.txt";
                }
            } else {
                std::cerr << "Warning: No value provided for -scriptfile1. Using default." << std::endl;
                scriptFile1 = "sequence1.txt";
            }
        } else if (arg == "-scriptfile2") {
            if (i + 1 < argc) {
                scriptFile2 = argv[++i];
                std::ifstream file(scriptFile2);
                if(!file.good()) {
                    std::cerr << "Warning: File " << scriptFile2 << " does not exist. Using default." << std::endl;
                    scriptFile2 = "sequence2.txt";
                }
            } else {
                std::cerr << "Warning: No value provided for -scriptfile2. Using default." << std::endl;
                scriptFile2 = "sequence2.txt";
            }
        } else if (arg == "-startlevel") {
            if (i + 1 < argc) {
                try {
                    startLevel = std::stoi(argv[++i]);
                    if(startLevel > 4 || startLevel < 0) {
                        std::cerr << "Warning: this level is not available. Using default." << std::endl;
                        startLevel = 0;
                    }
                } catch (const std::invalid_argument&) {
                    std::cerr << "Error: Invalid value for -startlevel, must be an integer. Using Default" << std::endl;
                    startLevel = 0;
                }
            } else {
                std::cerr << "Warning: No value provided for -startlevel. Using default." << std::endl;
                startLevel = 0; // or some default value
            }
        } else {
            std::cerr << "Unknown option: " << arg << std::endl;
        }
    }
    

    CommandInterpreter CI;
    // Create the list of players
    std::vector<std::unique_ptr<Player>> players;
    players.push_back(std::make_unique<Player>(scriptFile1, startLevel, seed));
    players.push_back(std::make_unique<Player>(scriptFile2, startLevel, seed));

    // Initialize the game - note the std::move
    Game g{std::move(players), CI};

    TextDisplay display(g);
    g.attach(&display);

    g.startGame();


}
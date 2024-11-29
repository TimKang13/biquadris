#include "command_interpreter.h"
#include <vector>
#include <iostream>
#include <string>
#include <utility>
#include <sstream>
#include <fstream>
using namespace std;

CommandInterpreter::CommandInterpreter(){
    // using a map format to accomodate for renaming commands
    useCmdLine = false;
    commands = {{"left", "left"},
            {"right", "right"},
            {"down", "down"},
            {"drop", "drop"},
            {"clockwise", "clockwise"},
            {"counterclockwise", "counterclockwise"},
            {"levelup", "levelup"},
            {"leveldown", "leveldown"},
            {"norandom", "norandom"},
            {"random", "random"},
            {"restart", "restart"},
            {"sequence", "sequence"},
            {"rename", "rename"}
    };
    specialActions = {{"heavy", "heavy"}, {"blind", "blind"}, {"force", "force"}};
}

std::pair<int, std::string> CommandInterpreter::getUserCmd(std::istream& input) {
    if(!useCmdLine) {
        while(count < sequence.size()) {
            std::istringstream iss{sequence[count]};
            std::string word;
            iss >> word;
            commandToReturn = separateNumber(sequence[count]);
            if(isValid()) {
                if(commandToReturn.second == "sequence" || commandToReturn.second == "norandom") {
                    std::string file;
                    iss >> file;
                    commandToReturn.second = commandToReturn.second +  " " + file;
                }
                if(commandToReturn.second == "rename") {
                    std::string oldName;
                    std::string newName;
                    iss >> oldName >> newName;
                    rename(oldName, newName);
                    count++;
                    continue;
                }
                updateNum();
                count++;
                return commandToReturn;
            }
            count++;
        }
        useCmdLine = true;
    }
    
    std::string line;
    // get a valid command
    while(std::getline(input, line)) {
        
        std::istringstream iss{line};
        std::string word;
        iss >> word;
        commandToReturn = separateNumber(word);
        if(!isValid()) {
            std::cerr << "Please enter a valid command: ";
            commandToReturn.first = 0;
            commandToReturn.second = "";
            continue;
        } 
        if(commandToReturn.second == "sequence" || commandToReturn.second == "norandom") {
            std::string file;
            iss >> file;
            commandToReturn.second = commandToReturn.second +  " " + file;
        }
        if(commandToReturn.second == "rename") {
            std::string oldName;
            std::string newName;
            iss >> oldName >> newName;
            rename(oldName, newName);
            continue;
        }

        break;
    } 
    
    updateNum();
    return commandToReturn;
    
}

std::string CommandInterpreter::getSpecialAction(std::istream& in) {
    std::string line;
    std::cout << "Please enter a special action (force/heavy/blind): ";

    while (std::getline(in, line)) {
        std::istringstream iss{line};
        std::string action, type;
        iss >> action;

        // Check if the action is valid
        auto it = specialActions.find(action);
        if (it != specialActions.end()) {
            if (it->second == "force") {
                // Expect a type argument after "force"
                if (iss >> type && (type == "L" || type == "Z" || type == "O" || type == "L" || type == "I" || type == "J" || type == "T")) {

                    return it->second + " " + type;
                } else {
                    std::cout << "Invalid or missing type for 'force'. Please try again.\n";
                    continue;
                }
            }
            // For "heavy" or "blind", no additional input is required
            return it->second;
        }

        std::cout << "Invalid action. Please try again.\n";
    }

    return ""; // Return an empty string if no valid input is provided
}
// changes any numbers greater than one to one for commands that shouldn't be run more than once
void CommandInterpreter::updateNum() {
    if(commandToReturn.first == 0) return;
    if(commandToReturn.second != "left" && commandToReturn.second != "right" && commandToReturn.second != "down" && commandToReturn.second != "drop" 
    && commandToReturn.second != "levelup" && commandToReturn.second != "leveldown" && commandToReturn.second != "clockwise" && commandToReturn.second != "right") {
        commandToReturn.first = 1;
    }
}
// checks if the command is valid, changes the command in std::pair commandToReturn to the actual command
bool CommandInterpreter::isValid() {
    if(commandToReturn.first < 0) {return false;}
    string temp = commandToReturn.second;
    if(temp == "I" || temp == "J" || temp == "S" || temp == "L" || temp == "O" || temp == "Z" || temp == "T") return true;
    std::vector<std::string> commandValues = getCommandValue(temp); // all command values that match the substring
    if(commandValues.size() == 1) {
        commandToReturn.second = commandValues[0];
        return true;
    }

    return false;
}

// get all commands values in the commands map that match the substring
std::vector<std::string> CommandInterpreter::getCommandValue(std::string substring) {
    std::vector<std::string> temp;
    // go through the entire map
    for (auto& p : commands) {
        if(p.first.length() >= substring.length() && substring == p.first.substr(0,substring.length())) {
            if(substring == p.first) {
                std::vector<std::string> temp1 = {{p.second}};
                return temp1;
            }
            temp.emplace_back(p.second);
        }
    }
    return temp;
}

// separtes numbers and letters from a string
std::pair<int, std::string> CommandInterpreter::separateNumber(std::string word) {
    size_t pos = 0; // To track where the numeric part ends
    int number = 0;

    try {
        // Attempt to convert the leading numeric part to an integer
        number = std::stoi(word, &pos);
    } catch (const std::invalid_argument&) {
        // If no numeric part exists, std::stoi will throw
        number = 1;
    }

    // Extract the remaining string starting from pos
    std::string letters = word.substr(pos);
    return {number, letters};
}

// rename a certain command or special action, if that name doesn't exist, do nothing
void CommandInterpreter::rename(std::string oldName, std::string newName) {
    // rename a command
    auto it = commands.find(oldName);
    if (it != commands.end()) {
        std::string value = it->second;
        commands.erase(it);
        commands.insert({newName, value});
        return;
    }
    //rename special action 
    it = specialActions.find(oldName);
    if (it != specialActions.end()) {
        std::string value = it->second;
        specialActions.erase(it);
        specialActions.insert({newName, value});
    }
}

void CommandInterpreter::setSequence(string file) {
    ifstream f{file};
    if(!f.good()) {
        std::cerr << "File does not exist" << std::endl;
        return;
    }
    string line;
    while(f >> line) {
        sequence.emplace_back(line);
    }
    useCmdLine = false;
    count = 0;
}
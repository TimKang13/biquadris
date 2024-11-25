#ifndef COMMANDINTERPRETER_H
#define COMMANDINTERPRETER_H
#include <string>
#include <vector>
#include <map>

class CommandInterpreter {
    std::map<std::string, std::string> commands;
    std::vector<std::string> macros; // to be implemented later, not sure how macro works yet
    std::pair<int, std::string> commandToReturn;
    std::pair<int, std::string> separateNumber(std::string word);
    bool isValid();
    void updateNum();
    std::vector<std::string> getCommandValue(std::string temp);
    void rename(std::string oldName, std::string newName);
    public:
        CommandInterpreter();
        std::pair<int, std::string> getUserCmd(std::istream& input);
};

#endif

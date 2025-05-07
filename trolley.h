#ifndef TROLLEY_H
#define TROLLEY_H

#include <vector>
#include <string>
#include <map>
#include <set>

enum class Command {
    CREATE_TRL,
    TRL_IN_STOP,
    STOPS_IN_TRL,
    TRLS
};

void processCommand(const std::string& input);
void createTrolley(const std::vector<std::string>& args);
void trolleysInStop(const std::vector<std::string>& args);
void stopsInTrolley(const std::vector<std::string>& args);
void listAllTrolleys();

#endif
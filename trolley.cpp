#include "trolley.h"
#include <iostream>
#include <sstream>

using namespace std;

static map<string, vector<string>> trolleys;
static map<string, set<string>> stops;

void processCommand(const string& input) {
    istringstream iss(input);
    vector<string> args;
    string arg;
    
    while (iss >> arg) {
        args.push_back(arg);
    }
    
    if (args.empty()) return;
    
    string command = args[0];
    args.erase(args.begin());
    
    if (command == "CREATE_TRL") {
        createTrolley(args);
    } else if (command == "TRL_IN_STOP") {
        trolleysInStop(args);
    } else if (command == "STOPS_IN_TRL") {
        stopsInTrolley(args);
    } else if (command == "TRLS") {
        listAllTrolleys();
    } else {
        cerr << "Unknown command: " << command << endl;
    }
}

void createTrolley(const vector<string>& args) {
    if (args.size() < 2) {
        cerr << "Incorrect CREATE_TRL command format" << endl;
        return;
    }
    
    string trolleyNum = args[0];
    vector<string> stopsList(args.begin() + 1, args.end());
    
    if (trolleys.find(trolleyNum) != trolleys.end()) {
        for (const auto& stop : trolleys[trolleyNum]) {
            stops[stop].erase(trolleyNum);
        }
    }
    
    trolleys[trolleyNum] = stopsList;
    for (const auto& stop : stopsList) {
        stops[stop].insert(trolleyNum);
    }
}

void trolleysInStop(const vector<string>& args) {
    if (args.empty()) {
        cerr << "Incorrect TRL_IN_STOP command format" << endl;
        return;
    }
    
    string stop = args[0];
    
    if (stops.find(stop) == stops.end() || stops[stop].empty()) {
        cout << "Trolleys is absent" << endl;
        return;
    }
    
    for (const auto& tr : stops[stop]) {
        cout << tr << " ";
    }
    cout << endl;
}

void stopsInTrolley(const vector<string>& args) {
    if (args.empty()) {
        cerr << "Incorrect STOPS_IN_TRL command format" << endl;
        return;
    }
    
    string trolleyNum = args[0];
    
    if (trolleys.find(trolleyNum) == trolleys.end()) {
        cout << "Stops is absent" << endl;
        return;
    }
    
    for (const auto& stop : trolleys[trolleyNum]) {
        cout << "Stop " << stop << ": ";
        if (stops[stop].size() <= 1) {
            cout << "0";
        } else {
            bool first = true;
            for (const auto& tr : stops[stop]) {
                if (tr != trolleyNum) {
                    if (!first) cout << " ";
                    cout << tr;
                    first = false;
                }
            }
        }
        cout << endl;
    }
}

void listAllTrolleys() {
    if (trolleys.empty()) {
        cout << "Trolleys is absent" << endl;
        return;
    }
    
    for (const auto& [trolley, stopsList] : trolleys) {
        cout << "TROLLEY " << trolley << ": ";
        for (const auto& stop : stopsList) {
            cout << stop << " ";
        }
        cout << endl;
    }
}
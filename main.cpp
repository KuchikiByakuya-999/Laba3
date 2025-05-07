#include "trolley.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    string line;
    
    cout << "Trolley management system. Enter commands (CREATE_TRL, TRL_IN_STOP, STOPS_IN_TRL, TRLS)" << endl;
    cout << "Enter 'exit' to quit" << endl;
    
    while (true) {
        cout << ">>> ";
        getline(cin, line);
        
        if (line == "exit") {
            break;
        }
        
        processCommand(line);
    }
    
    return 0;
}
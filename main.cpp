#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Visitor {
    string ticket;
    int duration;
};

void distributeQueue(int windows, vector<Visitor>& visitors) {
    vector<vector<Visitor>> windowQueues(windows);
    vector<int> windowTimes(windows, 0);
    
    sort(visitors.begin(), visitors.end(), [](const Visitor& a, const Visitor& b) {
        return a.duration > b.duration;
    });

    for (const auto& visitor : visitors) {
        auto min_it = min_element(windowTimes.begin(), windowTimes.end());
        int min_index = distance(windowTimes.begin(), min_it);
        
        windowQueues[min_index].push_back(visitor);
        windowTimes[min_index] += visitor.duration;
    }
    
    for (int i = 0; i < windows; ++i) {
        cout << "Окно " << i + 1 << " (" << windowTimes[i] << " минут): ";
        for (size_t j = 0; j < windowQueues[i].size(); ++j) {
            cout << windowQueues[i][j].ticket;
            if (j != windowQueues[i].size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

int main() {
    int windows;
    cout << ">>> Введите кол-во окон" << endl;
    cout << "<<< ";
    cin >> windows;
    
    vector<Visitor> visitors;
    string command;
    
    while (true) {
        cout << "<<< ";
        cin >> command;
        
        if (command == "ENQUEUE") {
            int duration;
            cin >> duration;
            
            string ticket = "T" + to_string(rand() % 900 + 100);
            visitors.push_back({ticket, duration});
            
            cout << ">>> " << ticket << endl;
        } else if (command == "DISTRIBUTE") {
            distributeQueue(windows, visitors);
            break;
        } else {
            cout << ">>> Неизвестная команда" << endl;
        }
    }
    
    return 0;
}
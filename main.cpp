#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>


using namespace std;

map<string, set<string>> friends;

void addFriend(const string& i, const string& j) {
    friends[i].insert(j);
    friends[j].insert(i);
}

int friendCount(const string& i) {
    return friends[i].size();
}

bool questionFriend(const string& i, const string& j) {
    return friends[i].count(j) > 0;
}

int main() {
    int N;
    cout << "Введите кол-во операций: ";
    cin >> N;
    
    vector<string> outputs;
    
    for (int k = 1; k <= N; ++k) {
        string command;
        cin >> command;
        
        if (command == "FRIENDS") {
            string i, j;
            cin >> i >> j;
            addFriend(i, j);
        }
        else if (command == "COUNT") {
            string i;
            cin >> i;
            int count = friendCount(i);
            outputs.push_back(to_string(count));
        }
        else if (command == "QUESTION") {
            string i, j;
            cin >> i >> j;
            bool result = questionFriend(i, j);
            outputs.push_back(result ? "YES" : "NO");
        }
    }
    
    for (const auto& output : outputs) {
        cout << output << endl;
    }
    
    return 0;
}
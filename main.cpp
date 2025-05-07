#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

struct Cell {
    string address;
    map<string, int> goods;
};

vector<Cell> cells;
int totalCapacity;
int usedCapacity = 0;
map<char, int> zoneCapacity;
map<char, int> zoneUsed;

void initializeWarehouse(int zones, int racks, int sections, int shelves) {
    totalCapacity = zones * racks * sections * shelves * 10;
    char letters[] = {'А', 'Б', 'В'};
    
    for (int i = 0; i < zones; i++) {
        char zone = letters[i];
        zoneCapacity[zone] = racks * sections * shelves * 10;
        zoneUsed[zone] = 0;
        
        for (int rack = 1; rack <= racks; rack++) {
            for (int section = 1; section <= sections; section++) {
                for (int shelf = 1; shelf <= shelves; shelf++) {
                    string address;
                    address += zone;
                    address += to_string(rack);
                    address += to_string(section);
                    address += to_string(shelf);
                    cells.push_back({address, {}});
                }
            }
        }
    }
}

bool addGoods(const string& name, int quantity, const string& address, string& message) {
    for (auto& cell : cells) {
        if (cell.address == address) {
            int currentQuantity = 0;
            for (const auto& item : cell.goods) {
                currentQuantity += item.second;
            }
            
            if (currentQuantity + quantity > 10) {
                message = "Ошибка: невозможно добавить " + to_string(quantity) + 
                          " единиц товара '" + name + "' в ячейку " + address + 
                          ". Превышена вместимость ячейки.";
                return false;
            }
            
            cell.goods[name] += quantity;
            usedCapacity += quantity;
            zoneUsed[address[0]] += quantity;
            message = "Товар успешно добавлен";
            return true;
        }
    }
    message = "Ошибка: ячейка с адресом " + address + " не найдена.";
    return false;
}

bool removeGoods(const string& name, int quantity, const string& address, string& message) {
    for (auto& cell : cells) {
        if (cell.address == address) {
            if (cell.goods.find(name) == cell.goods.end() || cell.goods[name] < quantity) {
                message = "Ошибка: невозможно удалить " + to_string(quantity) + 
                          " единиц товара '" + name + "' из ячейки " + address + 
                          ". Недостаточно товара.";
                return false;
            }
            
            cell.goods[name] -= quantity;
            usedCapacity -= quantity;
            zoneUsed[address[0]] -= quantity;
            
            if (cell.goods[name] == 0) {
                cell.goods.erase(name);
            }
            message = "Товар успешно удален";
            return true;
        }
    }
    message = "Ошибка: ячейка с адресом " + address + " не найдена.";
    return false;
}

string getWarehouseInfo() {
    string info;
    double totalPercent = (static_cast<double>(usedCapacity) / totalCapacity) * 100;
    info = "Общая загруженность склада: " + to_string(totalPercent).substr(0, 5) + "%\n";
    
    info += "Загруженность по зонам:\n";
    for (const auto& zone : zoneCapacity) {
        double zonePercent = (static_cast<double>(zoneUsed[zone.first]) / zone.second) * 100;
        info += "Зона " + string(1, zone.first) + ": " + to_string(zonePercent).substr(0, 5) + "%\n";
    }
    
    info += "\nСодержимое ячеек:\n";
    vector<string> emptyCells;
    for (const auto& cell : cells) {
        if (cell.goods.empty()) {
            emptyCells.push_back(cell.address);
        } else {
            info += "Ячейка " + cell.address + ": ";
            for (const auto& item : cell.goods) {
                info += item.first + " (" + to_string(item.second) + "), ";
            }
            info += "\n";
        }
    }
    
    info += "\nПустые ячейки: ";
    if (emptyCells.empty()) {
        info += "отсутствуют";
    } else {
        for (const auto& addr : emptyCells) {
            info += addr + ", ";
        }
    }
    info += "\n";
    
    return info;
}

int main() {
    // Инициализация склада: 3 зоны (А, Б, В), 20 стеллажей, 5 секций, 2 полки
    initializeWarehouse(3, 20, 5, 2);
    
    cout << "Добро пожаловать в систему учета товаров на складе!" << endl;
    cout << "Доступные команды: ADD, REMOVE, INFO, EXIT" << endl;
    
    while (true) {
        cout << ">>> ";
        string command;
        cin >> command;
        
        if (command == "EXIT") {
            break;
        } else if (command == "ADD") {
            string name, address;
            int quantity;
            cin >> name >> quantity >> address;
            
            string message;
            addGoods(name, quantity, address, message);
            cout << message << endl;
        } else if (command == "REMOVE") {
            string name, address;
            int quantity;
            cin >> name >> quantity >> address;
            
            string message;
            removeGoods(name, quantity, address, message);
            cout << message << endl;
        } else if (command == "INFO") {
            string info = getWarehouseInfo();
            cout << info;
        } else {
            cout << "Неизвестная команда. Попробуйте снова." << endl;
        }
    }
    
    return 0;
}
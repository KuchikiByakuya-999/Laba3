package first.javaFirst;
import java.util.*;

class Cell {
    String address;
    Map<String, Integer> goods = new HashMap<>();

    public Cell(String address) {
        this.address = address;
    }
}

class Warehouse {
    private List<Cell> cells = new ArrayList<>();
    private int totalCapacity;
    private int usedCapacity = 0;
    private Map<Character, Integer> zoneCapacity = new HashMap<>();
    private Map<Character, Integer> zoneUsed = new HashMap<>();
    
    public Warehouse(int zones, int racks, int sections, int shelves) {
        totalCapacity = zones * racks * sections * shelves * 10;
        
        for (char zone = 'А'; zone < 'А' + zones; zone++) {
            zoneCapacity.put(zone, racks * sections * shelves * 10);
            zoneUsed.put(zone, 0);
            
            for (int rack = 1; rack <= racks; rack++) {
                for (int section = 1; section <= sections; section++) {
                    for (int shelf = 1; shelf <= shelves; shelf++) {
                        String address = "" + zone + rack + section + shelf;
                        cells.add(new Cell(address));
                    }
                }
            }
        }
    }
    
    public String addGoods(String name, int quantity, String address) {
        for (Cell cell : cells) {
            if (cell.address.equals(address)) {
                int currentQuantity = cell.goods.values().stream().mapToInt(Integer::intValue).sum();
                
                if (currentQuantity + quantity > 10) {
                    return String.format("Ошибка: невозможно добавить %d единиц товара '%s' в ячейку %s. Превышена вместимость ячейки.", 
                                     quantity, name, address);
                }
                
                cell.goods.put(name, cell.goods.getOrDefault(name, 0) + quantity);
                usedCapacity += quantity;
                zoneUsed.put(address.charAt(0), zoneUsed.get(address.charAt(0)) + quantity);
                return "Товар успешно добавлен";
            }
        }
        return String.format("Ошибка: ячейка с адресом %s не найдена.", address);
    }
    
    public String removeGoods(String name, int quantity, String address) {
        for (Cell cell : cells) {
            if (cell.address.equals(address)) {
                if (!cell.goods.containsKey(name) || cell.goods.get(name) < quantity) {
                    return String.format("Ошибка: невозможно удалить %d единиц товара '%s' из ячейки %s. Недостаточно товара.", 
                                     quantity, name, address);
                }
                
                cell.goods.put(name, cell.goods.get(name) - quantity);
                usedCapacity -= quantity;
                zoneUsed.put(address.charAt(0), zoneUsed.get(address.charAt(0)) - quantity);
                
                if (cell.goods.get(name) == 0) {
                    cell.goods.remove(name);
                }
                return "Товар успешно удален";
            }
        }
        return String.format("Ошибка: ячейка с адресом %s не найдена.", address);
    }
    
    public String getInfo() {
        StringBuilder info = new StringBuilder();
        double totalPercent = (double) usedCapacity / totalCapacity * 100;
        info.append(String.format("Общая загруженность склада: %.2f%%%n", totalPercent));
        
        info.append("Загруженность по зонам:\n");
        for (char zone : zoneCapacity.keySet()) {
            double zonePercent = (double) zoneUsed.get(zone) / zoneCapacity.get(zone) * 100;
            info.append(String.format("Зона %c: %.2f%%%n", zone, zonePercent));
        }
        
        info.append("\nСодержимое ячеек:\n");
        List<String> emptyCells = new ArrayList<>();
        for (Cell cell : cells) {
            if (cell.goods.isEmpty()) {
                emptyCells.add(cell.address);
            } else {
                info.append("Ячейка ").append(cell.address).append(": ");
                for (Map.Entry<String, Integer> entry : cell.goods.entrySet()) {
                    info.append(entry.getKey()).append(" (").append(entry.getValue()).append("), ");
                }
                info.append("\n");
            }
        }
        
        info.append("\nПустые ячейки: ");
        if (emptyCells.isEmpty()) {
            info.append("отсутствуют");
        } else {
            for (String addr : emptyCells) {
                info.append(addr).append(", ");
            }
        }
        info.append("\n");
        
        return info.toString();
    }
}

public class main {
    public static void main(String[] args) {
        Warehouse warehouse = new Warehouse(3, 20, 5, 2);
        
        System.out.println("Добро пожаловать в систему учета товаров на складе!");
        System.out.println("Доступные команды: ADD, REMOVE, INFO, EXIT");
        
        Scanner scanner = new Scanner(System.in);
        while (true) {
            System.out.print(">>> ");
            String command = scanner.next();
            
            if (command.equals("EXIT")) {
                break;
            } else if (command.equals("ADD")) {
                String name = scanner.next();
                int quantity = scanner.nextInt();
                String address = scanner.next();
                System.out.println(warehouse.addGoods(name, quantity, address));
            } else if (command.equals("REMOVE")) {
                String name = scanner.next();
                int quantity = scanner.nextInt();
                String address = scanner.next();
                System.out.println(warehouse.removeGoods(name, quantity, address));
            } else if (command.equals("INFO")) {
                System.out.print(warehouse.getInfo());
            } else {
                System.out.println("Неизвестная команда. Попробуйте снова.");
            }
        }
        scanner.close();
    }
}
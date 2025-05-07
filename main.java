package secondJava; 

import java.util.*;

class Visitor {
    String ticket;
    int duration;
    
    public Visitor(String ticket, int duration) {
        this.ticket = ticket;
        this.duration = duration;
    }
}

public class main {
    public static void distributeQueue(int windows, List<Visitor> visitors) {
        List<List<Visitor>> windowQueues = new ArrayList<>();
        int[] windowTimes = new int[windows];
        
        for (int i = 0; i < windows; i++) {
            windowQueues.add(new ArrayList<>());
        }
        
        visitors.sort((a, b) -> Integer.compare(b.duration, a.duration));
        
        for (Visitor visitor : visitors) {
            int minIndex = 0;
            for (int i = 1; i < windows; i++) {
                if (windowTimes[i] < windowTimes[minIndex]) {
                    minIndex = i;
                }
            }
            
            windowQueues.get(minIndex).add(visitor);
            windowTimes[minIndex] += visitor.duration;
        }
        
        for (int i = 0; i < windows; i++) {
            System.out.print("Окно " + (i + 1) + " (" + windowTimes[i] + " минут): ");
            for (int j = 0; j < windowQueues.get(i).size(); j++) {
                System.out.print(windowQueues.get(i).get(j).ticket);
                if (j != windowQueues.get(i).size() - 1) {
                    System.out.print(", ");
                }
            }
            System.out.println();
        }
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println(">>> Введите кол-во окон");
        System.out.print("<<< ");
        int windows = scanner.nextInt();
        scanner.nextLine();
        
        List<Visitor> visitors = new ArrayList<>();
        Random random = new Random();
        
        while (true) {
            System.out.print("<<< ");
            String input = scanner.nextLine();
            String[] parts = input.split(" ");
            
            if (parts[0].equals("ENQUEUE")) {
                int duration = Integer.parseInt(parts[1]);
                
                String ticket = "T" + (random.nextInt(900) + 100);
                visitors.add(new Visitor(ticket, duration));
                
                System.out.println(">>> " + ticket);
            } else if (parts[0].equals("DISTRIBUTE")) {
                distributeQueue(windows, visitors);
                break;
            } else {
                System.out.println(">>> Неизвестная команда");
            }
        }
        
        scanner.close();
    }
}
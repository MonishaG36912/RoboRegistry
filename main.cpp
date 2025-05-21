#include <iostream>

#include "src/RobotRegistry.h"


int main() {
    RobotRegistry registry;
    bool running = true;
    bool menuShown = false;
    registry.displayGreeting();
    while (running) {
        if (!menuShown) {
            cout << "\n===== Robot Registry Menu =====\n";
            cout << "1. Load robots from file\n";
            cout << "2. Add a new robot\n";
            cout << "3. Display all robots\n";
            cout << "4. Show robots above a price\n";
            cout << "5. Display polymorphic robots\n";
            cout << "6. Menu\n";
            cout << "7. Exit\n";
            cout << "===============================\n";
            menuShown = true;
        }

        cout << "\nEnter your choice (6 to show menu): ";
        int choice;
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();                // Clear error state
            cin.ignore(1000, '\n');     // Discard the rest of the input line
            cout << "Invalid input. Please enter a number.\n";
            continue;                   // Restart loop
        }

        cin.ignore(); // Clear newline after number input

        switch (choice) {
            case 1: {
                string filename;
                cout << "Enter filename: ";
                getline(cin, filename);
                registry.readFromFile(filename);
                break;
            }
            case 2:
                registry.promptUserForRobot();
                break;
            case 3:
                registry.displayRobots();
                break;
          
            case 4: {
                double minPrice;
                cout << "Enter minimum price: ";
                cin >> minPrice;
                cin.ignore();
                auto filter = registry.getExpensiveRobotsFilter(minPrice);
                filter(); // call the lambda
                break;
            }
            case 5:
                registry.displayPolymorphicRobots();
                break;
            case 6:{
                cout << "\n===== Robot Registry Menu =====\n";
                cout << "1. Load robots from file\n";
                cout << "2. Add a new robot\n";
                cout << "3. Display all robots\n";
                cout << "4. Show robots above a price\n";
                cout << "5. Display polymorphic robots\n";
                cout << "6. Menu\n";
                cout << "7. Exit\n";
                cout << "===============================\n";
                break;
            }

            case 7:
                running = false;
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
                break;
        }
    }

    return 0;
}
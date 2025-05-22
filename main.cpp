#include <iostream>
#include <iomanip> // For std::setprecision and std::fixed
#include <string>
#include <map>

#include "src/RobotRegistry.h"

void printPriceSummary(const std::multimap<double, std::string>& companyPrices) {
    if (companyPrices.empty()) {
        std::cout << "No robots registered.\n";
        return;
    }

    // Since multimap is sorted by price (key), begin() is min, rbegin() is max
    auto minEntry = *companyPrices.begin();
    auto maxEntry = *companyPrices.rbegin();

    // Calculate mean
    double total = 0;
    for (const auto& entry : companyPrices) {
        total += entry.first;
    }
    double mean = total / companyPrices.size();

    // Print summary
    std::cout << "Price Summary:\n";
    std::cout << "Min Price: $" << std::fixed << std::setprecision(2) << minEntry.first
              << " (Company: " << minEntry.second << ")\n";
    std::cout << "Max Price: $" << maxEntry.first
              << " (Company: " << maxEntry.second << ")\n";
    std::cout << "Mean Price: $" << mean << "\n\n";

    // Print all sorted prices
    std::cout << "All Prices (sorted):\n";
    for (const auto& entry : companyPrices) {
        std::cout << "Price: $" << entry.first << ", Company: " << entry.second << "\n";
    }
}

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
                cout << "4. Summary of prize\n";
                cout << "5. Show robots above a price\n";
                cout << "6. Display polymorphic robots\n";
                cout << "7. Menu\n";
                cout << "8. Exit\n";
                cout << "===============================\n";
            menuShown = true;
        }

        cout << "\nEnter your choice (7 to show menu):";
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
                cout << "===============================\n";
                registry.readFromFile(filename);
                break;
            }
            case 2:
                registry.promptUserForRobot();
                break;
            case 3: {
                cout << "===============================\n";
                registry.displayRobots();
                break;
            }
            case 4: {
                auto prices = registry.getCompanyPrices();
                cout << "===============================\n";
                printPriceSummary(prices);
                break;
            }
          
            case 5: {
                double minPrice;
                cout << "Enter minimum price: ";
                cin >> minPrice;
                cin.ignore();
                cout << "===============================\n";
                auto filter = registry.getExpensiveRobotsFilter(minPrice);
                filter(); // call the lambda
                break;
            }
            case 6:
                registry.displayPolymorphicRobots();
                break;
            case 7:{
                cout << "\n===== Robot Registry Menu =====\n";
                cout << "1. Load robots from file\n";
                cout << "2. Add a new robot\n";
                cout << "3. Display all robots\n";
                cout << "4. Summary of prize\n";
                cout << "5. Show robots above a price\n";
                cout << "6. Display polymorphic robots\n";
                cout << "7. Menu\n";
                cout << "8. Exit\n";
                cout << "===============================\n";
                break;
            }

            case 8:
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
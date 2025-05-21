#include <iostream>
#include <string>
#include <cassert>
#include <utility>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <iostream>

#include "src/Robot.h"
#include "src/MilitaryRobot.h"
#include "src/IndustrialRobot.h"
#include "src/DomesticRobot.h"
#include "src/RobotComponent.h"

using namespace std;

// Functor for price validation
class PriceValidator {
public:
    bool operator()(double price) const {
        return price > 0.0;
    }
};

// Functor for string validation
class StringValidator {
public:
    bool operator()(const string& str) const {
        for (char ch : str) {
            if (!isalnum(ch) && ch != ' ') {
                return false;
            }
        }
        return !str.empty();
    }
};

// HumanoidRobot with composition
struct HumanoidRobot {
    string company;
    string name;
    string version;
    double price;
    RobotComponent* mainComponent;

    HumanoidRobot() : mainComponent(nullptr) {}

    HumanoidRobot(string comp, string n, string ver, double p, RobotComponent* compnt = nullptr)
        : company(move(comp)), name(move(n)), version(move(ver)), price(p), mainComponent(compnt) {}

    ~HumanoidRobot() {
        delete mainComponent;
    }

    HumanoidRobot(HumanoidRobot&& other) noexcept
        : company(move(other.company)), name(move(other.name)),
          version(move(other.version)), price(other.price),
          mainComponent(other.mainComponent) {
        other.mainComponent = nullptr;
    }

    HumanoidRobot& operator=(HumanoidRobot&& other) noexcept {
        if (this != &other) {
            company = move(other.company);
            name = move(other.name);
            version = move(other.version);
            price = other.price;
            delete mainComponent;
            mainComponent = other.mainComponent;
            other.mainComponent = nullptr;
        }
        return *this;
    }

    operator string() const {
        return company + " " + name + " v" + version + " ($" + to_string(price) + ")";
    }

    friend ostream& operator<<(ostream& os, const HumanoidRobot& hr) {
        os << "Company: " << hr.company << " | Name: " << hr.name
           << " | Version: " << hr.version << " | Price: $" << hr.price;
        if (hr.mainComponent) {
            os << " | Main Component: " << *hr.mainComponent;
        }
        return os;
    }
};

class RobotRegistry {
private:
    HumanoidRobot* robots;
    Robot** polymorphicRobots;
    int size;
    int polySize;
    int capacity;
    PriceValidator validatePrice;
    StringValidator validateString;

    void growArray() {
        capacity *= 2;
        HumanoidRobot* newRobots = new HumanoidRobot[capacity];
        for (int i = 0; i < size; i++) {
            newRobots[i] = move(robots[i]);
        }
        delete[] robots;
        robots = newRobots;
    }

    void computeColumnWidths(size_t& nameWidth, size_t& companyWidth, size_t& versionWidth) const {
        nameWidth = 5;
        companyWidth = 7;
        versionWidth = 7;
        for (int i = 0; i < size; i++) {
            nameWidth = max(nameWidth, robots[i].name.length());
            companyWidth = max(companyWidth, robots[i].company.length());
            versionWidth = max(versionWidth, robots[i].version.length());
        }
        nameWidth += 2;
        companyWidth += 2;
        versionWidth += 2;
    }

public:
    RobotRegistry() : size(0), polySize(0), capacity(2) {
        robots = new HumanoidRobot[capacity];
        polymorphicRobots = new Robot*[10];

        polymorphicRobots[polySize++] = new IndustrialRobot("IND-001", "Factory A", 50.5);
        polymorphicRobots[polySize++] = new DomesticRobot("DOM-001", "Home 1", "Cleaning");
        polymorphicRobots[polySize++] = new IndustrialRobot("IND-002", "Factory B", 75.0);
    }

    ~RobotRegistry() {
        delete[] robots;
        for (int i = 0; i < polySize; i++) {
            delete polymorphicRobots[i];
        }
        delete[] polymorphicRobots;
    }

    auto getExpensiveRobotsFilter(double minPrice) {
        return [this, minPrice]() {
            cout << "\nRobots above $" << minPrice << ":\n";
            for (int i = 0; i < size; i++) {
                if (robots[i].price >= minPrice) {
                    cout << robots[i] << endl;
                }
            }
        };
    }

    void addRobot(string&& company, string&& name, string&& version, double price, RobotComponent* component = nullptr) {
        if (!validatePrice(price)) {
            throw invalid_argument("Price must be positive.");
        }
        if (size == capacity) {
            growArray();
        }
        robots[size++] = HumanoidRobot(move(company), move(name), move(version), price, component);
    }

    void displayRobots() const {
        if (size == 0) {
            cout << "No robots registered yet.\n";
            return;
        }

        size_t nameWidth = 0, companyWidth = 0, versionWidth = 0;
        computeColumnWidths(nameWidth, companyWidth, versionWidth);
        const int priceWidth = 10;

        cout << "+" << string(companyWidth, '-') << "+"
             << string(nameWidth, '-') << "+"
             << string(versionWidth, '-') << "+"
             << string(priceWidth, '-') << "+\n";

        cout << "| " << "Company" << string(companyWidth - 8, ' ')
             << "| " << "Name" << string(nameWidth - 5, ' ')
             << "| " << "Version" << string(versionWidth - 8, ' ')
             << "| " << "Price" << " |\n";

        cout << "+" << string(companyWidth, '-') << "+"
             << string(nameWidth, '-') << "+"
             << string(versionWidth, '-') << "+"
             << string(priceWidth, '-') << "+\n";

        for (int i = 0; i < size; i++) {
            cout << "| " << robots[i].company
                 << string(companyWidth - robots[i].company.length() - 1, ' ')
                 << "| " << robots[i].name
                 << string(nameWidth - robots[i].name.length() - 1, ' ')
                 << "| " << robots[i].version
                 << string(versionWidth - robots[i].version.length() - 1, ' ')
                 << "| $" << fixed << setprecision(2) << robots[i].price
                 << string(priceWidth - to_string((int)robots[i].price).length() - 4, ' ')
                 << " |\n";
        }

        cout << "+" << string(companyWidth, '-') << "+"
             << string(nameWidth, '-') << "+"
             << string(versionWidth, '-') << "+"
             << string(priceWidth, '-') << "+\n";
    }

    void displayPolymorphicRobots() const {
        cout << "\nPolymorphic Robot Demonstrations:\n";
        for (int i = 0; i < polySize; i++) {
            polymorphicRobots[i]->performTask();
            cout << *polymorphicRobots[i] << endl;
        }
    }

    void redirectOutputToFile() {
        static ofstream file("output.txt");
        cout.rdbuf(file.rdbuf());  // Redirect std::cout to output.txt
    }

    void readFromFile(const string& filename) {
        ifstream input_file(filename);
        if (!input_file) {
            cerr << "Error: Unable to open file " << filename << endl;
            exit(EXIT_FAILURE);
        }

        string line;
        while (getline(input_file, line)) {
            if (line.find("Enter company name:") != string::npos) {
                string company = line.substr(line.find(":") + 2);

                getline(input_file, line); // robot name
                string name = line.substr(line.find(":") + 2);

                getline(input_file, line); // version
                string version = line.substr(line.find(":") + 2);

                getline(input_file, line); // price
                double price = stod(line.substr(line.find(":") + 2));

                getline(input_file, line); // Add a main component? (y/n)
                string addComponent = line.substr(line.find(":") + 2);
                string componentName;
                double componentWeight = 0.0;

                RobotComponent* component = nullptr;
                if (addComponent == "Y" || addComponent == "y") {
                    getline(input_file, line); // component name
                    componentName = line.substr(line.find(":") + 2);
                    getline(input_file, line); // component weight
                    componentWeight = stod(line.substr(line.find(":") + 2));
                    component = new RobotComponent(componentName, componentWeight);
                }

                addRobot(move(company), move(name), move(version), price, component);
            }
        }

        input_file.close();
        cout << "\nSuccessfully loaded robot data from " << filename << ".\n";
    } 


    void promptUserForRobot() {
        string name, company, version, componentName;
        double price, componentWeight;

        do {
            cout << "Enter company name: ";
            getline(cin, company);
        } while (!validateString(company));

        do {
            cout << "Enter robot name: ";
            getline(cin, name);
        } while (!validateString(name));

        do {
            cout << "Enter robot version: ";
            getline(cin, version);
        } while (!validateString(version));

        do {
            cout << "Enter robot price: ";
            cin >> price;
            cin.ignore();
        } while (!validatePrice(price));

        string addComp;
        RobotComponent* component = nullptr;
        cout << "Add a main component? (y/n): ";
        getline(cin, addComp);

        if (addComp == "y" || addComp == "Y") {
            cout << "Enter component name: ";
            getline(cin, componentName);
            cout << "Enter component weight: ";
            cin >> componentWeight;
            cin.ignore();
            component = new RobotComponent(componentName, componentWeight);
        }

        addRobot(move(company), move(name), move(version), price, component);
        cout << "Robot added successfully!\n";
    }
};
// Program Greeting with initialization
void displayGreeting() {
    cout << "\n============================================\n";
    cout << "      Humanoid Robot Management System\n";
    cout << "           Developed by Siva Sankar Garika\n";
    cout << "============================================\n";
    cout << "This program manages a registry of humanoid robots\n";
    cout << "with advanced features including:\n";
    cout << "- Polymorphic robot types\n";
    cout << "- Composition with robot components\n";
    cout << "- Dynamic memory management\n";
    cout << "- Advanced input validation\n";
    cout << "============================================\n\n";
}

int main() {
    RobotRegistry registry;
    bool running = true;
    bool menuShown = false;

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
        }
    }

    return 0;
}
